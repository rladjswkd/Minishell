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

	// if (argc < 2)
	// 	return (1);
	// echo_cmd(argv);
	int len = 5;
	print_current_working_directory_cmd();
	while (len--)
	{
		// print_current_working_directory_cmd();
		change_directory_cmd(argv[1]);
		print_current_working_directory_cmd();
		// printf("%s\n", print_current_working_directory_cmd());
	}
	return (0);
}
