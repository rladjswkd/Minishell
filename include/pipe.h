/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 20:30:55 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_pipe_type
{
	READ_END,
	WRITE_END,
}			t_pipe_type;

typedef struct s_pipe_info
{
	int	in;
	int	out;
}				t_pipe_info;

typedef enum e_bool
{
	FALSE,
	TRUE,
}			t_bool;

typedef enum e_sys_return
{
	SUCCESS,
	ERROR,
}			t_sys_return;
