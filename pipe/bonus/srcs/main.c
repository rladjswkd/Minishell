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
			/
	
	*/
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

int	execute_cmd(char **envp, char *argv)
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
		// printf("cmd_path : %s\n", cmd_path);
		// execlp();
		// = {"ls", "-al", NULL};
		execve(cmd_path, cmd, envp);
		// execve 정상동작되는 경우 반환값 없으며 테스트 결과 호출된 함수 밖으로 나가는 것으로 보임
		safe_free(&cmd_path);
		idx++;
	}
	free_list(&cmd);
	free_list(&path_list);
	// printf("%s: command not found\n", argv);
	return (FAIL);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		file1_fd;
	int		file2_fd;
	int		pid1;
	int		pid2;
	int		execute_cmd_return_val;

	if (argc < 1)
		return (1);
	/*
		환경변수를 명령어 실행할때마다 받는데 찾는 과정이 비효율적이다.
		파이프나 redirction으로 나뉘어있더라도 해당 명령이 입력될때까지는 1번만 환경변수를 가져와서 다른 명령어들에 주면될거같다.
		즉, newline 입력받을때까지는 환경변수를 1번만 읽어서 호출한다.
	*/
	if (pipe(fd) < 0)
	{
		printf("pipe error, %s\n", strerror(errno));
		return (5);
	}
	pid1 = fork();
	if (pid1 < 0)
	{
		printf("fork error\n");
		return (1);
	}
	// child process
	if (pid1 == 0)
	{
		file1_fd = open(argv[1], O_RDONLY);
		if (file1_fd < 0)
		{
			printf("%s : %s\n", argv[1], strerror(errno));
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
		execute_cmd_return_val = execute_cmd(envp, argv[2]);
		close(fd[0]);
		close(fd[1]);
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
		// STDIN일때 읽는것도 판단하지만 man이나 기타 공식문서 확인 필요.
		// 항상그러한가?
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			printf("%s dup2 %s\n", argv[1], strerror(errno));
			return (4);
		}
		close(fd[0]);
		close(fd[1]);
		file2_fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (file2_fd < 0)
		{
			printf("file2_fd error, %s\n", strerror(errno));
			return (3);
		}
		dup2(file2_fd, STDOUT_FILENO);
		close(file2_fd);
		execute_cmd_return_val = execute_cmd(envp, argv[3]);
		// printf("second execute_cmd_return_val : %d", execute_cmd_return_val);
	}
	/**/
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	// while (42);
	// memory issue by checking valgrind
	/*
		jake@DESKTOP-39VE82R:/mnt/d/42/Minishell/pipe$ valgrind --leak-check=yes ./pipex
		==3668== Memcheck, a memory error detector
		==3668== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
		==3668== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
		==3668== Command: ./pipex
		==3668==
		==3669== Syscall param openat(filename) points to unaddressable byte(s)
		==3669==    at 0x4962D1B: open (open64.c:48)
		==3669==    by 0x1096C1: main (in /mnt/d/42/Minishell/pipe/pipex)
		==3669==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
		==3669==
		==3670== Conditional jump or move depends on uninitialised value(s)
		==3670==    at 0x109F42: ft_strlen (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x109355: ft_strjoin (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x109575: execute_cmd (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x1098E3: main (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==
		==3670== Syscall param execve(filename) points to uninitialised byte(s)
		==3670==    at 0x493816B: execve (syscall-template.S:78)
		==3670==    by 0x10959D: execute_cmd (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x1098E3: main (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==  Address 0x4a47a99 is 25 bytes inside a block of size 208 alloc'd
		==3670==    at 0x483B7F3: malloc (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
		==3670==    by 0x109384: ft_strjoin (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x109575: execute_cmd (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==    by 0x1098E3: main (in /mnt/d/42/Minishell/pipe/pipex)
		==3670==
		(null) : Bad address
		==3669==
		==3669== HEAP SUMMARY:
		==3669==     in use at exit: 0 bytes in 0 blocks
		==3669==   total heap usage: 1 allocs, 1 frees, 1,024 bytes allocated
		==3669==
		==3669== All heap blocks were freed -- no leaks are possible
		==3669==
		==3669== For lists of detected and suppressed errors, rerun with: -s
		==3669== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
	*/
	return (0);
}
