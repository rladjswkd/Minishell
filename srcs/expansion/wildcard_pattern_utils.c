/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_pattern_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:13:57 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 20:19:56 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "lexer.h"
#include "utils.h"

static int	get_normal_case_pattern_size(t_list *cur_node)
{
	int		idx;
	int		alloc_size;
	char	prev_char;

	idx = 0;
	alloc_size = 0;
	while ((get_token(cur_node)->data)[idx])
	{
		if ((get_token(cur_node)->data)[idx] != '*')
			alloc_size += 1;
		else
		{
			if (prev_char != '*')
				alloc_size += 1;
		}
		prev_char = (get_token(cur_node)->data)[idx];
		idx++;
	}
	return (alloc_size);
}

int	get_pattern_alloc_size(t_list *start_node, t_list *end_node)
{
	t_list	*cur_node;
	int		alloc_size;
	int		idx;
	char	prev_char;

	if (start_node == NULL || end_node == NULL)
		return (0);
	alloc_size = 0;
	cur_node = start_node;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_SQUOTE
			|| get_token(cur_node)->types & TOKEN_DQUOTE)
			alloc_size += ft_strlen(get_token(cur_node)->data);
		else
			alloc_size += get_normal_case_pattern_size(cur_node);
		if (cur_node == end_node)
			break ;
		cur_node = cur_node->next;
	}
	return (alloc_size);
}
