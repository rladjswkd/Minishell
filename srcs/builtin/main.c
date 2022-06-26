#include <stdio.h>
#include <unistd.h>
#include "builtin.h"
#include "utils.h"
#include <fcntl.h>
#include <stdlib.h>

int	main(int argc, char **argv)
{
	char	*buf;
	char	*ret;
	int		fd;

	if (argc < 2)
		return (1);
	// buf = NULL;
	// read(STDIN_FILENO, (char *)buf, 3);
	// printf("buf : %s\n", buf);
	// fd = open("test.txt", O_RDWR);
	// printf("fd : %d\n", fd);
	// printf("ft_strlen(buf) : %d\n", ft_strlen(buf));
	// write(fd, buf, ft_strlen(buf));
	// exit_cmd(atoi(argv[1]));
	print_current_working_directory_cmd();
	printf("\nbuf : %s\n", buf);
	// printf("current path : %s\n", ret);
	// printf("argv[1] %s\n", argv[1]);
	change_directory_cmd(argv[1]);
	print_current_working_directory_cmd();
	// ret = print_current_working_directory_cmd();
	// printf("current path : %s\n", ret);
	// exit_cmd(42);
	// exit_cmd에 값을 안줄수도 있는가?
	// status를 넘겨주고 없으면 default로 0을 준다.
	return (0);
}
