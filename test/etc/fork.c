#include <unistd.h>
#include <stdio.h>

int main()
{
    int pid;

    pid = fork();
    if (pid < 0)
        return (-1);
    else if (pid == 0)
        printf("child process\n");
    else
        printf("parent process\n");
    return (0);
}