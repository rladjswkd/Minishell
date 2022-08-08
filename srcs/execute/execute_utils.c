/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 16:32:30 by jim               #+#    #+#             */
/*   Updated: 2022/08/03 16:37:22 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "utils.h"

static int	safe_strjoin(char **dst, char *s1, char *s2, char **depend_list)
{
	*dst = ft_strjoin(s1, s2);
	if (*dst == NULL)
	{
		free_list(&depend_list);
		return (-1);
	}
	return (0);
}

static int get_length(t_list *plist)
{
	t_list	*cur_node;
	int		list_len;

	list_len = 0;
	cur_node = plist;
	while (cur_node)
	{
		cur_node = cur_node->next;
		list_len++;
	}
	return (list_len);
}

char	**list_to_array(t_list *plist)
{
	char		**arr_list;
	int			idx;
	int			list_len;
	t_list		*cur_node;

	if (plist == NULL)
		return (NULL);
	list_len = get_length(plist);
	arr_list = (char **)malloc(sizeof(char *) * (list_len + 1));
	if (arr_list == NULL)
		return (NULL);
	idx = 0;
	cur_node = plist;
	while (idx < list_len)
	{
		arr_list[idx] = get_token(cur_node)->data;
		idx++;
		cur_node = cur_node->next;
	}
	arr_list[list_len] = NULL;
	return (arr_list);
}
/**/

char	**env_list_to_array(t_env_list *env_list)
{
	char		**arr_list;
	int			idx;
	t_env_node	*cur_node;
	char		*tmp_str;

	arr_list = (char **)malloc(sizeof(char *) * (env_list->list_length + 1));
	if (arr_list == NULL)
		return (NULL);
	idx = 0;
	cur_node = env_list->header_node;
	while (cur_node && idx < env_list->list_length)
	{
		if (safe_strjoin(&tmp_str, cur_node->key, "=", arr_list)
			|| safe_strjoin(&arr_list[idx], tmp_str, cur_node->value, arr_list))
		{
			safe_free(&tmp_str);
			free_list(&arr_list);
			return (NULL);
		}
		safe_free(&tmp_str);
		cur_node = cur_node->next_node;
		idx++;
	}
	arr_list[env_list->list_length] = NULL;
	return (arr_list);
}
