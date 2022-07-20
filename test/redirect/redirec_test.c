#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/*
	- < > << >> 각각 1개씩 테스트
	- 같은걸 연속으로 테스트
		- <, done
		- >
	- 2개를 섞어서 테스트
		- 순서 바꾸어서도 적용
	- 2개를 여러번 섞어서 테스트
	- 2개 이상을 1번씩 섞어서 테스트
	- 2개 이상을 2번 이상씩 섞어서 테스트s
*/

static size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

static int	safe_dup2(int from, int to)
{
	if (dup2(from, to) < 0)
		return (-1);
	if (close(from) < 0)
		return (-1);
	return (1);
}

static void	input_redirec(char *file_name)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;

	file_fd = open(file_name, O_RDONLY, 0666);
	safe_dup2(file_fd, STDIN_FILENO);
	// read_size = read(STDIN_FILENO, buf, 42);
	// printf("read_size : %zd\nbuf : %s\n", read_size, buf);
}

static void	output_redirec(char *file_name)
{
	int		file_fd;
	char	buf[42];

	file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	safe_dup2(file_fd, STDOUT_FILENO);
	// write(STDOUT_FILENO, &"write to last be opened file\n", ft_strlen("write to last opened file\n"));
}

static void	append_redirec(char *file_name)
{
	int		file_fd;
	char	buf[42];

	file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	safe_dup2(file_fd, STDOUT_FILENO);
	// write(STDOUT_FILENO, &"write to last be opened file\n", ft_strlen("write to last opened file\n"));
}

int	main(int argc, char **argv)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;
	int		idx;
	char	*cmd[] = {"cat", NULL};

	if (argc < 4)
		return (1);
	for (int i = 0; i < 42; i++)
	{
		input_redirec(argv[2]);
		output_redirec(argv[1]);
		append_redirec(argv[3]);
	}
	if (execve("/bin/cat", cmd, NULL) < 0)
		return (1);
	/*
		< input case
	*/

	return (0);
}
