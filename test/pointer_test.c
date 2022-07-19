/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 11:33:09 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 12:35:49 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void    safe_free(char **str)
{
	free(*str);
	*str = NULL;
}

void    free_str(char *str)
{
	printf("str : %s\n", str);
	safe_free(&str);
	printf("str after free_str : %s\n", str);
}

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && str[len])
		len++;
	return (len);
}

int	main(int argc, char **argv)
{
	char	*alloc_str;
	size_t	idx;
	size_t	str_len;

	str_len = ft_strlen(argv[1]);
	alloc_str = (char *)malloc(sizeof(char) * (str_len + 1));
	if (alloc_str == NULL)
		return (1);
	idx = 0;
	while (idx < str_len)
	{
		alloc_str[idx] = argv[1][idx];
		idx++;
	}
	alloc_str[str_len] = '\0';
	free_str(alloc_str);
	return (0);
}
