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

static int	safe_dup(int from, int to)
{
	if (dup2(from, to) < 0)
		return (-1);
	if (close(from) < 0)
		return (-1);
	return (1);
}

static void	input_redirec(int argc, char **argv)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;
	int		idx;

	idx = 1;
	while (argc > idx)
	{
		file_fd = open(argv[idx], O_RDONLY, 0666);
		safe_dup(file_fd, STDIN_FILENO);
		idx++;
	}
	// printf("file_fd : %d\n", file_fd);
	read_size = read(STDIN_FILENO, buf, 42);
	printf("read_size : %zd\nbuf : %s\n", read_size, buf);
}

static void	output_redirec(int argc, char **argv)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;
	int		idx;

	idx = 1;
	file_fd = -1;
	while (argc > idx)
	{
		file_fd = open(argv[idx], O_CREAT | O_RDWR | O_TRUNC, 0666);
		safe_dup(file_fd, STDOUT_FILENO);
		idx++;
	}
	if (file_fd != -1)
		write(STDOUT_FILENO, &"write to last be opened file\n", ft_strlen("write to last opened file\n"));
}

static void	append_redirec(int argc, char **argv)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;
	int		idx;

	idx = 1;
	file_fd = -1;
	while (argc > idx)
	{
		file_fd = open(argv[idx], O_CREAT | O_RDWR | O_APPEND, 0666);
		safe_dup(file_fd, STDOUT_FILENO);
		idx++;
	}
	if (file_fd != -1)
		write(STDOUT_FILENO, &"write to last be opened file\n", ft_strlen("write to last opened file\n"));
}

int	main(int argc, char **argv)
{
	int		file_fd;
	char	buf[42];
	ssize_t	read_size;
	int		idx;

	if (argc < 2)
		return (1);
	idx = 1;
	file_fd = -1;
	while (argc > idx)
	{
		file_fd = open(argv[idx], O_CREAT | O_RDWR | O_APPEND, 0666);
		safe_dup(file_fd, STDOUT_FILENO);
		idx++;
	}
	if (file_fd != -1)
		write(STDOUT_FILENO, &"write to last be opened file\n", ft_strlen("write to last opened file\n"));
	/*
		< input case
	*/

	return (0);
}
