/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:34:03 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 15:34:08 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	org_dstsize;

	i = ft_strlen(dst);
	j = 0;
	org_dstsize = i;
	while (src && src[j] != '\0' && (org_dstsize + j + 1 < dstsize))
		dst[i++] = src[j++];
	if (org_dstsize < dstsize)
		dst[i] = '\0';
	while (src && src[j] != '\0')
		j++;
	if (dstsize < org_dstsize)
		return (j + dstsize);
	else
		return (j + org_dstsize);
}
