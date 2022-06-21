/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 14:27:14 by jim               #+#    #+#             */
/*   Updated: 2022/06/21 18:24:43 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include "utils.h"

size_t	ft_strlen(char const *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char const *s, int fd)
{
	// if (s == NULL)
	// 	return ;
	// NULL check 하는게 맞는가?
	write(fd, s, ft_strlen(s));
}

void	print_newline_fd(int fd)
{
	write(fd, &"\n", 1);
}
