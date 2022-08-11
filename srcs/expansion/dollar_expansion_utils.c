/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:37:59 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 12:02:49 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "destruct_wrapper.h"
#include "token.h"
#include "expansion.h"
#include "utils.h"

static void	change_dollar_expansion_flag(int *dollar_expansion_flag)
{
	if (*dollar_expansion_flag == NORMAL)
		*dollar_expansion_flag = VARIABLE;
	else
		*dollar_expansion_flag = NORMAL;
}

static void	reset_expansion_str_split_var(t_list *cur_node, \
									int *dollar_expansion_flag, \
									t_sub_str_info	*sub_str_info)
{
	get_token(cur_node)->types = *dollar_expansion_flag;
	if (sub_str_info->as_is_str[sub_str_info->idx] == '$'
		&& *dollar_expansion_flag == VARIABLE)
		;
	else
		change_dollar_expansion_flag(dollar_expansion_flag);
	sub_str_info->start_idx = (size_t)sub_str_info->idx;
	sub_str_info->len = 0;
}

static void	init_expansion_str_split_var(t_sub_str_info *sub_str_info, \
								int *dollar_expansion_flag)
{
	*dollar_expansion_flag = NORMAL;
	if ((sub_str_info->as_is_str)[0] == '$')
		*dollar_expansion_flag = VARIABLE;
	sub_str_info->idx = 0;
	sub_str_info->len = 0;
	sub_str_info->start_idx = 0;
}

static int	alloc_node(t_list **cur_node, t_list *tmp_expansion_list, \
						t_sub_str_info *sub_str_info, \
						int *dollar_expansion_flag)
{
	(*cur_node)->next = (t_list *)malloc(sizeof(t_list));
	if ((*cur_node)->next == NULL)
		return (wrapper_free_token_list(tmp_expansion_list, -1));
	(*cur_node)->next->node = (t_token *)malloc(sizeof(t_list));
	if ((*cur_node)->next == NULL)
		return (wrapper_free_token_list(tmp_expansion_list, -1));
	(get_token((*cur_node)->next)->data) = \
											ft_substr(sub_str_info->as_is_str, \
													sub_str_info->start_idx, \
													sub_str_info->len);
	if (get_token((*cur_node)->next)->data == NULL)
		return (wrapper_free_token_list(tmp_expansion_list, -1));
	reset_expansion_str_split_var((*cur_node)->next, \
							dollar_expansion_flag, \
							sub_str_info);
	(*cur_node) = (*cur_node)->next;
	(*cur_node)->next = NULL;
	return (0);
}

int	expansion_str_split(t_token *token, t_list *tmp_expansion_list)
{
	t_sub_str_info	sub_str_info;
	t_list			*cur_node;
	int				dollar_flag;

	cur_node = tmp_expansion_list;
	sub_str_info.as_is_str = (const char *)token->data;
	init_expansion_str_split_var(&sub_str_info, &dollar_flag);
	while (sub_str_info.as_is_str[sub_str_info.idx])
	{
		if (check_dollar_flag(dollar_flag, sub_str_info))
		{
			if (dollar_flag == VARIABLE
				&& sub_str_info.as_is_str[sub_str_info.idx] == '?')
			{
				(sub_str_info.len)++;
				(sub_str_info.idx)++;
			}
			alloc_node(&cur_node, tmp_expansion_list, &sub_str_info, \
						&dollar_flag);
		}
		(sub_str_info.len)++;
		(sub_str_info.idx)++;
	}
	alloc_node(&cur_node, tmp_expansion_list, &sub_str_info, &dollar_flag);
	return (0);
}
