
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

int main()
{
    int status;
    char message[100];

while (true)
{
    std::cin.getline(message, 100, '\n');
    pid_t child = fork();

    if (child == 0)
    {   
        execl("/bin/sh", "sh", "-c", message, NULL);
        exit(0);
        
    }
    else if(child < 0)
    {
        continue;
    }
    else
    {
        waitpid(child, &status, 0);
    }

}
    return 0;
}