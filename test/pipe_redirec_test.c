#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
	echo a > output > b > c > d < e | cat |
	stdout 
	- test할 사항
	- pipe 1개, 2개, n개 일때의 fd 전달
	- redirec 있을때 케이스
*/

typedef enum e_pipe_type
{
	READ_END,
	WRITE_END,
}			t_pipe_type;

typedef int	t_fd;

static int	before_pipe(t_fd fd[2], char **argv)
{
	int		pid;
	char	*cmd[] = {"cat", NULL};

	pid = fork();
	if (pid < 0)
	{
		printf("child process error\n");
		return (1);
	}
	else if (pid == 0)
	{
		close(fd[READ_END]);
		if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
			return (1);
		close(fd[WRITE_END]);
		// cmd[1] = argv[0];
		if (execve("/bin/cat", cmd, NULL) < 0)
			printf("execve error\n");
	}
	else
	{
		close(fd[WRITE_END]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

static int	after_pipe(t_fd fd[2], char **argv)
{
	int		pid;
	char	*cmd[] = {"cat", NULL};

	pid = fork();
	if (pid < 0)
		return (1);
	else if (pid == 0)
	{
		close(fd[WRITE_END]);
		if (dup2(fd[READ_END], STDIN_FILENO) < 0)
			return (1);
		close(fd[READ_END]);
		if (execve("/bin/cat", cmd, NULL) < 0)
			printf("execve error\n");
		return (1);
	}
	else
	{
		close(fd[READ_END]);
		waitpid(pid, NULL, 0);
	}
	return (0);
}

static int	connect_pipe(int *fd, char **argv)
{
	before_pipe(fd, argv);
	after_pipe(fd, argv);
	return (0);
}

static int	*make_pipe()
{
	int	*fd;

	fd = (int *)malloc(sizeof(int) * 2);
	if (fd == NULL)
		return (NULL);
	if (pipe(fd) < 0)
	{
		free(fd);
		fd = NULL;
	}
	return (fd);
}

/*
	- make multipipe
	- 다음에 파이프가 있는지 확인하고서 있으면 연결한다.
	- fork와 파이프 연결은 개별로 바꾼다.
	- 현재 위치(명령어 블록)기준으로 이전에 파이프가 있었는지, 다음에 파이프가 있는지를 확인하여
	이전에 파이프가 있었다면
	dup2(fd[READ_END], STDIN)으로 변경한다.
	이후에 파이프가 있다면
	dup2(fd[WRITE_END], STDOUT)으로 변경한다.
	connect_to_prev
	connect_to_next
	이후에 파이프 기호가 있다면
	pipe()선언한다.
	fork()를 뜬다.
	
*/
int main(int argc, char **argv)
{
	int		*pipe_fd;
	// char	*cmd[] = {"ls", NULL};
	size_t	multipipe_cnt;;

	multipipe_cnt = 2;
	while (multipipe_cnt)
	{
		// printf("multipipe_cnt : %zu\n", multipipe_cnt);
		pipe_fd = make_pipe();
		fork();
		if (pipe_fd == NULL)
			return (1);
		before_pipe(pipe_fd, argv);
		after_pipe(pipe_fd, argv);
		// connect_pipe(pipe_fd, argv);
		free(pipe_fd);
		multipipe_cnt--;
	}

	return (0);
}