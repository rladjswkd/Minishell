/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:07:43 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 17:21:04 by jim              ###   ########seoul.kr  */
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
#include "linked_list.h"
#include "utils.h"

/* */
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
			return (1);
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

/* heredoc_fd_to_list 밖에서 null로 초기화해서 줄것. -1 return시 밖에서 free() */
int	heredoc_fd_to_list(t_list *list, int fd)
{
	t_list			*cur_node;
	t_heredoc_node	*heredoc_node;

	if (fd < 0)
		return (-1);
	while (list->next)
		list = list->next;
	list->next = create_list();
	cur_node = list->next;
	if (cur_node == NULL)
		return (-1);
	heredoc_node = (t_heredoc_node *)malloc(sizeof(t_heredoc_node));
	if (heredoc_node == NULL)
		return (-1); // heredoc_list free!!!
	heredoc_node->fd = fd;
	cur_node->node = (t_heredoc_node *)heredoc_node;
	return (0);
}
