/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:25:48 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 21:01:00 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "wildcard.h"
#include "linked_list.h"
#include "lexer.h"
#include "utils.h"

int	add_pattern_list(t_list *pattern_list, char *dir_file_name)
{
	while (pattern_list->next)
		pattern_list = pattern_list->next;
	pattern_list->next = (t_list *)malloc(sizeof(t_list));
	if (pattern_list->next == NULL)
		return (-1);
	pattern_list->next->node = (t_token *)malloc(sizeof(t_token));
	if (pattern_list->next->node == NULL)
		return (-1); // free pattern_list, node, data free는 할당의 역순!
	get_token(pattern_list->next)->data = ft_strdup(dir_file_name);
	get_token(pattern_list->next)->types = TOKEN_NORMAL;
	if (get_token(pattern_list->next)->data == NULL)
		return (-1); // free pattern_list, node, data
	pattern_list = pattern_list->next;
	pattern_list->next = NULL;
	return (0);
}

/*
아래 타입들에 대해서 어떤식으로 패턴 매칭할것인가?
	다음패턴을 확인한다.
	e.g) *l*
		중간에 l이들어가거나, l로 시작하거나 l로 끝날 수 있다.
- *
- .*
- .*.
- *.*.
- *.*.*
- ..으로만 시작하는건 또 다르다.
*/
static int	match_pattern(const char *pattern, const char *dir_file_name,
						 const int *wildcard_pattern_flag)
{
	int	idx;
	int	pattern_idx;

	if (dir_file_name[0] == '.' && pattern[0] != '.')
		return (0);
	idx = 0;
	pattern_idx = 0;
	while (pattern[pattern_idx] && dir_file_name[idx])
	{
		if (wildcard_pattern_flag[pattern_idx] == 0)
		{
			if (pattern_idx > 0 && wildcard_pattern_flag[pattern_idx - 1])
			{
				while (dir_file_name[idx] && dir_file_name[idx] != pattern[pattern_idx])
					idx++;
			}
			if (dir_file_name[idx] != pattern[pattern_idx])
				return (0);
			idx++;
		}
		pattern_idx++;
	}
	return (1);
}

/*
	cur_dir_file_list 문자열들을 돌면서 pattern에 매칭되는것을 찾는다.
	매칭된것은 해당 문자열을 포함하는 list(node멤버변수에 token을 포함함)를 만든다.
	매칭된것을 찾으면 리스트를 만든다.
*/
static t_list	*get_pattern_matched_list(char *pattern,
										char **cur_dir_file_list,
										int *wildcard_pattern_flag)
{
	t_list	pattern_list;
	int		idx;

	idx = 0;
	pattern_list.next = NULL;
	while (cur_dir_file_list[idx])
	{
		if (match_pattern(pattern, cur_dir_file_list[idx], wildcard_pattern_flag))
		{
			if (add_pattern_list(&pattern_list, cur_dir_file_list[idx]) < 0)
			{
				// free pattern_list
				return (NULL);
			}
		}
		idx++;
	}
	return (pattern_list.next);
}

// match된 list들을 start_node에는 첫번쨰 list 값을 넣어주며 이후 노드들에 이어붙인다.
// 그리고 기존 start_node 이후부터 end_node까지는 제거한다. 
// matched_list마지막이 end_node->next 노드를 가리켜야한다.
static int	concat_matched_list_to_org_list(t_list **start_node,
										   t_list **end_node,
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
		safe_free_token(&tmp_node);
		if (tmp_node == *end_node)
			break ;
		tmp_node = next_node;
	}
	*end_node = cur_node->next;
	return (0);
}

/*
	TOKEN_CONCAT이 있을 수 있으므로 "."*"."같이 들어오는 경우 혹은 ls* 같이 1개 노드만 들어오는 경우를 가정

	** 여러개 있는 경우는 skip하고 * 한개로 만든다.
	pattern을 가져와서 cur_dir_file_list에 문자열들을 돌면서 매칭되는것을 찾는다.
	- 매칭되는 것을 찾았다면
		- 해당 문자열을 포함하는 list(node멤버변수에 token을 포함함)를 만든다.
		- 매칭되는 것이 있을때만 만들고 기존 값을 없애고 새로운 노드를 이어붙인다.
	- 매칭되는 것이 없으면 원본을 건들지 않는다.

	""
*/
// list에 wildcard_conversion 해준 리스트를 연결해준다.
// 단순한 방법 고민
static int	wildcard_conversion(t_list **start_node, t_list **end_node,
							   char **cur_dir_file_list, t_list **list)
{
	char	*pattern;
	int		*wildcard_pattern_flag;
	t_list	*matched_list;
	t_list	*tmp_start_node;

	tmp_start_node = *start_node;
	wildcard_pattern_flag = get_wildcard_pattern_flag(*start_node, *end_node);
	if (wildcard_pattern_flag == NULL)
		return (-1);
	pattern = get_organized_pattern(*start_node, *end_node, \
									wildcard_pattern_flag);
	if (pattern == NULL)
		return (-1);
	matched_list = get_pattern_matched_list(pattern, cur_dir_file_list, \
											wildcard_pattern_flag);
	if (matched_list)
		concat_matched_list_to_org_list(start_node, end_node, matched_list);
	if (tmp_start_node == *list)
		*list = *start_node;
	else
	{
		// 
		while ((*list)->next != tmp_start_node)
			(*list) = (*list)->next;
		(*list)->next = *start_node;
	}
	safe_free(&pattern);
	return (0);
}

static int	is_there_any_wildcard(t_list *cur_node)
{
	char	*str;

	if (get_token(cur_node)->types & TOKEN_SQUOTE
		|| get_token(cur_node)->types & TOKEN_DQUOTE)
		return (0);
	str = get_token(cur_node)->data;
	if (ft_strchr(str, '*') < 0)
		return (0);
	return (1);
}

static int	do_wildcard(t_list **list, char **cur_dir_file_list)
{
	t_list	*cur_node;
	t_list	*start_node;

	if (*list == NULL || cur_dir_file_list == NULL)
		return (0);
	cur_node = *list;
	start_node = NULL;
	while (cur_node)
	{
		if (start_node == NULL)
			start_node = cur_node;
		if (is_there_any_wildcard(cur_node))
		{
			while (cur_node && get_token(cur_node)->types & TOKEN_CONCAT)
				cur_node = cur_node->next;
			if (wildcard_conversion(&start_node, &cur_node, \
									cur_dir_file_list, list) < 0)
				return (-1);
		}
		if (cur_node && !(get_token(cur_node)->types & TOKEN_CONCAT))
			start_node = NULL;
		if (cur_node)
			cur_node = cur_node->next;
	}
	return (0);
}

/*< a << b >> c >> e << df
	- 어떤 redir type인지 읽어서 처리한다.
	- expansion 처리되었다는 가정하에 실행한다.
	- ex
*/
int	wildcard_for_curdir(t_simple *scmd_list)
{
	char	**cur_dir_file_list;

	if (scmd_list == NULL)
		return (-1);
	cur_dir_file_list = get_cur_dir_file_list();
	if (cur_dir_file_list == NULL)
		return (-1);
	if (do_wildcard(&(scmd_list->redirs), cur_dir_file_list) < 0)
		return (wrapper_free_list(&cur_dir_file_list));
	if (do_wildcard(&(scmd_list->args), cur_dir_file_list) < 0)
		return (wrapper_free_list(&cur_dir_file_list));
	free_list(&cur_dir_file_list);
	return (0);
}
