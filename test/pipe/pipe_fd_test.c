#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int fd[2];

    fd[0] = dup(STDIN_FILENO);
    printf("fd[0] : %d\n", fd[0]);
    close(fd[0]);
    printf("after close(fd[0]) : %d\n", fd[0]);
    printf("fd[1] : %d\n", fd[1]);
    fd[1] = dup(STDIN_FILENO);
    printf("after close(fd[1]) : %d\n", fd[1]);
    return (0);
}

