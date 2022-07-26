/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:17:37 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 19:09:16 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "linked_list.h"
#include "heredoc.h"
#include "lexer.h"
#include "redirect.h"
#include "ft_error.h"


static int	safe_dup2(int from, int to)
{
	if (dup2(from, to) < 0)
		return (-1);
	if (close(from) < 0)
		return (-1);
	return (0);
}

/* -ing 
int	heredoc_redirect(t_list *heredoc_list)
{
	int		file_fd;
	int		status;
	t_list	*tmp_node;

	file_fd = ((t_heredoc_node *)(heredoc_list->next->node))->fd;
	tmp_node = heredoc_list->next->node;
	heredoc_list->next = tmp_node->next;
	status = safe_dup2(file_fd, STDIN_FILENO);
	return (status);
}
*/
int	heredoc_redirect(t_list *heredoc_list)
{
	t_heredoc_node	*heredoc_node;
	t_list			*tmp_node;
	int				heredoc_tmp_file_fd;
	int				status;

	if (heredoc_list == NULL || heredoc_list->next == NULL)
		return (-1);
	heredoc_node = heredoc_list->next->node;
	heredoc_tmp_file_fd = heredoc_node->fd;
	tmp_node = heredoc_list->next;
	if (heredoc_list && heredoc_list->next)
		heredoc_list->next = heredoc_list->next->next;
	free(tmp_node);
	status = safe_dup2(heredoc_tmp_file_fd, STDIN_FILENO);
	return (status);
}

int	input_redirect(char *file_name)
{
	int	file_fd;
	int	status;

	file_fd = open(file_name, O_RDONLY, 0666);
	if (file_fd == -1)
		return (-1);
	status = safe_dup2(file_fd, STDIN_FILENO);
	return (status);
}

int	output_redirect(char *file_name)
{
	int	file_fd;
	int	status;

	file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (file_fd == -1)
		return (-1);
	status = safe_dup2(file_fd, STDOUT_FILENO);
	return (status);
}

int	append_redirect(char *file_name)
{
	int	file_fd;
	int	status;

	file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0666);
	if (file_fd == -1)
		return (-1);
	status = safe_dup2(file_fd, STDOUT_FILENO);
	return (status);
}
