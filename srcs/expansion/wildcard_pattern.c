/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_pattern.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:13:57 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 12:04:39 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wildcard.h"
#include "token.h"
#include "utils.h"

static void	copy_normal_case_pattern_sub_routine(t_pattern_info *pattern_info, \
													int idx, int *pattern_idx)
{
	if (pattern_info->prev_char != '*')
	{
		pattern_info->pattern[*pattern_idx] = pattern_info->normal_str[idx];
		pattern_info->wildcard_pattern_flag[*pattern_idx] = 1;
		(*pattern_idx)++;
	}
}

// 마지막 '\0' 넣는것에 대해 제대로 되는지 테스트 필요, 엣지 케이스는 없는가?
static void	copy_normal_case_pattern(char *pattern, int *wildcard_pattern_flag, \
										t_list *cur_node, int dst_size)
{
	int				idx;
	int				pattern_idx;
	t_pattern_info	pattern_info;

	idx = 0;
	pattern_idx = 0;
	pattern_info.normal_str = get_token(cur_node)->data;
	pattern_info.pattern = pattern;
	pattern_info.wildcard_pattern_flag = wildcard_pattern_flag;
	while (pattern_info.pattern[pattern_idx])
		pattern_idx++;
	while (pattern_info.normal_str[idx] && pattern_idx < dst_size)
	{
		if (pattern_info.normal_str[idx] == '*')
			copy_normal_case_pattern_sub_routine(&pattern_info, \
												idx, &pattern_idx);
		else
		{
			pattern[pattern_idx] = pattern_info.normal_str[idx];
			pattern_idx++;
		}
		pattern_info.prev_char = pattern_info.normal_str[idx];
		idx++;
	}
	pattern[pattern_idx] = '\0';
}

/*
	새로운 공간에 organize된것을 담고있다가
	기존 공간에 넘겨줄것인가?(기존공간은 free)
	만일 동일한 경우 낭비가 될수 있다.
	패턴이 일치하는게 없을 경우 기존것을 바꾸는 것은 정의한 동작이 아니므로 문제가 될수 있다.
	organize 하면 안된다.ㄴ
	"", ''분간해야한다.
	**로 여러개가 들어오면 이어붙인다.
*/
char	*get_organized_pattern(t_list *start_node, t_list *end_node,
									int *wildcard_pattern_flag)
{
	t_list	*cur_node;
	char	*pattern;
	int		alloc_size;

	if (start_node == NULL || end_node == NULL || wildcard_pattern_flag == NULL)
		return (NULL);
	alloc_size = get_pattern_alloc_size(start_node, end_node) + 1;
	pattern = (char *)malloc(sizeof(char) * alloc_size);
	if (pattern == NULL)
		return (NULL);
	pattern[0] = '\0';
	cur_node = start_node;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_SQUOTE
			|| get_token(cur_node)->types & TOKEN_DQUOTE)
			ft_strlcat(pattern, get_token(cur_node)->data, alloc_size);
		else
			copy_normal_case_pattern(pattern, wildcard_pattern_flag, \
									cur_node, alloc_size);
		if (cur_node == end_node)
			break ;
		cur_node = cur_node->next;
	}
	return (pattern);
}

int	*get_wildcard_pattern_flag(t_list *start_node, t_list *end_node)
{
	int		*wildcard_pattern_flag;
	int		alloc_size;
	int		idx;

	if (start_node == NULL || end_node == NULL)
		return (NULL);
	alloc_size = get_pattern_alloc_size(start_node, end_node) + 1;
	wildcard_pattern_flag = (int *)malloc(sizeof(int) * alloc_size);
	if (wildcard_pattern_flag == NULL)
		return (NULL);
	idx = 0;
	while (idx < alloc_size)
	{
		wildcard_pattern_flag[idx] = 0;
		idx++;
	}
	return (wildcard_pattern_flag);
}
