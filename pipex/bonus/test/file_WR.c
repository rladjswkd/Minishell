#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
// #include "get_next_line.h"

static size_t ft_strlen(const char *s)
{
	size_t  len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int main(int argc, char **argv)
{
	int		fd;
	// int		read_fd;
	char	*str;

	if (argc < 2)
		return (42);
	fd = open("test11521.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
	// read_fd =
	if (fd < 0)
	{
		printf("fd : %d\n", fd);
		return (1);
	}
	write(fd, argv[1], ft_strlen(argv[1]));
	write(fd, argv[1], ft_strlen(argv[1]));
	write(fd, &"\n", 1);
    read(fd, str, 42);
    printf("str : %s\n", str);
	close(fd);

    
	return (0);
}
