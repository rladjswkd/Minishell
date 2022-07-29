/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:06:09 by jim               #+#    #+#             */
/*   Updated: 2022/07/29 11:38:57 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	*get_exit_status()
{
	static int	exit_status;

	return (&exit_status);
}

int	update_exit_status(int status)
{
	*(get_exit_status()) = status;
}