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

static int	*make_pipe(int fd)
{
	return (pipe(fd));
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

static int	connect_to_prev(t_fd *pipe_fd)
{
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) < 0)
		return (0);
	close(pipe_fd[READ_END]);
	return (1);
}

/*
이미 닫힌 fd를 close할 경우 error가 발생할 수 있다.
*/
static int	connect_to_next(t_fd *pipe_fd)
{
	close(pipe_fd[READ_END]);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
		return (0);
	close(pipe_fd[WRITE_END]);
	return (0);
}

static int	is_exist_prev_pipe(size_t org_cnt, size_t cnt)
{
	if (org_cnt > cnt)
		return (1);
	return (0);
}

static int	is_exist_next_pipe(size_t cnt)
{
	if (cnt > 0)
		return (1);
	return (0);
}

static int	child_process(int pipe_org_cnt, int pipe_cnt, t_fd *pipe_fd)
{
	if (is_exist_prev_pipe(pipe_org_cnt, pipe_cnt))
		connect_to_prev(pipe_fd);
	if (is_exist_next_pipe(pipe_cnt))
		connect_to_next(pipe_fd); //prev에서 쓰인것과 다른 fd여야한다.
	return (0);
}

/*
	현재가 오른쪽으로 연결하는지 왼쪽으로 연결하는지에 따라서 달라진다.
	닫아야할 fd가 달라진다.
	어떻게 구분해서 넘겨줄것인가
	조건문을 덕지덕지 나눠서 넣지 않고 할수 있는 방법은 무엇인가?
*/
static int	parent_process(int *pipe_fd, pid_t pid, int status)
{
	// if
	// close(pipe_fd[]);
	waitpid(pid, &status, NULL)
}

int main(int argc, char **argv)
{
	int		pipe_fd[2];
	int		pid;
	int		status;
	// char	*cmd[] = {"ls", NULL};
	size_t	multipipe_cnt;
	size_t	org_multipipe_cnt;

	org_multipipe_cnt = 2;
	multipipe_cnt = 2;
	while (multipipe_cnt)
	{
		if (is_exist_next_pipe(multipipe_cnt))
			if (pipe(pipe_fd) < 0)
				return (1);
		// printf("multipipe_cnt : %zu\n", multipipe_cnt);
		pid = fork();
		if (pid < 0)
			return (1);
		else if (pid == 0)
			child_process(pipe_fd);
		else
			parent_process(pid, ,status);
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