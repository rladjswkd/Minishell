/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:37:43 by jim               #+#    #+#             */
/*   Updated: 2022/07/04 16:28:08 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	size_t			i;

	i = 0;
	while (i++ < n)
	{
		c1 = *s1++;
		c2 = *s2++;
		if (c1 != c2)
		{
			if (c1 < c2)
				return (-1);
			else
				return (1);
		}
		if (!c1)
			break ;
	}
	return (0);
}
