/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:10:59 by jim               #+#    #+#             */
/*   Updated: 2022/08/16 14:16:17 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

/*
	gnu bash
	name 기준
	name
	A word consisting solely of letters, numbers, and underscores,
	and beginning with a letter or underscore.
	Names are used as shell variable and function names.
	Also referred to as an identifier.
*/

void	safe_free(char	**char_pptr)
{
	free(*char_pptr);
	*char_pptr = NULL;
}

int	free_key_value(char **key, char **value)
{
	free(*key);
	*key = NULL;
	free(*value);
	*value = NULL;
	return (-1);
}

int	split_key_value(char *envp_element, char **key, char **value)
{
	int	delimiter_posi;

	delimiter_posi = ft_strchr(envp_element, '=');
	if (delimiter_posi < 0)
	{
		*key = ft_strdup(envp_element);
		*value = NULL;
		if (*key == NULL)
			return (-1);
	}
	else
	{
		*key = ft_strndup(envp_element, delimiter_posi);
		if (*key == NULL)
			return (-1);
		*value = ft_strndup(&(envp_element[delimiter_posi + 1]), \
						ft_strlen(envp_element) - (delimiter_posi + 1));
		if (*value == NULL)
		{
			free_key_value(key, NULL);
			return (-1);
		}
	}
	return (0);
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

int	reset_in_out_fd(int io_backup[2])
{
	if (dup2(io_backup[0], STDIN_FILENO) < 0
		|| dup2(io_backup[1], STDOUT_FILENO) < 0)
		return (-1);
	return (0);
}
