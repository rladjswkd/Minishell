/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:08:25 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:59:12 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>  // readline이전에 stdio를 include해야한다 왜?
#include <readline/readline.h>
#include "token.h"
#include "heredoc.h"
#include "expansion.h"
#include "utils.h"
//계속 return시킬 것 아니라면 exit한다.
// unlink 실패해도 free해야한다. 어쨌든, -1 return하므로 error 체크하지 않는다.
static int	free_and_close(char *file_name, int tmp_file_fd, char *read_str)
{
	unlink(file_name);
	safe_free(&file_name);
	safe_free(&read_str);
	close(tmp_file_fd);
	return (-1);
}

static int	get_readline(char *file_name, int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;
	char	*with_newline;

	while (1)
	{
		read_str = readline("$>");
		if (read_str == NULL)
			return (-1);
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		with_newline = ft_strjoin(read_str, "\n");
		safe_free(&read_str);
		if (with_newline == NULL)
			return (-1);
		if (write(tmp_file_fd, with_newline, ft_strlen(with_newline)) < 0)
			return (free_and_close(file_name, tmp_file_fd, read_str));
		safe_free(&with_newline);
	}
	close(tmp_file_fd);
	return (1);
}

static int	get_tmp_file_fd(char *file_name)
{
	int	open_fd;

	open_fd = open(file_name, O_RDONLY, 0666);
	if (open_fd < 0)
		return (-1);
	if (unlink(file_name) < 0)
		return (-1);
	safe_free(&file_name);
	return (open_fd);
}

int	concat_heredoc_word_list(t_list *list)
{
	if (get_token(list)->types & TOKEN_CONCAT
		&& list->next)
	{
		if (concat_list_in_condition(list) < 0)
			return (-1);
	}
	return (0);
}

int	heredoc_routine(char *heredoc_word)
{
	int		tmp_file_fd;
	char	*file_name;

	tmp_file_fd = create_heredoc_tmp_file(&file_name);
	if (tmp_file_fd < 0)
		return (-1);
	if (get_readline(file_name, tmp_file_fd, heredoc_word) < 0)
		return (-1);
	tmp_file_fd = get_tmp_file_fd(file_name);
	if (tmp_file_fd < 0)
		return (-1);
	return (tmp_file_fd);
}
