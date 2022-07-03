/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:23 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 16:25:48 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <unistd.h>
#include <stdlib.h>
/*
	- exit status를 여기서 처리할지
		exit_cmd 빌트인 함수를 이용할지는 추가적인 고민필요.
*/

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
	write(STDERR_FILENO, &"\n", 1);
}

/*
	- exit status
	char로 캐스팅해서 넘겨주었을때 정상처리되는지 확인
	exit()함수에서!!
*/
void	error_handler(char *cmd, char *argv, char *msg, char exit_status)
{
	print_error(SHELL_NAME, cmd, argv, msg);
	exit(exit_status);
}
