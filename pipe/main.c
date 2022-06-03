/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:50 by jim               #+#    #+#             */
/*   Updated: 2022/06/03 21:52:55 by jim              ###   ########seoul.kr  */
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
	int		pid;
	char	*path;

	// if (argc != 5)
	// 	return (1);
	file1_fd = open(argv[1],O_RDONLY);
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
	// strjoin 필요
	path = ft_strjoin("/bin/", argv[2]);
	// dup2(STDOUT_FILENO, fd[1]);
	if (execve(path, &argv[2], NULL) < 0)
		strerror(errno);
	if (pipe(fd) != 0)
	{
		strerror(errno);
		return (5);
	}
	dup2(STDOUT_FILENO, fd[1]);
	pid = fork();
	if (pid < 0)
	{
		strerror(errno);
		return (3);
	}
	path = ft_strjoin("/bin/", argv[3]);
	file2_fd = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY);
	if (file2_fd < 0)
	{
		strerror(errno);
		return (3);
	}
	if (pid == 0)
	{
		if (dup2(fd[0], file2_fd) < 0)
		{
			strerror(errno);
			return (4);
		}
		close(fd[0]);
		close(fd[1]);
		execve(path, &argv[3], NULL);
	}

	file2_fd
	// close(fd[0]);
	// close(fd[1]);
	/* child process */
	// waitpid(pid);
	return (0);
}
