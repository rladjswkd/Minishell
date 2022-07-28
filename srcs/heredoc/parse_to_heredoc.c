/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:01:34 by jim               #+#    #+#             */
/*   Updated: 2022/07/28 23:42:04 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include "linked_list.h"
#include "lexer.h"
#include "redirect.h"
#include "heredoc.h"
//debug
#include <stdio.h>
#include <unistd.h>

static int	heredoc_input_processing(t_list **redirect_list)
{
	t_list	*redirect_node;
	t_list	*heredoc_word_node;
	int		heredoc_fd;

	redirect_node = *redirect_list;
	while (redirect_node && redirect_node->next)
	{
		if (get_token(redirect_node)->types & TOKEN_HEREDOC)
		{
			heredoc_word_node = redirect_node->next;
			heredoc_fd = heredoc_routine(get_token(heredoc_word_node)->data);
			if (heredoc_fd < 0)
				return (-1);
			get_token(heredoc_word_node)->heredoc_fd = heredoc_fd;
		}
		redirect_node = redirect_node->next->next;
	}
	if (redirect_node)
		return (-1);
	return (1);
}

static int	test_heredoc_fd(t_list **redirect_list)
{
	t_list	*redirect_node;
	t_list	*heredoc_word_node;
	// test
	int    read_size;
	char   buf[1152];

	redirect_node = *redirect_list;
	while (redirect_node && redirect_node->next)
	{
		if (get_token(redirect_node)->types & TOKEN_HEREDOC)
		{
			heredoc_word_node = redirect_node->next;
			// get_token(heredoc_word_node)->heredoc_fd = heredoc_fd;
			read(get_token(heredoc_word_node)->heredoc_fd, buf, 1152);
			printf("buf in test_heredoc_hd() : %s\n", buf);
		}
		redirect_node = redirect_node->next->next;
	}
	if (redirect_node)
		return (-1);
	return (1);
}

int	parse_to_heredoc(t_list *parse_list)
{
	t_list	*parse_node;
	t_list	*redirect_list;

	if (parse_list == NULL)
		return (-1);
	parse_node = parse_list;
	while (parse_node)
	{
		if (get_command_type(parse_node) == SIMPLE_NORMAL)
		{
			redirect_list = get_simple(parse_node)->redirs;
			if (heredoc_input_processing(&redirect_list) < 0)
				return (-1);
			parse_node = parse_node->next;
		}
		else if (get_command_type(parse_node) == COMPOUND_PIPELINE \
				|| get_command_type(parse_node) == COMPOUND_SUBSHELL)
			parse_node = get_compound(parse_node)->list;
	}
	return (1);
}
