/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:31:11 by jim               #+#    #+#             */
/*   Updated: 2021/12/15 14:36:54 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*save[OPEN_MAX];
	int			newline_idx;
	char		read_str[BUFFER_SIZE + 1];
	int			read_size;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	while (TRUE)
	{
		newline_idx = ft_strchr(save[fd], '\n');
		if (newline_idx >= 0)
			return (get_next_line_from_save(&save[fd], newline_idx));
		read_size = read(fd, read_str, BUFFER_SIZE);
		if (read_size <= 0)
			break ;
		read_str[read_size] = '\0';
		save[fd] = ft_strjoin(save[fd], read_str);
		if (save[fd] == NULL)
			return (NULL);
	}	
	return (return_remain(&save[fd], read_size));
}

char	*return_remain(char **save, int read_size)
{
	char	*ret;

	if (*save == NULL || save == NULL)
		return (NULL);
	ret = NULL;
	if ((ft_strlen(*save) > 0) && read_size == 0)
	{
		ret = ft_strdup(*save);
		if (ret == NULL)
		{
			free(*save);
			*save = NULL;
			return (NULL);
		}
	}
	free(*save);
	*save = NULL;
	return (ret);
}

char	*get_next_line_from_save(char **save, int newline_idx)
{
	char	*next_line;
	char	*tmp;

	next_line = ft_substr(*save, 0, newline_idx + 1);
	if (next_line == NULL)
	{
		free(*save);
		*save = NULL;
		return (NULL);
	}
	tmp = ft_strdup(*save + newline_idx + 1);
	free(*save);
	if (tmp == NULL)
	{
		free(next_line);
		*save = NULL;
		return (NULL);
	}
	*save = tmp;
	return (next_line);
}
