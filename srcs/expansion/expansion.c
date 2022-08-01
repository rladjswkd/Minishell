/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:23:56 by jim               #+#    #+#             */
/*   Updated: 2022/08/01 23:51:17 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "expansion.h"
#include "utils.h"
#include <stdlib.h>

// debug
void	free_node(t_list **node);

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

static int	expand_dollar_sign_in_every_node(t_env_list *env_list, t_list *list)
{
	t_list		*cur_node;
	t_list		*next_node;
	const char	*cur_str;

	if (env_list == NULL || list == NULL)
		return (-1);
	cur_node = list;
	// expasion만 진행
	while (cur_node)
	{
		// $가 붙어있는 경우 변환한다.
		if (is_dollar_sign_conversion(get_token(cur_node)))
			if (dollar_sign_conversion(env_list, get_token(cur_node)) < 0)
				(-1);
		cur_node = cur_node->next;
	}
	// $로 변환했는데도 비어있다면(data값이 ""인 경우)해당 노드를 날린다.
	cur_node = list;
	while (cur_node)
	{
		cur_str = get_token(cur_node)->data;
		if (ft_strncmp(cur_str, "", max_nonnegative(cur_str, "") == 0))
		{
			next_node = cur_node->next;
			cur_node->next = cur_node->next->next;
			free_node(&next_node);
		}
		cur_node = cur_node->next;
	}
}

void	free_node(t_list **node)
{
	safe_free(&(get_token(*node)->data));
	free(*node);
	*node = NULL;
}

// 42"a" 5 ->42a 5로 붙어야한다.
static int	get_alloc_size_in_condition(t_list *list)
{
	t_list	*cur_node;
	int		alloc_size;

	cur_node = list;
	alloc_size = 0;
	alloc_size += ft_strlen(get_token(cur_node)->data);
	while (cur_node && cur_node->next \
			&& get_token(cur_node)->types & TOKEN_CONCAT)
	{
		alloc_size += ft_strlen(get_token(cur_node->next)->data);
		cur_node = cur_node->next;
	}
	return (alloc_size);
}

/*
 - next node, TOKEN_CONCAT 조건이 있어야하는게 헛점이 될수도 있다.
 - next node가 없는 경우
 - next node가 있지만 현재 노드 type이 TOKEN_CONCAT 아닌 경우
 - 병합했을떄 ""만 남는다면? $ab $cd expasion에 해당하는 값이 없어서 빈값만 있을 수 있다.
	이 부분은 dollar expasion에서 처리한다.
*/
static void	concat_list_data_in_condition(t_list *list, char *dst, int dstsize)
{
	t_list	*cur_node;
	t_list	*next_node;
	char	*to_be_str;

	cur_node = list;
	next_node = cur_node->next;
	ft_strlcpy(dst, get_token(cur_node)->data, dstsize);
	safe_free(&(get_token(cur_node)->data));
	while (cur_node && next_node \
			&& get_token(cur_node)->types & TOKEN_CONCAT)
	{
		ft_strlcat(dst, get_token(next_node)->data, dstsize);
		get_token(cur_node)->types = get_token(next_node)->types;
		cur_node->next = next_node->next;
		free_node(&next_node);
		next_node = cur_node->next;
	}
	get_token(cur_node)->data = dst; // dst가 "" 될 수 있는 경우가 있는가?
}

int	concat_list_in_condition(t_list *list)
{
	int		alloc_size;
	char	*to_be_str;

	alloc_size = get_alloc_size_in_condition(list) + 1;
	to_be_str = (char *)malloc(sizeof(char) * alloc_size);
	if (to_be_str == NULL)
		return (-1);
	concat_list_data_in_condition(list, to_be_str, alloc_size);
	return (0);
}

static int	do_expansion(t_env_list *env_list, t_list *list)
{
	t_list	*cur_node;

	if (env_list == NULL || list == NULL)
		return (0);
	if (expand_dollar_sign_in_every_node(env_list, list))
		return (-1);
	cur_node = list;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_CONCAT
			&& cur_node->next)
		{
			if (concat_list_in_condition(cur_node) < 0)
				(-1);
		}
		cur_node = cur_node->next;
	}
}

int	expansion(t_env_list *env_list, t_simple *scmd_list)
{
	if (env_list == NULL || scmd_list == NULL)
		return (-1);
	if (do_expansion(env_list, scmd_list->redirs) < 0)
		return (-1);
	if (do_expansion(env_list, scmd_list->args) < 0)
		return (-1);
	return (0);
}
