/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   construct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:13 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:14 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	malloc_wrapper(size_t size, void **ptr)
{
	size_t	i;
	char	*cptr;

	*ptr = malloc(size);
	if (!(*ptr))
		return (0);
	i = 0;
	cptr = (char *)(*ptr);
	while (i < size)
		cptr[i++] = 0;
	return (1);
}
