/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:48:23 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 21:25:41 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdlib.h>

char	*ft_strndup(const char *s1, int len)
{
	char	*dest;
	size_t	idx;

	if (s1 == NULL || len < 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	idx = 0;
	while (s1[idx] && len > idx)
	{
		dest[idx] = s1[idx];
		idx++;
	}
	dest[idx] = 0;
	return (dest);
}
