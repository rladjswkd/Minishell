/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:07:43 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 19:50:26 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#include "heredoc.h"
#include "structure_linked_list.h"
#include "utils.h"

static int	check_tmp_file_name(char *file_name)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	char			buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
		return (-1);
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		if (ft_strncmp(file_name, file->d_name, \
						max_nonnegative(file_name, file->d_name)) == 0)
		{
			closedir(dir_ptr);
			return (1);
		}
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (0);
}

static char	*get_tmp_file_name(void)
{
	char	*file_name;
	char	*itoa_num;
	int		num;

	num = 0;
	while (1)
	{
		itoa_num = ft_itoa(num);
		if (itoa_num == NULL)
			return (NULL);
		file_name = ft_strjoin(".heredoc_tmp_file_", itoa_num);
		safe_free(&itoa_num);
		if (file_name == NULL)
			return (NULL);
		if (check_tmp_file_name(file_name) == 0)
			break ;
		safe_free(&file_name);
		num++;
	}
	return (file_name);
}

int	create_heredoc_tmp_file(char **file_name)
{
	int		tmp_file_fd;

	*file_name = get_tmp_file_name();
	if (*file_name == NULL)
		return (-1);
	tmp_file_fd = open(*file_name, O_CREAT | O_WRONLY, 0666);
	if (tmp_file_fd < 0)
	{
		safe_free(file_name);
		return (-1);
	}
	return (tmp_file_fd);
}
