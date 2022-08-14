/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 01:04:03 by jim               #+#    #+#             */
/*   Updated: 2022/08/14 17:16:58 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "destruct_wrapper.h"
#include "token.h"
#include "type_token.h"
#include "utils.h"
#include <stddef.h>

// match된 list들을 start_node에는 첫번쨰 list 값을 넣어주며 이후 노드들에 이어붙인다.
// 그리고 기존 start_node 이후부터 end_node까지는 제거한다. 
// matched_list마지막이 end_node->next 노드를 가리켜야한다.
int	concat_matched_list_to_org_list(t_list **start_node, \
									t_list **end_node, \
									t_list *matched_list)
{
	t_list	*tmp_node;
	t_list	*cur_node;
	t_list	*next_node;

	tmp_node = *start_node;
	if (*start_node == NULL || *end_node == NULL || matched_list == NULL)
		return (-1);
	*start_node = matched_list;
	cur_node = *start_node;
	while (cur_node->next)
		cur_node = cur_node->next;
	cur_node->next = (*end_node)->next;
	while (tmp_node)
	{
		next_node = tmp_node->next;
		if (tmp_node == *end_node)
		{
			safe_free_token(&tmp_node);
			break ;
		}
		safe_free_token(&tmp_node);
		tmp_node = next_node;
	}
	*end_node = cur_node;
	return (0);
}

/*
	- heredoc은 실행부 이전에 처리하기에 wildcard로 변환하지 않는다.
*/
int	is_there_any_wildcard(t_list *cur_node, t_list *prev_node)
{
	char	*str;

	if (get_token_type(cur_node) & TOKEN_SQUOTE
		|| get_token_type(cur_node) & TOKEN_DQUOTE
		|| (prev_node && get_token_type(prev_node) & TOKEN_HEREDOC))
		return (0);
	str = get_token(cur_node)->data;
	if (ft_strchr(str, '*') < 0)
		return (0);
	return (1);
}
