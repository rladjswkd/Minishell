/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:50 by jim               #+#    #+#             */
/*   Updated: 2022/06/05 22:28:55 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t	ft_strlen(const char *s1)
{
	size_t	len;

	len = 0;
	while (*s1++)
		len++;
	return (len);
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

int	main(int argc, char **argv)
{
	int		fd[2];
	int		file1_fd;
	int		file2_fd;
	int		pid1;
	int		pid2;
	char	*path;

	// if (argc != 5)
	// 	return (1);
	if (pipe(fd) < 0)
	{
		strerror(errno);
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
			strerror(errno);
			return (3);
		}
		if (dup2(file1_fd, STDIN_FILENO) < 0)
		{
			strerror(errno);
			return (4);
		}
		close(file1_fd);
		// strjoin 필요
		dup2(fd[1], STDOUT_FILENO);
		close(fd[0]);
		close(fd[1]);
		execlp(argv[2], argv[2], NULL);
		// ¡  사용의 문제 pipe 구성은 성공
		// path = ft_strjoin("/bin/", argv[2]);
		// if (execve(path, &argv[2], NULL) < 0)
		// {
		// 	strerror(errno);
		// 	free(path);
		// 	path = NULL;
		// }
		// free(path);
		// path = NULL;
	}
	pid2 = fork();
	if (pid2 < 0)
		return (1);
	if (pid2 == 0)
	{
		// printf("pid2 have benn created\n");
		// pipe로 넘겨받은 값을 STDIN으로 넘긴다.(builtin에서 읽을 수 있도록!, 하지만 STDIN이어야지만 읽일 수 있는건지는 모른다.)
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		close(fd[1]);
		// printf("argv[4] : %s\n", argv[4]);
		file2_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 644);
		// printf("file2_fd : %d\n", file2_fd);
		if (file2_fd < 0)
		{
			printf("file2_fd error\n");
			strerror(errno);
			return (3);
		}
		// printf("file2_fd have benn opened : %d\n", file2_fd);
		// dup2(STDOUT_FILENO, file2_fd);
		dup2(file2_fd, STDOUT_FILENO);
		execlp(argv[3], argv[3], NULL);
		// path = ft_strjoin("/bin/", argv[3]);
		// printf("path : %s\n", path);
		// if (execve(path, &argv[3], NULL) < 0)
		// {
		// 	strerror(errno);
		// 	free(path);
		// 	path = NULL;
		// }
		// free(path);
		// path = NULL;
		close(file2_fd);
	}
	/* */
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	return (0);
}
