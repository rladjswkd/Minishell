/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:06:09 by jim               #+#    #+#             */
/*   Updated: 2022/07/30 17:35:03 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "env_list.h"

int	*get_exit_status()
{
	static int	exit_status;

	return (&exit_status);
}

int	update_exit_status(int status, t_env_list *env_list, t_list *parse_list)
{
	if (status < 0)
	{
		delete_env_list(&env_list);
		// delete_list(&parse_list)
		status = 2;
	}
	*(get_exit_status()) = status;
}