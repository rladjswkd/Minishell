/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:07:43 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 10:29:18 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>

// #include "redirect.h"

int	check_tmp_file_name(char *file_name)
{
	DIR				*dir_ptr = NULL;
	struct dirent	*file    = NULL;
	char			buf[PATH_MAX];

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	if((dir_ptr = opendir(buf)) == NULL)
		return -1;
	while((file = readdir(dir_ptr)) != NULL) 
	{
		if (ft_strncmp(file_name, file->d_name, \
						max_nonnegative(file_name, file->d_name)) == 0)
			return (1);
	}
	closedir(dir_ptr);
	return (0);
}

static char *get_tmp_file_name(void)
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

static void	input_to_tmp_file(char *file_name, int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;

	while (1)
	{
		read_str = readline("$>");
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		if (write(tmp_file_fd, read_str, ft_strlen(read_str)) < 0)
			exit(1);
		safe_free(&read_str);
	}
	close(tmp_file_fd);
}

int	create_heredoc_tmp_file(char **file_name)
{
	int		tmp_file_fd;

	*file_name = get_tmp_file_name();
	if (*file_name == NULL)
		return (-1);
	tmp_file_fd = redirection(HERE_DOC, *file_name);
	if (tmp_file_fd < 0)
	{
		safe_free(file_name);
		return (-1);
	}
	return (tmp_file_fd);
}