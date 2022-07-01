/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:12 by jim               #+#    #+#             */
/*   Updated: 2022/07/01 21:09:38 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

# define LONGLONG_MAX_STR "9223372036854775807"
# define LONGLONG_MIN_STR "-9223372036854775808"
# define SHELL_NAME "minishell"
#include <unistd.h>
// #include "builtin.h"
// #include "utils.h"

#include <stdio.h>
/*
	- long long 넘어가는 것은 어떻게할 것인가?q
	- 애초에 문자열인 케이스는 어떻게 파악할것인가?
	- 기존 atol, atoi를 이용해서 확인한다.
	- exit z 2 3 	
*/
/* 
 * positive negative 둘'다 확인해야한다.
 * sign부터 확인하며
 * –9223372036854775808 ~ 9223372036854775807
 * 
 */
static long long	ft_atol(char *str, int *num_flag);
size_t	ft_strlen(const char *s);

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

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

int	is_whitespace(char const ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	return (0);
}

int	ft_isnum(char ch)
{
	if ('9' >= ch && ch >= '0')
		return (1);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	idx;

	idx = 0;
	while (s[idx])
		idx++;
	return (idx);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize == 0)
		return (i);
	while ((k < dstsize - 1) && src[k])
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (i);
}

static int	compare_long_long_max(char *str, long long sign)
{
	size_t	boundary_idx;
	size_t	idx;
	char	boundary_num[ft_strlen(LONGLONG_MIN_STR) + 1];

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

static int is_it_over_long_long(char *str, long long sign)
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
		if (ft_isnum(str[idx]) == 0)
		{
			*num_flag = 0;
			break ;
		}
		ret = ret * 10 + str[idx] - '0';
		idx++;
	}
	return ((int)ret);
}
/*
 * exit status는 무엇인가?
 * shell에서 exit 42에서 넘어오는 값을 의미하는가?
 * exit == exit 0 wsl(ubuntu)에서는 바로 종료된다.
 * exit 1이나 다른 값은 정상처리된다.
 * exit character, string의 경우 error 문구발생
 * builtin별로 인자에 대한 처리가 나뉘므로 그에 따른 예외처리 추가적으로 필요
 * long long 으로 
 */


void	exit_cmd(char **status)
{
	int	*num_flag;

	*num_flag = 1;
	printf("*status : %s\n", *status);
	ft_atol(*status, num_flag);
	if (*num_flag == 0)
		print_error(SHELL_NAME, "exit", *status, "numeric argument required");
	printf("num_flag : %d\n", *num_flag);
}

int main(int argc, char **argv)
{
	exit_cmd(&argv[1]);
	return (0);
}