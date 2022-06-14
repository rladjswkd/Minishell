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

typedef enum	e_pipe_flag
{
	READ_END,
	WRITE_END,
}				t_pipe_flag;

#endif
