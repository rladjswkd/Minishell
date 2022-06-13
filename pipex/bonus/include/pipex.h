/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 17:18:21 by jim               #+#    #+#             */
/*   Updated: 2022/06/06 19:40:30 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/*
	./pipex here_doc LIMITER cmd1 cmd2 file
	cmd1 << LIMITER | cmd2 >> file
*/

typedef enum	e_redirection_flag
{
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}				t_redirection_flag;

typedef enum	e_file_flag
{
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
}				t_file_flag;

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

#endif
