/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:34:25 by jim               #+#    #+#             */
/*   Updated: 2022/06/18 18:34:43 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_gnl_strjoin(char *s1, char *s2)
{
	char	*dst;
	size_t	s1_size;
	size_t	s2_size;

	if (s2 == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		s1 = ft_strdup("");
		if (s1 == NULL)
			return (NULL);
	}
	s1_size = ft_strlen(s1);
	s2_size = ft_strlen(s2);
	dst = (char *)malloc(sizeof(char) * (s1_size + s2_size + 1));
	if (dst == NULL)
	{
		free(s1);
		return (NULL);
	}
	ft_strlcpy(dst, s1, s1_size + 1);
	free(s1);
	ft_strlcat(dst, s2, s1_size + s2_size + 1);
	return (dst);
}
