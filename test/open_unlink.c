#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int return_fd(char *file_name)
{
    int fd;
    fd = open(file_name, O_RDONLY);
    unlink(file_name);
    return (fd);
}

int main(int argc, char **argv)
{
    int fd;
    char buf[42];
    int read_size;

    fd = return_fd("a.txt");
    read_size = read(fd, &buf, 42);
    buf[read_size] = '\0';
    printf("%s\n", buf);
    return (0);
}

