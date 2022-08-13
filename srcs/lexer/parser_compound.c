/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:30 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/13 21:40:36 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "command_compound.h"
#include "destruct.h"
#include "finder_compound.h"

static void	rearrange_subshell(t_list **c, t_list *l, t_list *r, t_list *neu)
{
	t_list	*prev_l;
	t_list	*prev_r;

	get_prev_command(*c, l, &prev_l);
	if (*c == l)
		*c = neu;
	else
		prev_l->next = neu;
	get_compound(neu)->list = l->next;
	prev_r = l;
	while (prev_r->next != r)
		prev_r = prev_r->next;
	prev_r->next = 0;
	l->next = 0;
	neu->next = r->next;
	r->next = 0;
	free_command(l);
	free_command(r);
}

static void	rearrange_pipeline(t_list *s, t_list *e, t_list *neu)
{
	t_list	*next;
	int		type;

	while (s != e->next)
	{
		type = get_command_type(s);
		next = s->next;
		if (type & SIMPLE_PIPE)
			free_command(s);
		else if (type & COMPOUND_PIPELINE)
		{
			append_back(&(get_compound(neu)->list), get_compound(s)->list);
			get_compound(s)->list = 0;
			free_command(s);
		}
		else
		{
			append_back(&(get_compound(neu)->list), s);
			if (s != e)
				s->next = 0;
		}
		s = next;
	}
	e->next = 0;
}

static int	process_subshell(t_list **parsed, t_list *r)
{
	t_list	*l;
	t_list	*neu;

	if (!r || !find_lbracket(*parsed, r, &l))
		return (1);
	if (get_simple_type(l->next) & COMPOUND_SUBSHELL && l->next->next == r)
		return (-1);
	if (!create_command(&neu, COMPOUND_SUBSHELL))
		return (0);
	rearrange_subshell(parsed, l, r, neu);
	return (1);
}

static int	process_pipeline(t_list **parsed)
{
	t_list	*start;
	t_list	*end;
	t_list	*neu;
	t_list	*prev_s;

	find_pipeline(*parsed, &start, &end);
	if (start && end)
	{
		if (!create_command(&neu, COMPOUND_PIPELINE))
			return (0);
		get_prev_command(*parsed, start, &prev_s);
		if (*parsed == start)
			*parsed = neu;
		else
			prev_s->next = neu;
		neu->next = end->next;
		rearrange_pipeline(start, end, neu);
	}
	return (1);
}

int	parse_compound(t_list **parsed)
{
	int		flag;
	t_list	*rbracket;

	flag = (find_rbracket(*parsed, &rbracket) || find_pipe(*parsed));
	while (flag)
	{
		if (!process_subshell(parsed, rbracket) || !process_pipeline(parsed))
			return (0);
		flag = (find_rbracket(*parsed, &rbracket) || find_pipe(*parsed));
	}
	return (1);
}
