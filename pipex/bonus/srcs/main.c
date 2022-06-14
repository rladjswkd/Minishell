/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:37:50 by jim               #+#    #+#             */
/*   Updated: 2022/06/14 18:39:52 by jim              ###   ########seoul.kr  */
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
#include "get_next_line.h"
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

static int	error_handler(int error_status)
{
	perror(NULL);
	return (error_status);
}

int	file_open(t_file_flag file_flag, char *file_name)
{
	int	file_fd;

	file_fd = -1;
	if (file_flag == FILE_READ)
		file_fd = open(file_name, O_RDONLY);
	else if (file_flag == FILE_WRITE)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC);
	else if (file_flag == FILE_APPEND)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND);
	else if (file_flag == FILE_WRITE_ONLY)
		file_fd = open(file_name, O_CREAT | O_RDWR);
	return (file_fd);
}

int	redirection(t_redirection_flag redirection_flag, char *file_name)
{
	int	file_fd;

	file_fd = -1;
	if (redirection_flag == INPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == OUTPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == HERE_DOC)
		file_fd = file_open(FILE_WRITE_ONLY, file_name);
	else if (redirection_flag == APPEND)
		file_fd = file_open(FILE_APPEND, file_name);
	else
		printf("unknown redirection_flag\n.");
	return (file_fd);
}


/*
	./pipex here_doc LIMITER cmd1 cmd2 file
	cmd1 << LIMITER | cmd2 >> file
*/

static int	init_value(void)
{
	/*
		구조체 필요
	*/
	return (0);
}

static char	*check_tmp_file(void)
{
	char	*file_name;
	char	*tmp_file_name;
	int		file_fd;
	int		num;

	file_name = ft_strdup(".tmp_heredoc_file");
	if (file_name == NULL)
		return (NULL);
	num = 0;
	while (redirection(HERE_DOC, file_name) == -1)
	{
		tmp_file_name = ft_strjoin(file_name, ft_itoa(num));
		if (tmp_file_name == NULL)
		{
			free(file_name);
			return (NULL);
		}
		free(file_name);
		file_name = tmp_file_name;
	}
	/*

	*/
}

static int	heredoc_tmpfile_handle(char *heredoc_word, int *pipe_fd)
{
	/*

		- open tmp file to write
		- gnl done
		- pipe connect (STDOUT to pipe[WRITE_END]
		- write tmp file data to STDOUT
			- tmp file 닫아야해서 위 작업이 필요하다.
		- close tmp file
		- remove tmp file using path
	*/
	int		tmp_file;
	char	*file_name;
	char	*read_str;

	// - tmpfile name check
	file_name = check_tmp_file();
	if (file_name == NULL)
		return (error_handler(1));
	tmp_file = redirection(HERE_DOC, file_name);
	if (tmp_file < 0)
		return (error_handler(1));
	read_str = get_next_line(STDIN_FILENO);
	while (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)))
	{
		if (write(tmp_file, read_str, ft_strlen(read_str)) < 0)
			exit(1);
	}
	if (dup2(tmp_file, STDIN_FILENO) < 0)
		return (error_handler(1));
	if (dup2(pipe_fd[WRITE_END], STDOUT_FILENO) < 0)
		return (error_handler(1));
}

static int	here_doc(int argc, char **argv, char **envp)
{
	char	*heredoc_word;
	char	*cmd1;
	char	*cmd2;
	char	*file_name;
	int		fd[2];
	int		read_fd;
	// int		write_fd;
	int		pid1;
	int		pid2;

	(void)argc;
	heredoc_word = argv[2];
	cmd1 = argv[3];
	cmd2 = argv[4];
	file_name = argv[5];
	if (pipe(fd) < 0)
	{
		perror("pipe");
		return (1);
	}
	pid1 = fork();
	if (pid1 < 0)
		return (error_handler(1));
	else if (pid1 == 0) //child process
	{
		close(fd[READ_END]);
		// need to file name check
		heredoc_tmpfile_handle(heredoc_word, fd);
		execute_cmd(envp, cmd1);
		exit(127);
			// save_read_str(read_str, pList);
			// linked list 이용
		// save_node_to_file();
		// linked list에 있는 data들을 순차적으로 file에 저장한다
		// delete_linked_list(&pList);
		/*
			임시파일을 만들수 있지만 마지막에 EOF에 해당하는 HERE_DOC 들어오고서
			생긴다음에 삭제되는것으로 보인다.
			그러므로 마지막 전까지는 linked list에 node로 저장하고
			here_doc 단어가 들어오면 임시파일에 linked list의 데이터들을 저장한다.

		*/
		/*
			get_next_line로 읽은것을 STDIN이나 STDOUT으로 쓸수없다.
			STDIN으로하면 다음에 get_next_lineg할 것을 못 읽고
			STDOUT은 cmd를 실행결과용으로 쓸것이다.
			즉,  get_next_line으로 읽은 것을 우선 다른 공간에 저장해놓아야한다.
		*/
	}
	pid2 = fork();
	if (pid2 < 0)
		return (error_handler(2));
	else if (pid1 == 0) //child process
	{
		close(fd[WRITE_END]);
		read_fd = redirection(HERE_DOC, file_name);
		if (read_fd < 0)
			return (error_handler(1));
		if (dup2(STDIN_FILENO, read_fd) < 0)
			return (error_handler(2));
		if (dup2(STDOUT_FILENO, fd[WRITE_END]) < 0)
			return (error_handler(2));
		execute_cmd(envp, cmd1);
		exit(127);
	}
	close(fd[0]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}

/*
	// multipipe
		./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
		< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

*/
/*
static int	multipipe(int argc, char **argv, char **envp)
{
	int		fd[2][2];
	int		*prev_fd;
	int		*next_fd;
	int		pid[3];
	int		file_fd[2];
	int		idx;

	if (pipe(fd[READ_END]) < 0)
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
		if (dup2(fd[0][WRITE_END], STDOUT_FILENO))
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
		if (pipe(fd[idx][WRITE_END]) < 0)
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
	// redirection to output file
	pid[2] = fork();
	if (pid[2] < 0)
	{
		printf("%s\n", strerror(errno));
		waitpid(pid[0]);
		return (1);
	}
	if (pid[2] == 0)
	{
		file2_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC);
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
		if (dup2(STDOUT_FILENO, file_fd[WRITE_END]) < 0)
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
*/

int	main(int argc, char **argv, char **envp)
{
	if (argc < 6)
		return (1);
	if (ft_strncmp(argv[1], "here_doc", max_nonnegative("here_doc", argv[1])) \
		== 0)
	{
		// here_doc routine
		/*
			./pipex here_doc LIMITER cmd cmd1 file
			cmd << LIMITER | cmd1 >> file
		*/
		return (here_doc(argc, argv, envp));
	}
	else
	{
		// multipipe
		/*
			./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
			< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2
		*/
		printf("multi-pipe\n");
		// return (multipipe(argc, argv, envp));
	}
	return (0);
}

