/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:10:59 by jim               #+#    #+#             */
/*   Updated: 2022/06/21 22:28:15 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include "utils.h"

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

size_t	max_nonnegative(char const *s1, char const *s2)
{
	size_t	s1_size;
	size_t	s2_size;

	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	if (s1_size > s2_size)
		return (s1_size);
	return (s2_size);
}
