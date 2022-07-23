/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:08:25 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 09:43:17 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "heredoc.h"
#include "utils.h"
#include "linked_list.h"
#include "redirect.h"

//계속 return시킬 것 아니라면 exit한다.
static int	free_and_close(char *file_name, int tmp_file_fd, char *read_str)
{
	unlink(file_name);
	safe_free(&file_name);
	safe_free(&read_str);
	if (close(tmp_file_fd) < 0)
		return (-1);
	return (1);
}

static int	get_readline(char *file_name, int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;
	char	*with_newline;

	while (1)
	{
		read_str = readline("$>");
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		with_newline = ft_strjoin(read_str, "\n");
		if (with_newline == NULL)
		{
			safe_free(&read_str);
			return (-1);
		}
		safe_free(&read_str);
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

	open_fd = file_open(FILE_READ, file_name);
	if (open_fd < 0)
		return (-1);
	if (unlink(file_name) < 0)
		return (-1);
	safe_free(&file_name);
	return (open_fd);
}

int	heredoc_routine(char *heredoc_word)
{
	int		tmp_file_fd;
	char	*file_name;
	char	buf[4242 + 1]; // should be changed

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

int	heredoc_fd_to_list(t_list *list, int fd)
{
	t_list			*cur_node;
	t_heredoc_node	*heredoc_node;

	if (fd < 0)
	{
		free_linked_list(&list);
		return (-1);
	}
	while (list->next)
		list = list->next;
	list->next = create_list();
	cur_node = list->next;
	if (cur_node == NULL)
	{
		free_linked_list(&list);
		return (-1);
	}
	heredoc_node = (t_heredoc_node *)malloc(sizeof(t_heredoc_node));
	if (heredoc_node == NULL)
	{
		free_linked_list(&list);
		return (-1);
	}
	heredoc_node->fd = fd;
	cur_node->node = (t_heredoc_node *)heredoc_node;
	return (0);
}
