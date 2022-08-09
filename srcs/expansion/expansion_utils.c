/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:22:03 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 16:55:14 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env_list.h"
#include "linked_list.h"
#include "expansion.h"
#include "lexer.h"
#include "utils.h"

void	free_node(t_list **list)
{
	safe_free(&(get_token(*list)->data));
	free((*list)->node);
	(*list)->node = NULL;
	free(*list);
	*list = NULL;
}

static int	is_there_any_dollar_sign(t_token *token)
{
	const char	*str;
	int			idx;

	str = (const char *)token->data;
	idx = 0;
	while (str[idx])
	{
		if (str[idx] == '$')
			return (1);
		idx++;
	}
	return (0);
}

/*
	-simple cmd에서만 실행됨
	- redirs, args에서 읽어와서 $, "", ''로 된 것들을 변환하고 하나의 node로 붙인다.
	- "", '' 어떤식으로 되어있는지 확인 필요
	- $$ 어떻게 해석할 것인가?
	- "", '' concat이 있는 동안에는 이어붙인다.
		이어 붙이는데 쓰인 node는 free한다.
		현재노드는 free된 노드의 다음 node로 연결한다.
		더 이상 concat이 없을때까지 이어붙인다.
		그리고 type에 concat을 지운다.
		1101을 ->1001로 만드는법 
		해당 부분만 빼고 나머지는 1로 만든다음에 & 연산한다.
		-> ~(TOKEN_CONCAT) & ORG
*/
static int	is_dollar_sign_conversion(t_token *token)
{
	if (!(token->types & TOKEN_SQUOTE)
		&& (token->types & TOKEN_NORMAL || token->types & TOKEN_DQUOTE)
		&& is_there_any_dollar_sign(token))
		return (1);
	return (0);
}

static void	remove_empty_node(t_list **cur_node, t_list **prev_node, \
								t_list **list)
{
	const char	*cur_str;

	while (*cur_node)
	{
		cur_str = get_token(*cur_node)->data;
		if (ft_strncmp(cur_str, "", max_nonnegative(cur_str, "")) == 0)
		{
			if (*cur_node == *prev_node)
			{
				*prev_node = (*prev_node)->next;
				free_node(cur_node);
				*cur_node = *prev_node;
				*list = *prev_node;
			}
			else
			{
				(*prev_node)->next = (*cur_node)->next;
				free_node(cur_node);
				*cur_node = (*prev_node)->next;
			}
			continue ;
		}
		*prev_node = *cur_node;
		*cur_node = (*cur_node)->next;
	}
}

int	expand_dollar_sign_in_every_node(t_env_list *env_list, \
												t_list **list)
{
	t_list		*cur_node;
	t_list		*prev_node;

	if (env_list == NULL || list == NULL || *list == NULL)
		return (0);
	cur_node = *list;
	while (cur_node)
	{
		if (is_dollar_sign_conversion(get_token(cur_node)))
			if (dollar_sign_conversion(env_list, get_token(cur_node)) < 0)
				return (-1);
		cur_node = cur_node->next;
	}
	cur_node = *list;
	prev_node = *list;
	remove_empty_node(&cur_node, &prev_node, list);
	return (0);
}
