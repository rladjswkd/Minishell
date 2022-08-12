/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:25:48 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 18:17:58 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "wildcard.h"
#include "structure_simple.h"
#include "token.h"
#include "destruct_wrapper.h"
#include "utils.h"

static void	link_conversion_to_middle_or_end(t_list **list, \
											t_list **start_node, \
											t_list *tmp_start_node)
{
	t_list	*cur_node;

	cur_node = *list;
	while (cur_node->next != tmp_start_node)
		cur_node = cur_node->next;
	cur_node->next = *start_node;
}

/*
	TOKEN_CONCAT이 있을 수 있으므로 "."*"."같이 들어오는 경우 혹은 ls* 같이 1개 노드만 들어오는 경우를 가정

	** 여러개 있는 경우는 skip하고 * 한개로 만든다.
	pattern을 가져와서 cur_dir_file_list에 문자열들을 돌면서 매칭되는것을 찾는다.
	- 매칭되는 것을 찾았다면
		- 해당 문자열을 포함하는 list(node멤버변수에 token을 포함함)를 만든다.
		- 매칭되는 것이 있을때만 만들고 기존 값을 없애고 새로운 노드를 이어붙인다.
	- 매칭되는 것이 없으면 원본을 건들지 않는다.
*/
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
		link_conversion_to_middle_or_end(list, start_node, tmp_start_node);
	safe_free(&pattern);
	free(wildcard_pattern_flag);
	wildcard_pattern_flag = NULL;
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
