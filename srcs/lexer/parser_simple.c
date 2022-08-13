/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:33 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/12 20:21:33 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "linked_list.h"
#include "command_simple.h"
#include "destruct.h"
#include "heredoc.h"

static int	find_simple_type(t_list *token_list)
{
	int	type;

	if (!token_list)
		return (0);
	type = get_token_type(token_list);
	if (type & (TOKEN_NORMAL | TOKEN_REDIR))
		return (SIMPLE_NORMAL);
	else if (type & TOKEN_PIPE)
		return (SIMPLE_PIPE);
	else if (type & TOKEN_LBRACKET)
		return (SIMPLE_LBRACKET);
	else if (type & TOKEN_RBRACKET)
		return (SIMPLE_RBRACKET);
	else if (type & TOKEN_LOGICAL)
	{
		if ((get_token(token_list)->data)[0] == CHAR_AMPERSAND)
			return (SIMPLE_AND);
		return (SIMPLE_OR);
	}
	return (0);
}

static void	parse_args_redirs(t_list *parsed, t_list **list)
{
	t_simple	*simple;
	t_list		*next;

	simple = get_simple(parsed);
	while (find_simple_type(*list) & SIMPLE_NORMAL)
	{
		next = (*list)->next;
		if (get_token_type(*list) & (TOKEN_REDIR | TOKEN_REDIRARG))
		{
			if (get_token_type(*list) & TOKEN_HEREDOC)
			{
				if (concat_heredoc_word_list((*list)->next))
					return ;
				get_token((*list)->next)->heredoc_fd = heredoc_routine(
					get_token((*list)->next)->data);
				if (get_token((*list)->next)->heredoc_fd < 0)
					return ;
			}
			append_back(&(simple->redirs), *list);
		}
		else
			append_back(&(simple->args), *list);
		(*list)->next = 0;
		*list = next;
	}
}

int	parse_simple(t_list *token_list, t_list *header)
{
	int		type;
	t_list	*token_ptr;

	while (token_list)
	{
		type = find_simple_type(token_list);
		if (!create_command(&(header->next), type))
			return (0);
		if (type & SIMPLE_NORMAL)
			parse_args_redirs(header->next, &token_list);
		else
		{
			token_ptr = token_list;
			token_list = token_list->next;
			free_token(token_ptr);
		}
		header = header->next;
	}
	return (1);
}
