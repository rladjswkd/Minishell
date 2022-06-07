/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:50 by jim               #+#    #+#             */
/*   Updated: 2022/06/06 21:38:51 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"

typedef enum	e_bool_flag
{
	FALSE = 0,
	TRUE = 1,
}				t_e_bool_flag;

typedef enum	e_flag
{
	ERROR = -1,
	SUCCESS = 0,
	FAIL = 1,
}				t_e_flag;

static void	safe_free(char	**char_pptr)
{
	free(*char_pptr);
	*char_pptr = NULL;
}

static char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	idx;
	size_t	sub_idx;
	char	*str;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)malloc(sizeof(char *) * (s1_len + s2_len + 1));
	if (str == NULL)
		return (NULL);
	idx = 0;
	while (idx < s1_len)
	{
		str[idx] = s1[idx];
		idx++;
	}
	sub_idx = 0;
	while (idx < s1_len + s2_len)
	{
		str[idx] = s2[sub_idx];
		sub_idx++;
		idx++;
	}
	return (str);
}

char	**find_path_list(char **envp)
{
	/*
	- 동작과정
		env에서 PATH 환경변수를 가져온다.
			- environ에 접근하여
				PATH로 시작하는 것을 찾는다.
				strnstr()사용
			- PATH를 ":" 기준으로 자른다.
				한개씩 반복문 돌면서 execve로 실행시킨다.
	
	*/
	char	*path;
	char	**path_list;
	size_t	idx;

	path = NULL;
	while (*envp && path == NULL)
	{
		path = ft_strnstr(*envp, "PATH", ft_strlen("PATH="));
		envp++;
	}
	if (path == NULL)
		return (NULL);
	path += sizeof(char) * ft_strlen("PATH=");
	return (ft_split(path, ':'));

}

int	execute_cmd(char **path_list, char *argv)
{
	char	**cmd;
	char	*cmd_path;
	char	*path_with_slash;
	size_t	idx;

	idx = 0;
	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
	{
		free_list(&path_list);
		return (ERROR);
	}
	while (path_list[idx])
	{
		path_with_slash = ft_strjoin(path_list[idx], "/");
		cmd_path = ft_strjoin(path_with_slash, cmd[0]);
		safe_free(&path_with_slash);
		printf("cmd_path : %s\n", cmd_path);
		execve(cmd_path, cmd, NULL);
		// execve 정상동작되는 경우 반환값 없으며 테스트 결과 호출된 함수 밖으로 나가는 것으로 보임
		// printf("before safe_free\n");
		safe_free(&cmd_path);
		idx++;
	}
	printf("after while\n");
	free_list(&cmd);
	free_list(&path_list);
	return (SUCCESS);
}

int	main(int argc, char **argv, char **envp)
{
	// int		fd[2];
	// int		file1_fd;
	// int		file2_fd;
	// int		pid1;
	// int		pid2;
	// char	*path;
	// char	**cmd;
	char	**path_list;
	int		execute_cmd_return_val;

	// if (argc != 5)
	// 	return (1);
	path_list = find_path_list(envp);
	if (path_list == NULL)
	{
		printf("path_list is NULL\n");
		return (1);
	}
	execute_cmd_return_val = execute_cmd(path_list, argv[1]);
	printf("execute_cmd_return_val : %d\n", execute_cmd_return_val);
	while (42);
	// execute_cmd(char **path_list, char *argv)
	/*
	if (pipe(fd) < 0)
	{
		printf("pipe error, %s\n", strerror(errno));
		return (5);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (1);
	// child process
	if (pid1 == 0)
	{
		file1_fd = open(argv[1], O_RDONLY);
		if (file1_fd < 0)
		{
			printf("%s : %s\n", argv[1], strerror(errno));
			ft_putstr("");
			return (3);
		}
		if (dup2(file1_fd, STDIN_FILENO) < 0)
		{
			printf("%s dup2 %s\n", argv[1], strerror(errno));
			return (4);
		}
		close(file1_fd);
		if (dup2(fd[1], STDOUT_FILENO) < 0)
		{
			printf("%s dup2 %s\n", argv[1], strerror(errno));
			return (4);
		}
		close(fd[0]);
		close(fd[1]);
		// execlp(argv[2], argv[2], NULL);
		// strjoin 필요
		printf("before split\n");
		cmd = ft_split(argv[2], ' ');
		if (cmd == NULL)
		{
			printf("ft_split fail\n");
			(NULL);
		}
		path = ft_strjoin("/bin/", cmd[0]);
		if (execve(path, cmd, NULL) < 0)
		{
			printf("%s\n", argv[1], strerror(errno));
			free(path);
			path = NULL;
		}
		// free_list(&cmd);
		free(path);
		path = NULL;
	}
	// while (42);
	// pipe fork
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		// printf("pid2 have been created\n");
		// pipe로 넘겨받은 값을 STDIN으로 넘긴다.(builtin에서 읽을 수 있도록!, 하지만 STDIN이어야지만 읽일 수 있는건지는 모른다.)
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			printf("%s dup2 %s\n", argv[1], strerror(errno));
			return (4);
		}
		close(fd[0]);
		close(fd[1]);
		// printf("argv[4] : %s\n", argv[4]);
		file2_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		// printf("file2_fd : %d\n", file2_fd);
		if (file2_fd < 0)
		{
			printf("file2_fd error, %s\n", strerror(errno));
			return (3);
		}
		dup2(file2_fd, STDOUT_FILENO);
		close(file2_fd);
		// execlp(argv[3], argv[3], NULL);
		cmd = ft_split(argv[3], ' ');
		if (cmd == NULL)
		{
			printf("ft_split fail\n");
			(NULL);
		}
		path = ft_strjoin("/bin/", cmd[0]);
		if (execve(path, cmd, NULL) < 0)
		{
			strerror(errno);
			free(path);
			path = NULL;
		}
		// free_list(&cmd);
		free(path);
		path = NULL;

	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	*/
	return (0);
}
