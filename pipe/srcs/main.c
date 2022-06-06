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
#include "utils.h"

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

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		file1_fd;
	int		file2_fd;
	int		pid1;
	int		pid2;
	char	*path;
	char	**cmd;

	// if (argc != 5)
	// 	return (1);
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
			printf("%s %s\n", argv[1], strerror(errno));
			perror("error");
			ft_putstr("");
			return (3);
		}
		if (dup2(file1_fd, STDIN_FILENO) < 0)
		{
			printf("%s dup2 %s\n", argv[1], strerror(errno));
			perror("error");
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
			strerror(errno);
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
		//

	}
	/* */
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (0);
}
