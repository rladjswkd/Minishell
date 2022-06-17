/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:18:21 by jim               #+#    #+#             */
/*   Updated: 2022/06/14 15:46:10 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
	./pipex here_doc LIMITER cmd1 cmd2 file
	cmd1 << LIMITER | cmd2 >> file
	./pipex here_doc LIMITER cat cat file
*/

typedef enum e_redirection_flag
{
	NONE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}				t_redirection_flag;

typedef enum e_file_flag
{
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
	FILE_RDWR,
}				t_file_flag;

typedef enum e_flag
{
	ERROR = -1,
	SUCCESS = 0,
	FAIL = 1,
}				t_e_flag;

typedef enum e_pipe_flag
{
	READ_END,
	WRITE_END,
}			t_pipe_flag;

typedef struct s_execute_info
{
	char				*cmd;
	char				**envp;
	char				pipe_fd[2];
	t_redirection_flag	redirection_flag;
	char				*heredoc_word;
	char				*file_name;
}				t_execute_info;

// typedef struct s_here_doc_init
// {
// 	cmd

// }				t_here_doc_init;

#endif
