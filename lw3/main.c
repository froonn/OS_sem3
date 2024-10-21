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
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define SIZE_MMAP (sizeof(struct Point))
#define START (-10)
#define STOP 10
#define STEP 1
#define SLEEP_TIME 0
#define OUTPUT_FILE "output.txt"
#define LOG_FILE "log.txt"

typedef struct Point {
    double x;
    double y;
    time_t time_received;
    time_t time_logged;
} Point;

void calculate_function(Point *point, sem_t *sem_calc, sem_t *sem_write) {
    int sem_calc_value, sem_write_value;
    for (double i = START; i < STOP; i += STEP) {
        sem_wait(sem_calc);
        point->x = i;
        point->y = sin(i);
        point->time_received = time(NULL);

        sem_getvalue(sem_calc, &sem_calc_value);
        sem_getvalue(sem_write, &sem_write_value);
        printf("calc_func: sem_calc: %i, sem_write_value: %i, i: %lf, x: %lf\n", sem_calc_value, sem_write_value, i, point->x);

        sem_post(sem_write);
        sleep(SLEEP_TIME);
    }
}

void write_to_file(Point *point, sem_t *sem_write, sem_t *sem_log) {
    int sem_log_value, sem_write_value;
    for (double i = START; i < STOP; i += STEP) {
        sem_wait(sem_write);
        FILE *file = fopen(OUTPUT_FILE, "a");
        if (file) {
            fprintf(file, "x: %lf, y: %lf\n", point->x, point->y);
            fclose(file);
        }

        sem_getvalue(sem_write, &sem_write_value);
        sem_getvalue(sem_log, &sem_log_value);
        printf("write_func: sem_write_value: %i, sem_log_value: %i\n", sem_write_value, sem_log_value);

        point->time_logged = time(NULL);
        sem_post(sem_log);
        sleep(SLEEP_TIME);

    }
}

void log_times(Point *point, sem_t *sem_calc, sem_t *sem_log) {
    int sem_log_value, sem_calc_value;

    for (double i = START; i < STOP; i += STEP) {
        sem_wait(sem_log);
        FILE *log_file = fopen(LOG_FILE, "a");
        if (log_file) {
            fprintf(log_file, "time_received for x = %lf: %s", point->x, ctime(&point->time_received));
            fprintf(log_file, "time_logged for x = %lf: %s", point->x, ctime(&point->time_logged));
            fclose(log_file);
        }

        sem_getvalue(sem_log, &sem_log_value);
        sem_getvalue(sem_calc, &sem_calc_value);
        printf("log_func: sem_calc_value: %i, sem_log_value: %i\n", sem_calc_value, sem_log_value);

        sem_post(sem_calc);
        sleep(SLEEP_TIME);
    }
}

int main() {

    // Create shared memory
    Point *shared_mem = mmap(NULL, SIZE_MMAP, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (shared_mem == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // Create named semaphores
    sem_unlink("/sem_calc");
    sem_unlink("/sem_write");
    sem_unlink("/sem_log");

    sem_t *sem_calc = sem_open("/sem_calc", O_CREAT, O_RDWR, 1);
    sem_t *sem_write = sem_open("/sem_write", O_CREAT, O_RDWR, 0);
    sem_t *sem_log = sem_open("/sem_log", O_CREAT, O_RDWR, 0);

    if (sem_calc == SEM_FAILED || sem_write == SEM_FAILED || sem_log == SEM_FAILED) {
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

    pid_t first_stream, second_stream, third_stream;

    first_stream = fork();
    if (first_stream < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (first_stream == 0) {
        calculate_function(shared_mem, sem_calc, sem_write);

        sem_close(sem_calc);
        sem_close(sem_write);
        sem_close(sem_log);
        munmap(shared_mem, SIZE_MMAP);
        exit(EXIT_SUCCESS);
    }

    second_stream = fork();
    if (second_stream < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (second_stream == 0) {
        write_to_file(shared_mem, sem_write, sem_log);

        sem_close(sem_calc);
        sem_close(sem_write);
        sem_close(sem_log);
        munmap(shared_mem, SIZE_MMAP);
        exit(EXIT_SUCCESS);
    }

    third_stream = fork();
    if (third_stream < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (third_stream == 0) {
        log_times(shared_mem, sem_calc, sem_log);

        sem_close(sem_calc);
        sem_close(sem_write);
        sem_close(sem_log);
        munmap(shared_mem, SIZE_MMAP);
        exit(EXIT_SUCCESS);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    sem_close(sem_calc);
    sem_close(sem_write);
    sem_close(sem_log);
    sem_unlink("/sem_calc");
    sem_unlink("/sem_write");
    sem_unlink("/sem_log");
    munmap(shared_mem, SIZE_MMAP);
    exit(EXIT_SUCCESS);
}