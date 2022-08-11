/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:21 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:56:09 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_linked_list.h"
#include "command_simple.h"
#include "command.h"

int	find_lbracket(t_list *parsed, t_list *rbracket, t_list **lbracket)
{
	int	type;

	*lbracket = 0;
	while (parsed && parsed != rbracket)
	{
		type = get_simple_type(parsed);
		if (type & SIMPLE_LBRACKET)
			*lbracket = parsed;
		if (*lbracket && type & SIMPLE_PIPE)
			*lbracket = 0;
		parsed = parsed->next;
	}
	return (*lbracket != 0);
}

int	find_rbracket(t_list *parsed, t_list **rbracket)
{
	t_list	*cur;

	cur = parsed;
	*rbracket = 0;
	while (cur)
	{
		if (get_simple_type(cur) & SIMPLE_RBRACKET)
		{
			*rbracket = cur;
			return (1);
		}
		cur = cur->next;
	}
	return (0);
}

int	find_pipe(t_list *parsed)
{
	while (parsed)
	{
		if (get_command_type(parsed) & SIMPLE_PIPE)
			return (1);
		parsed = parsed->next;
	}
	return (0);
}

static int	is_included_pipeline(t_list *parsed)
{
	static int	mask = SIMPLE_NORMAL
		| COMPOUND_SUBSHELL | COMPOUND_PIPELINE;

	return (parsed && get_command_type(parsed) & mask
		&& parsed->next && get_command_type(parsed->next) & SIMPLE_PIPE
		&& parsed->next->next
		&& get_command_type(parsed->next->next) & mask);
}

void	find_pipeline(t_list *parsed, t_list **start, t_list **end)
{
	*start = 0;
	*end = 0;
	while (parsed && !is_included_pipeline(parsed))
		parsed = parsed->next;
	if (!parsed)
		return ;
	*start = parsed;
	while (parsed && is_included_pipeline(parsed))
		parsed = parsed->next->next;
	if (parsed)
		*end = parsed;
}
