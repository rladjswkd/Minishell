/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:06:09 by jim               #+#    #+#             */
/*   Updated: 2022/08/13 20:56:21 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdlib.h>
#include "structure_linked_list.h"
#include "env_list.h"
#include "destruct.h"

int	handle_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	else
		return (EXIT_FAILURE);
}

int	*get_exit_status(void)
{
	static int	exit_status;

	return (&exit_status);
}

void	update_exit_status(int status)
{
	*(get_exit_status()) = status;
}
