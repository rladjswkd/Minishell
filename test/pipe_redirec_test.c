#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

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

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	ft_putstr_fd(int fd, const char *str)
{
	write(fd, str, ft_strlen(str));
}

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
	ft_putstr_fd(STDERR_FILENO, "connect_to_prev\n");
	if (dup2(pipe_fd[READ_END], STDIN_FILENO) < 0)
		return (-1);
	if (close(pipe_fd[READ_END]) < 0)
		return (-1);
	return (1);
}

/*
이미 닫힌 fd를 close할 경우 error가 발생할 수 있다.
*/
static int	connect_to_next(t_fd *pipe_fd)
{
	ft_putstr_fd(STDERR_FILENO, "connect_to_next\n");
	printf("pipe_fd[READ_END] : %d\n", pipe_fd[READ_END]);
	if (close(pipe_fd[READ_END]) < 0)
		return (-1);
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
		return (-1);
	if (close(pipe_fd[WRITE_END]) < 0)
		return (-1);
	printf("pipe_fd[READ_END] after dup2 : %d\n", pipe_fd[READ_END]);
	return (1);
}

static int	is_exist_prev_pipe(int org_cnt, int cnt)
{
	if (org_cnt > cnt)
		return (1);
	return (0);
}

static int	is_exist_next_pipe(int cnt)
{
	if (cnt > 0)
		return (1);
	return (0);
}

static int	child_process(t_fd *pipe_fd, int pipe_org_cnt, int pipe_cnt)
{
	char	*cmd[] = {"ls", "-al", NULL};

	if (is_exist_prev_pipe(pipe_org_cnt, pipe_cnt))
		connect_to_prev(pipe_fd);
	if (is_exist_next_pipe(pipe_cnt))
		connect_to_next(pipe_fd);
	if (execve("/bin/ls", cmd, NULL) < 0)
		ft_putstr_fd(STDERR_FILENO, "execve error\n");
	return (2);
}

/*
	현재가 오른쪽으로 연결하는지 왼쪽으로 연결하는지에 따라서 달라진다.
	닫아야할 fd가 달라진다.
	어떻게 구분해서 넘겨줄것인가
	조건문을 덕지덕지 나눠서 넣지 않고 할수 있는 방법은 무엇인가?
	왼쪽에 파이프가 있었다면 
	close(fd[WRITE_END]);
	parent process가 child보다 늦게 실행되는가?
*/
static int	parent_process(int *pipe_fd, pid_t pid, int *status, int pipe_org_cnt, int pipe_cnt)
{
	if (is_exist_prev_pipe(pipe_org_cnt, pipe_cnt))
		if (close(pipe_fd[READ_END]) < 0)
			return (-1);
	if (is_exist_next_pipe(pipe_cnt))
		if (close(pipe_fd[WRITE_END]) < 0)
			return (-1);
	waitpid(pid, status, 0);
	return (1);
}

int main(int argc, char **argv)
{
	int		pipe_fd[2][2];
	int		pid;
	int		*status;
	int		multipipe_cnt;
	int		org_multipipe_cnt;
	int		*pfd;

	org_multipipe_cnt = 5;
	multipipe_cnt = org_multipipe_cnt;
	while (1)
	{
		if (is_exist_next_pipe(multipipe_cnt))
		{
			pfd = pipe_fd[(multipipe_cnt - 1) % 2];
			if (pipe(pfd) < 0)
				return (1);
			printf("pfd[0] : %d\n", pfd[0]);
			printf("pfd[1] : %d\n", pfd[1]);
		}
		// builtin이면 fork()를 하지 않는다.
		// 부모 프로세스로 먼저 fork된다는 보장이 있는가?
		// 생각해보니까 사실 상관없다. fork()시점에서 이미 close(fd[WRITE_END]) 신경 쓸 필요없다. fork()이전에 했는지가 중요하다.
		pid = fork();
		if (pid < 0)
			return (1);
		else if (pid == 0)
			child_process(pfd, org_multipipe_cnt, multipipe_cnt);
		else
			parent_process(pfd, pid, status, org_multipipe_cnt, multipipe_cnt);
		multipipe_cnt--;
		if (multipipe_cnt + 1 <= 0)
			break ;
	}
	return (0);
}
