/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:12 by jim               #+#    #+#             */
/*   Updated: 2022/06/30 20:41:26 by jim              ###   ########seoul.kr  */
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
 * exit 값이 없으면 0으로 종료된다.
 * exit 인자가 여러개인 경우
 * 첫번째 값이 문자이면 exit(255)로 처리된다.
 * 첫번쨰 값이 숫자이면서 인자가 여러개면 too many argument처리된다.
 * 1개 값만 있고 숫자이면 그대로 들어가서 8bit로 캐스팅된다.
 */
void	exit_cmd(const char **status)
{

	ft_putstr_fd("exit\n", STDOUT_FILENO);
	// if (status <= (__LONG_LONG_MAX__) && status <= INT64_MIN)
	// 	ft_putstr_fd("numeric argument required", STDERR_FILENO);
	exit(atoi(*status[0]));
}
