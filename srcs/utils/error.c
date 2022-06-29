/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:23 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 15:48:19 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "utils.h"
#include <unistd.h>
/*
	- exit status를 여기서 처리할지
		exit_cmd 빌트인 함수를 이용할지는 추가적인 고민필요.
*/

/*
	bash: cd: 13: No such file or directory
	jake@DESKTOP-39VE82R:/mnt/d/42$ export aaaa==
	jake@DESKTOP-39VE82R:/mnt/d/42$ export =aa
	bash: export: `=aa': not a valid identifier
	- error msg 조합에 대한 고려
	호출하는 입장에서의 줄 길이와 에러 메시지를 어떻게 전달하는게 효율적인가?
*/
char	*combine_error_msg(char *shell_name, char *cmd, char *argv, char *msg)
{
	char	*err_msg;
	// const	char *;
	size_t	alloc_size;
	
}

int		print_error(char *msg)
{
	ft_putstr_fd(STDERR_FILENO, msg);
}

void	error_handler(char *error_statement, int exit_status)
{
	exit_cmd(exit_status);
}
