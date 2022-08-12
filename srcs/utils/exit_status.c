/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:06:09 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 18:17:03 by jim              ###   ########.fr       */
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

void	update_exit_status(int status, t_list *org_list)
{
	if (status < 0)
	{
		free_command_list(org_list);
		status = 2;
	}
	*(get_exit_status()) = status;
}
