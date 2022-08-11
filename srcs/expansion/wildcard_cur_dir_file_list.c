/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_cur_dir_file_list.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:54:27 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 15:36:19 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"

/*
  매칭되는 것이 없다면 literal로 취급
  *만 들어오는 경우 현재 디렉토리에 있는 file or directory들을 넘겨준다.
  .*이 있는 경우에만 .을 가져온다
  *.* (총  2자 이상이야어햔다.   .으로 시작하는 것은 포함되지 않으며, .으로 끝나는건 가능하다.)
  pattern은 별도 함수에서 매칭시킨다.
  매칭된 것은 연결리스트로 준다?
  $> cat < a*
	minishell: ambiguous redirection
	$> cat < ab*
	abab
*/
static int	get_alloc_size(void)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	char			buf[PATH_MAX];
	int				size;

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
		return (-1);
	file = readdir(dir_ptr);
	size = 0;
	while (file != NULL)
	{
		file = readdir(dir_ptr);
		size++;
	}
	closedir(dir_ptr);
	return (size);
}

static char	**alloc_word_list(void)
{
	int		alloc_size;
	char	**word_list;
	int		idx;

	alloc_size = get_alloc_size() + 1;
	word_list = (char **)malloc(sizeof(char *) * alloc_size);
	if (word_list == NULL)
		return (NULL);
	idx = 0;
	while (idx < alloc_size)
	{
		word_list[idx] = NULL;
		idx++;
	}
	return (word_list);
}

static int	copy_cur_dir_file_list(DIR *dir_ptr, char ***cur_dir_file_list)
{
	struct dirent	*file;
	int			idx;

	if (dir_ptr == NULL)
	{
		free_list(cur_dir_file_list);
		return (-1);
	}
	file = readdir(dir_ptr);
	idx = 0;
	while (file != NULL)
	{
		(*cur_dir_file_list)[idx] = ft_strdup(file->d_name);
		if ((*cur_dir_file_list)[idx] == NULL)
		{
			free_list(cur_dir_file_list);
			return (-1);
		}
		file = readdir(dir_ptr);
		idx++;
	}
	(*cur_dir_file_list)[idx] = NULL;
	return (0);
}

char	**get_cur_dir_file_list(void)
{
	char	**cur_dir_file_list;
	DIR		*dir_ptr;
	char	buf[PATH_MAX];
	int		ret;

	cur_dir_file_list = alloc_word_list();
	if (cur_dir_file_list == NULL)
		return (NULL);
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (NULL);
	dir_ptr = opendir(buf);
	ret = copy_cur_dir_file_list(dir_ptr, &cur_dir_file_list);
	closedir(dir_ptr);
	if (ret < 0)
		return (NULL);
	return (cur_dir_file_list);
}
