/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:14:21 by jim               #+#    #+#             */
/*   Updated: 2022/07/06 14:38:59 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

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
			&& ft_is_digit(str[idx]) == 0 \
			&& str[idx] != '_')
			return (0);
		idx++;
	}
	return (1);
}
