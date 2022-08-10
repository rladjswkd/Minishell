/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:14:21 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 15:33:41 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	check_start_of_variable(char ch)
{
	if (ft_is_alpha(ch) || ch == '_')
		return (1);
	return (0);
}

int	check_mid_of_variable(char ch)
{
	if (ft_is_alpha(ch) == 0 \
		&& ft_is_digit(ch) == 0 \
		&& ch != '_')
		return (0);
	return (1);
}

int	check_valid_variable(char *str)
{
	size_t	idx;

	idx = 0;
	if (check_start_of_variable(str[idx]) == 0)
		return (0);
	idx++;
	while (str[idx])
	{
		if (check_mid_of_variable(str[idx]) == 0)
			return (0);
		idx++;
	}
	return (1);
}
