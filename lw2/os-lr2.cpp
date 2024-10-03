#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>

void print_time()
{
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    printf("Time: %d : %d : %d \n\n", datetime.tm_hour, datetime.tm_min, datetime.tm_sec);
}

void print_info(int n)
{
    printf("Process number: %d\n", n);
    printf("Process: %d \n", getpid());
    printf("Parent process: %d \n", getppid());

    print_time();
}

int main()
{

    pid_t parent_process = getpid();
    pid_t child_process_1 = fork();
    pid_t child_process_2 = -1;
    if(child_process_1 != 0) child_process_2 = fork();
    int status;

    waitpid(child_process_2, &status, 0);
    
    if (child_process_1 == 0)
    {
        print_info(1);
    }

    if (child_process_2 == 0)
    {
        sleep(1);
        print_info(2);
    }

    if (parent_process == getpid())
    {
        sleep(1);
        print_info(0);
        system("ps -x");
    }

    return 0;
}
