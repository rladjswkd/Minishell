/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_pattern_match.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 00:52:44 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 01:55:02 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "linked_list.h"
#include "lexer.h"
#include "utils.h"

int	add_pattern_list(t_list *pattern_list, char *dir_file_name)
{
	while (pattern_list->next)
		pattern_list = pattern_list->next;
	pattern_list->next = (t_list *)malloc(sizeof(t_list));
	if (pattern_list->next == NULL)
		return (wrapper_free_token_list(pattern_list, -1));
	pattern_list->next->node = (t_token *)malloc(sizeof(t_token));
	if (pattern_list->next->node == NULL)
		return (wrapper_free_token_list(pattern_list, -1));
	get_token(pattern_list->next)->data = ft_strdup(dir_file_name);
	if (get_token(pattern_list->next)->data == NULL)
		return (wrapper_free_token_list(pattern_list, -1));
	get_token(pattern_list->next)->types = TOKEN_NORMAL;
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
	while (pattern[pattern_idx])
	{
		if (wildcard_pattern_flag[pattern_idx] == 0)
		{
			while (pattern_idx > 0 && wildcard_pattern_flag[pattern_idx - 1]
					&& dir_file_name[idx]
					&& (pattern[pattern_idx + 1] == 0 && dir_file_name[idx + 1]
						|| dir_file_name[idx] != pattern[pattern_idx])
					)
				idx++;
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
t_list	*get_pattern_matched_list(char *pattern,
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
                safe_free_token_list(&pattern_list);
				return (NULL);
			}
		}
		idx++;
	}
	return (pattern_list.next);
}
