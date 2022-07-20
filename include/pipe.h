/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/07/20 20:26:24 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_pipe_type
{
	READ_END,
	WRITE_END,
}			t_pipe_type;

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

typedef struct s_fd_info
{
	int		fd[2][2];
	int		spin_flag;
}				t_fd_info;

int	connect_to_prev(int fd[2]);
int	connect_to_next(int fd[2]);
int	is_exist_prev_pipe(t_list *start_node, t_list *cur_node);
int	is_exist_next_pipe(t_list *cur_node);