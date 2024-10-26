/* lw3 OS sem3 variants 5 using semaphore */

/* Создать консольное приложение, порождающее несколько потоков.
 * Первый поток высчитывает таблицу значений функции (можно взять любую
 * математическую функцию), второй поток осуществляет вывод каждого
 * значения в файл по мере его высчитывания. Третий поток ведет лог
 * процедуры обмена, записывая туда время получения значения функции и
 * время записи данного значения в файл. Каждая пара значений,
 * полученная в процессе вычисления, должна быть занесена в объект
 * класса Point, который может быть уничтожен только тогда, когда
 * информация о нем будет занесена в лог-файл. Обращение к объекту
 * Point должно происходить через потокобезопасный умный указатель.
 */

#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Define constants
#define START (-10)
#define STOP 10
#define STEP 0.1
#define SIZE_MMAP (sizeof(struct Point) * ((int) (abs(START - STOP) / STEP) - 1))
#define SLEEP_TIME 0
#define OUTPUT_FILE "output.txt"
#define LOG_FILE "log.txt"

typedef struct Point {
    double x;
    double y;
    time_t time_received;
    time_t time_logged;
} Point;

typedef struct {
    Point *point;
    sem_t *sem_write;
    sem_t *sem_log;
} ThreadArgs;

void *calculate_function(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *) args;

    for (double i = START; i < STOP - STEP / 2; i += STEP) {
        int index = (i - START + STEP / 2) / STEP;

        thread_args->point[index].x = i;
        thread_args->point[index].y = sin(i);
        thread_args->point[index].time_received = time(NULL);

        sleep(SLEEP_TIME);
        sem_post(thread_args->sem_write);
    }
    pthread_exit(EXIT_SUCCESS);
}

void *write_to_file(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *) args;

    for (double i = START; i < STOP - STEP / 2; i += STEP) {
        int index = (i - START + STEP / 2) / STEP;

        sem_wait(thread_args->sem_write);
        FILE *file = fopen(OUTPUT_FILE, "a");
        if (file) {
            fprintf(file, "x: %lf, y: %lf\n", thread_args->point[index].x, thread_args->point[index].y);
            fclose(file);
        }
        thread_args->point[index].time_logged = time(NULL);

        sem_post(thread_args->sem_log);
    }
    pthread_exit(EXIT_SUCCESS);
}

void *log_times(void *args) {
    ThreadArgs *thread_args = (ThreadArgs *) args;

    for (double i = START; i < STOP - STEP / 2; i += STEP) {
        int index = (i - START + STEP / 2) / STEP;

        sem_wait(thread_args->sem_log);
        FILE *log_file = fopen(LOG_FILE, "a");
        if (log_file) {
            fprintf(log_file, "time_received for x = %lf: %s", thread_args->point[index].x,
                    ctime(&(thread_args->point)[index].time_received));
            fprintf(log_file, "time_logged for x = %lf: %s", thread_args->point[index].x,
                    ctime(&(thread_args->point)[index].time_logged));
            fclose(log_file);
        }
    }
    pthread_exit(EXIT_SUCCESS);
}

int main(void) {

    Point *shared_mem = mmap(NULL, SIZE_MMAP, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    sem_unlink("/sem_write");
    sem_unlink("/sem_log");

    sem_t *sem_write = sem_open("/sem_write", O_CREAT, O_RDWR, 0);
    sem_t *sem_log = sem_open("/sem_log", O_CREAT, O_RDWR, 0);

    if (sem_write == SEM_FAILED || sem_log == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    FILE *file;

    file = fopen(OUTPUT_FILE, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(file);

    file = fopen(LOG_FILE, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(file);

/*
    int size = (abs(START - STOP) / STEP) - 1;
    int size_of_point = sizeof(Point);
    printf("parent PID: %i, SIZE: %i, size of point: %i, size mmap: %i\n", getpid(), size, size_of_point, SIZE_MMAP);
*/

    pthread_t t1, t2, t3;
    int s1, s2, s3;

    ThreadArgs *args = (ThreadArgs *) malloc(sizeof(ThreadArgs));
    *args = (ThreadArgs) {shared_mem, sem_write, sem_log};

    s1 = pthread_create(&t1, NULL, calculate_function, (void *) args);
    s2 = pthread_create(&t2, NULL, write_to_file, (void *) args);
    s3 = pthread_create(&t3, NULL, log_times, (void *) args);

    if (s1 || s2 || s3) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    free(args);

    sem_close(sem_write);
    sem_close(sem_log);

    sem_unlink("/sem_write");
    sem_unlink("/sem_log");

    munmap(shared_mem, SIZE_MMAP);

    exit(EXIT_SUCCESS);
}
