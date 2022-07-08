/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:23 by jim               #+#    #+#             */
/*   Updated: 2022/07/06 19:42:24 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include "ft_error.h"
#include <unistd.h>
#include <stdlib.h>

void	print_error(char *shell_name, char *cmd, char *argv, char *msg)
{
	ft_putstr_fd(shell_name, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	if (cmd != NULL)
	{
		ft_putstr_fd(cmd, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (argv != NULL)
	{
		ft_putstr_fd(argv, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (msg != NULL)
		ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	error_handler(char *cmd, char *argv, char *msg, char exit_status)
{
	print_error(SHELL_NAME, cmd, argv, msg);
	*(get_exit_status()) = exit_status;
}
