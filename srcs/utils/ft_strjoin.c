/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:35:18 by jim               #+#    #+#             */
/*   Updated: 2022/06/18 18:35:27 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*dst;
	size_t	dstsize;

	dstsize = ft_strlen(s1) + ft_strlen(s2) + 1;
	dst = (char *)malloc(sizeof(char) * (dstsize));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, ft_strlen(s1) + 1);
	ft_strlcat(dst, s2, dstsize);
	return (dst);
}
