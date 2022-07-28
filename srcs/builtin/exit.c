/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:12 by jim               #+#    #+#             */
/*   Updated: 2022/07/28 19:21:12 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "builtin.h"
#include "utils.h"
#include "ft_error.h"

static int	compare_long_long_max(char *str, long long sign)
{
	size_t	boundary_idx;
	size_t	idx;
	char	boundary_num[21];

	boundary_idx = 0;
	if (sign > 0)
		ft_strlcpy(boundary_num, LONGLONG_MAX_STR, \
					ft_strlen(LONGLONG_MAX_STR) + 1);
	else
	{
		ft_strlcpy(boundary_num, LONGLONG_MIN_STR, \
					ft_strlen(LONGLONG_MIN_STR) + 1);
		boundary_idx = 1;
	}
	idx = 0;
	while (str[idx])
	{
		if (boundary_num[boundary_idx] < str[idx])
			return (1);
		boundary_idx++;
		idx++;
	}
	return (0);
}

static int	is_it_over_long_long(char *str, long long sign)
{
	size_t	len;
	size_t	max_len;

	len = ft_strlen(str);
	max_len = ft_strlen(LONGLONG_MAX_STR);
	if (sign < 0)
	{
		len += 1;
		max_len += 1;
	}
	if (len > max_len)
		return (1);
	else if (len == max_len)
		return (compare_long_long_max(str, sign));
	return (0);
}

static long long	ft_atol(char *str, int *num_flag)
{
	long long	ret;
	long long	sign;
	size_t		idx;

	ret = 0;
	idx = 0;
	sign = 1;
	while (is_whitespace(str[idx]))
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
		if (str[idx] == '-')
			sign = -1;
	if (is_it_over_long_long(&str[idx], sign))
		*num_flag = 0;
	while (str[idx] && *num_flag)
	{
		if (ft_is_digit(str[idx]) == 0)
		{
			*num_flag = 0;
			break ;
		}
		ret = ret * 10 + str[idx] - '0';
		idx++;
	}
	return (ret);
}

static int	is_more_than_one(char **status)
{
	if (*status != NULL && *(status + 1) != NULL)
		return (1);
	return (0);
}

/*
 * 고려사항
 * exit 인자가 없는 경우
 * 추후 연결리스트 사용 에정
 * 인자에 대해서 포인터를 받고 사용 이후에는 free시킨다.  dangling 포함.
 * too many arguments의 경우 exit status 1이 나온다 하지만 동작은 하지말아야한다.
 * exit status를 바꾼다?
 */

void	exit_cmd(char **status, int is_child)
{
	int		num_flag;
	char	exit_status;

	num_flag = 1;
	if (*status)
		exit_status = (char)ft_atol(*status, &num_flag);
	if (*status == NULL)
		exit_status = (char)*get_exit_status();
	else if (num_flag == 0) 
	{
		print_error(SHELL_NAME, "exit", *status, \
					"numeric argument required");
		exit_status = (char)255;
	}
	else if (is_more_than_one(status))
	{
		print_error(SHELL_NAME, "exit", NULL, "too many arguments");
		exit_status = (char)1;
		return ;
	}
	if (num_flag && is_child == FALSE)
		ft_putstr_fd("exit\n", STDOUT_FILENO);
	exit(exit_status);
}
