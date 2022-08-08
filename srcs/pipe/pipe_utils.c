/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/20 19:25:31 by jim               #+#    #+#             */
/*   Updated: 2022/07/24 21:31:41 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "linked_list.h"
#include "pipe.h"
// debug
#include <stdlib.h>
#include "utils.h"


size_t	count_digits(int n)
{
	size_t	expo;

	expo = 0;
	if (n < 0)
	{
		n *= -1;
		expo++;
	}
	while (n)
	{
		expo++;
		n /= 10;
	}
	return (expo);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	char	*to_be_s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	digits = count_digits(n);
	to_be_s = (char *)malloc(sizeof(char) * (digits + 1));
	if (!to_be_s)
		return (0);
	if (n < 0)
	{
		n = -n;
		to_be_s[0] = '-';
	}
	to_be_s[digits] = '\0';
	digits--;
	while (n)
	{
		to_be_s[digits] = (n % 10) + '0';
		digits--;
		n /= 10;
	}
	return (to_be_s);
}

int	connect_to_prev(int fd[2])
{
	if (dup2(fd[READ_END], STDIN_FILENO) < 0)
		return (-1);
	if (close(fd[READ_END]) < 0)
		return (-1);
	return (1);
}

/*
    이미 닫힌 fd를 close할 경우 error가 발생할 수 있다.
    call by value여도 상관없다.
    close()에는 리터럴한 값으로 가서
    그 값이 indexing되어서 close이후에 file descritor자원이 반환되므로 그러하다.
*/
int	connect_to_next(int fd[2])
{
	char	*pipe_fd[2];

	// ft_putstr_fd("connect_to_next(int *pipe_fd) : ", STDERR_FILENO);
	if (close(fd[READ_END]) < 0)
		return (-1);
	if (dup2(fd[WRITE_END], STDOUT_FILENO) < 0)
		return (-1);
	if (close(fd[WRITE_END]) < 0)
		return (-1);
	// pipe_fd[0] = ft_itoa(fd[READ_END]);
	// pipe_fd[1] = ft_itoa(fd[WRITE_END]);
	// ft_putstr_fd(pipe_fd[0], STDERR_FILENO);
	// ft_putstr_fd("  ", STDERR_FILENO);
	// ft_putstr_fd(pipe_fd[1], STDERR_FILENO);
	// ft_putstr_fd("\n", STDERR_FILENO);
	return (1);
}

int	is_exist_prev_pipe(t_list *start_node, t_list *cur_node)
{
	if (start_node != cur_node)
		return (1);
	return (0);
}

int	is_exist_next_pipe(t_list *cur_node)
{
	if (cur_node->next)
		return (1);
	return (0);
}
