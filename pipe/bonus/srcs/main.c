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
#include "pipex.h"

static void	safe_free(char	**char_pptr)
{
	free(*char_pptr);
	*char_pptr = NULL;
}

static char	**find_path_list(char **envp)
{
	char	*path;

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

static int	execute_cmd(char **envp, char *argv)
{
	char	**cmd;
	char	*cmd_path;
	char	**path_list;
	char	*path_with_slash;
	size_t	idx;

	if (envp == NULL || argv == NULL)
		return (FALSE);
	idx = 0;
	path_list = find_path_list(envp);
	if (path_list == NULL)
		return (ERROR);
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
		execve(cmd_path, cmd, envp);
		safe_free(&cmd_path);
		idx++;
	}
	free_list(&cmd);
	free_list(&path_list);
	return (FAIL);
}

static size_t	max_nonnegative(char *s1, char *s2)
{
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (s1_size > s2_size)
		return (s1_size);
	return (s2_size);
}

static int	here_doc(int argc, char **argv, char **envp)
{

	return (1);
}

/*
	// multipipe
	/*
		./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
		< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
	*/
*/
static int	multipipe(int argc, char **argv, char **envp)
{
	int		fd[2][2];
	int		*prev_fd;
	int		*next_fd;
	int		pid[3];
	int		file_fd[2];
	int		idx;

	if (pipe(fd[0]) < 0)
	{
		printf("%s\n", strerror(errno));
		return (1);
	}
	pid[0] = fork();
	if (pid1 < 0)
	{
		printf("%s\n", strerror(errno));
		return (2);
	}
	if (pid1 == 0)
	{
		file_fd[0] = open(argv[1], O_RDONLY);
		if (file_fd[0]  < 0)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		if (dup2(file_fd[0], STDIN_FILENO))
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		close(file_fd[0]);
		if (dup2(fd[0][1], STDOUT_FILENO))
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		if (execute_cmd(envp, argv[2]) == FAIL)
			exit(1);
	}
	idx = 2;
	// for making pipeline
	while (idx < argc - 1)
	{
		/*
			pipe 2개를 돌아가면서 쓴다.
		*/
		if (pipe(fd[1]) < 0)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		pid[1] = fork();
		if (pid[1] < 0)
		{
			printf("%s\n", strerror(errno));
			return (2);
		}
		// pi
		// to be continue
		idx++;
		// 부모 프로세스의 pid[1]를 가리킬것인가?
		waitpid(pid[1]);
	}
	/* redirection to output file*/
	pid[2] = fork();
	if (pid[2] < 0)
	{
		printf("%s\n", strerror(errno));
		waitpid(pid[0]);
		return (1);
	}
	if (pid[2] == 0)
	{
		file2_fd = open(argv[argc - 1], O_CREATE | O_RDWR | O_TRUNC);
		if (file2_fd < 0)
		{
			printf("%s\n", strerror(errno));
			waitpid(pid[0]);
			return (1);
		}
		if (dup2(fd[(argc - 1) % 2][0], STDIN_FILENO) < 0)
		{
			printf("%s\n", strerror(errno));
			return (1);	
		}
		if (dup2(STDOUT_FILENO, file_fd[1]) < 0)
		{
			printf("%s\n", strerror(errno));
			return (1);
		}
		if (execute_cmd(envp, argv[argc - 2]) == FAIL)
		{
			close(file1_fd);
			exit(1);
		}
	}
	waitpid(pid[0]);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	if (argc < 6)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", max_nonnegative("here_doc", argv[1])) == 0)
	{
		// here_doc routine
		/*
			./pipex here_doc LIMITER cmd cmd1 file
			cmd << LIMITER | cmd1 >> file
		*/
		if (here_doc(argc, argv, envp) < 0)
			return (1);
	}
	else
	{
		// multipipe
		/*
			./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
			< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
		*/
		if (multipipe(argc, argv, envp) < 0)
			return (1);
	}
	return (0);
}
