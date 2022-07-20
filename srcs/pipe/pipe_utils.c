/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:25:31 by jim               #+#    #+#             */
/*   Updated: 2022/07/20 19:56:50 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "linked_list.h"
#include "pipe.h"

int	connect_to_prev(int fd[2])
{
	if (dup2(fd[READ_END], STDIN_FILENO) < 0)
		return (-1);
	if (close(fd[READ_END]) < 0)
		return (-1);
	return (1);
}

/*
    이미 닫힌 fd를 close할 경우 error가 발생할 수 있다.
    call by value여도 상관없다.
    close()에는 리터럴한 값으로 가서
    그 값이 indexing되어서 close이후에 file descritor자원이 반환되므로 그러하다.
*/
int	connect_to_next(int fd[2])
{
	if (close(fd[READ_END]) < 0)
		return (-1);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		return (-1);
	if (close(fd[WRITE_END]) < 0)
		return (-1);
	return (1);
}

int	is_exist_prev_pipe(t_list *start_node, t_list *cur_node)
{
	if (start_node != cur_node)
		return (1);
	return (0);
}

int	is_exist_next_pipe(t_list *cur_node)
{
	if (cur_node->next)
		return (1);
	return (0);
}
