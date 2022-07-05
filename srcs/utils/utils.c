/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:10:59 by jim               #+#    #+#             */
/*   Updated: 2022/07/05 19:55:25 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

/*
	gnu bash
	name 기준
	name
	A word consisting solely of letters, numbers, and underscores,
	and beginning with a letter or underscore.
	Names are used as shell variable and function names.
	Also referred to as an identifier.

	bash: export: `2': not a valid identifier
*/
static int	check_start_of_name(char ch)
{
	if (ft_is_alpha(ch) || ch == '_')
		return (1);
	return (0);
}

int	check_valid_name(char *str)
{
	size_t	idx;

	idx = 0;
	if (check_start_of_name(str[idx]) == 0)
		return (0);
	idx++;
	while (str[idx])
	{
		if (ft_is_alpha(str[idx]) == 0 \
			|| ft_is_digit(str[idx]) == 0 \
			|| str[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
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

int	is_whitespace(char const ch)
{
	if (ch == ' ' || ch == '\t')
		return (1);
	return (0);
}
