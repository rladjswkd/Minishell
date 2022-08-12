/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion_concat.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:23:01 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 18:21:04 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structure_linked_list.h"
#include "token.h"
#include "utils.h"

static int	get_alloc_size(t_list *tmp_expansion_list)
{
	t_list	*cur_node;
	int		alloc_size;

	cur_node = tmp_expansion_list;
	alloc_size = 0;
	while (cur_node)
	{
		alloc_size += ft_strlen(get_token(cur_node)->data);
		cur_node = cur_node->next;
	}
	return (alloc_size);
}

static void	concat_list_data(t_list *list, char *dst, \
							int dstsize)
{
	t_list	*cur_node;

	cur_node = list;
	while (cur_node)
	{
		ft_strlcat(dst, get_token(cur_node)->data, dstsize);
		cur_node = cur_node->next;
	}
}

int	concat_tmp_expansion_list(t_token *token, t_list *tmp_expansion_list)
{
	int	alloc_size;

	alloc_size = get_alloc_size(tmp_expansion_list->next) + 1;
	token->data = (char *)malloc(sizeof(char) * alloc_size);
	if (token->data == NULL)
		return (-1);
	(token->data)[0] = '\0';
	concat_list_data(tmp_expansion_list->next, token->data, alloc_size);
	return (0);
}
