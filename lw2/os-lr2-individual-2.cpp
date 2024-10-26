#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>


void write_process_info(int n, int *p)
{
    int current = getpid();
    int parent = getppid();
    write(p[1], &n, sizeof(int));
    write(p[1], &current, sizeof(int));
    write(p[1], &parent, sizeof(int));

    printf("process %d", n+1);
    printf(" %d", current);
    printf(" was born by %d \n\n", parent);
    
}

void write_process_killed(int n)
{
    printf("process %d", n+1);
    printf(" %d", getpid());
    printf(" is being killed, parent: %d \n\n", getppid());
}

void print_all_processes_data(pid_t parent, int* processes)
{

    wait(NULL);
    for(int i = 0; i < 7; i++)
    {
        printf("Process %d is a child of ", processes[i*2]);
        printf("%d \n", processes[i*2 + 1]);
    }
}

int main()
{
    int *processes = new int[14];
    pid_t parent = getpid();
    int p[2];
    pipe(p);
    write_process_info(0, p);
    
    pid_t child1 = fork();
    wait(NULL);

    if (getpid() == parent)
    {
        pid_t child2 = fork();
        wait(NULL);
        
        if (child2 == 0)
        {
            write_process_info(2, p);
            pid_t child5 = fork();
            wait(NULL);
            if (child5 == 0)
            {
                write_process_info(5, p);
                write_process_killed(5);
                exit(0);
            }
            write_process_killed(2);
            exit(0);
        }
    } 
    
    if (child1 == 0)
    {
        write_process_info(1, p);
        pid_t child3 = fork();
        wait(NULL);
        if (child3 != 0)
        {
            pid_t child4 = fork();
            wait(NULL);
            if (child4 == 0)
            {
                write_process_info(4, p);
                write_process_killed(4);
                exit(0);
            }
        }

        if (child3 == 0)
        {
            write_process_info(3, p);
            pid_t child6 = fork();
            wait(NULL);
            if (child6 == 0)
            {
                write_process_info(6, p);
                write_process_killed(6);
                exit(0);
            }
            execl("/bin/sh", "sh", "-c", "ls", NULL);
            write_process_killed(3);
            exit(0);
        }
        write_process_killed(1);
        exit(0);
    }

    for (int i = 0; i < 7; i++)
    {
        int n = 0;
        read(p[0], &n, sizeof(int));
        read(p[0], &processes[n*2], sizeof(int));
        read(p[0], &processes[n*2+1], sizeof(int));
    }

    print_all_processes_data(parent, processes);

    printf("\n");

    delete[] processes;
    write_process_killed(0);
    return 0;
}