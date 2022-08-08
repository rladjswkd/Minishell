/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 15:24:09 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 15:32:49 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lexer.h"
#include "utils.h"

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
	get_token(cur_node)->data = dst;
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

static int	do_concat_list(t_list **list)
{
	t_list	*cur_node;

	cur_node = *list;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_CONCAT
			&& cur_node->next)
		{
			if (concat_list_in_condition(cur_node) < 0)
				return (-1);
		}
		cur_node = cur_node->next;
	}
	return (0);
}

int	concat_list(t_simple *scmd_list)
{
	t_list	*cur_node;

	if (scmd_list == NULL)
		return (-1);
	if (do_concat_list(&(scmd_list->redirs)) < 0)
		return (-1);
	if (do_concat_list(&(scmd_list->args)) < 0)
		return (-1);
	return (0);
}
