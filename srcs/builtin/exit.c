/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:12 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 16:14:41 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */


#include <stdlib.h>
#include <unistd.h>
#include "utils.h"

/*
	- long long 넘어가는 것은 어떻게할 것인가?
	- 애초에 문자열인 케이스는 어떻게 파악할것인가?
	- 기존 atol, atoi를 이용해서 확인한다.
	-
*/
static long long	ft_atol(char *str)
{
	long long	ret;
	size_t		idx;

	ret = 0;
	idx = 0;
	while (str[idx])
	{
		idx++;
	}
	return (0);
}
/*
 * exit status는 무엇인가?
 * shell에서 exit 42에서 넘어오는 값을 의미하는가?
 * exit == exit 0 wsl(ubuntu)에서는 바로 종료된다.
 * exit 1이나 다른 값은 정상처리된다.
 * exit character, string의 경우 error 문구발생
 * builtin별로 인자에 대한 처리가 나뉘므로 그에 따른 예외처리 추가적으로 필요
 * 인자가 여러개이면 too many argument로 처리한다.
 */
void	exit_cmd(char **status)
{
		
	printf("exit\n");
	// if (status <= (__LONG_LONG_MAX__) && status <= INT64_MIN)
	// 	ft_putstr_fd("numeric argument required", STDERR_FILENO);
	// exit((char)status);
	;
}
