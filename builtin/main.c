#include <stdio.h>
#include <unistd.h>
#include "builtin.h"

int main(int argc, char **argv)
{
	char	*buf;
	char	*ret;

	if (argc < 2)
		return (1);
	buf = NULL;
	ret = print_current_working_directory_cmd();
	printf("buf : %s\n", buf);
	printf("current path : %s\n", ret);
	printf("%s\n", argv[1]);
	change_directory_cmd(argv[1]);
	ret = print_current_working_directory_cmd();
	printf("current path : %s\n", ret);
	exit_cmd(42);
	// exit_cmd에 값을 안줄수도 있는가?
	// status를 넘겨주고 없으면 default로 0을 준다.
	return (0);
}