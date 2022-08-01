/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:06:09 by jim               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 08:16:59 by jim              ###   ########.fr       */
=======
/*   Updated: 2022/08/01 13:50:35 by jim              ###   ########.fr       */
>>>>>>> c885569a85f37038920567a5b0483fffaa655a79
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "env_list.h"

int	*get_exit_status()
{
	static int	exit_status;

	return (&exit_status);
}

<<<<<<< HEAD
int	update_exit_status(int status, t_list *parse_list)
{
	if (status < 0)
	{
		// delete_list(&parse_list);
=======
int	update_exit_status(int status, t_list *org_list)
{
	if (status < 0)
	{
		// delete_env_list(&env_list);
		// delete_list(&org_list)
>>>>>>> c885569a85f37038920567a5b0483fffaa655a79
		status = 2;
	}
	*(get_exit_status()) = status;
}