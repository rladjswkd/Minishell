#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    int fd[2];
    int pid1;

    if (pipe(fd) < 0)
        return (1);
    pid1 = fork();
    if (pid1 < 0)    
        return (2);
    if (pid1 == 0)
    {
        dup2(fd[1], STDOUT_FILENO);
        
    }
    return (0);
}