/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_to_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 21:01:34 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 11:01:50 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include "linked_list.h"
#include "lexer.h"
#include "redirect.h"
#include "heredoc.h"

static int	heredoc_input_processing(t_list *redirect_list, \
										t_list *heredoc_list)
{
	t_list  *redirect_node;
	t_list	*heredoc_word_node;

	redirect_node = redirect_list;
	while (redirect_node && redirect_node->next)
	{
		if (get_token(redirect_node)->types & TOKEN_HEREDOC)
		{
			heredoc_word_node = redirect_node->next;
			if (heredoc_fd_to_list(heredoc_list, \
				heredoc_routine(get_token(heredoc_word_node)->data)) < 0)
				return (ENOMEM);
		}
		redirect_node = redirect_node->next->next;
	}
	if (redirect_node)
		return (-1);
	return (1);
}

int parse_to_heredoc(t_list *parse_list, t_list *heredoc_list)
{
	t_list  *parse_node;
	t_list	*redirect_list;

	parse_node = parse_list;
	while (parse_node)
	{
		if (get_command_type(parse_node) == SIMPLE_NORMAL)
		{
			redirect_list = get_simple(parse_node)->redirs;
			heredoc_input_processing(redirect_list, heredoc_list);
		}
		parse_node = parse_list->next;
	}
	
	
}