/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plain_linked_list.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/18 20:36:00 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include <stdlib.h>
/*
	- node에 담은 것이 어떤 데이터 타입인지 모르므로 해당 node에 접근하여 값들을 
	free하지않으면 pointer를 잃으므로 leak이 발생할 것이다.
*/
static void	free_node(t_list **cur_node)
{
	free((*cur_node)->node);
	(*cur_node)->node = NULL;
}

void	free_linked_list(t_list **list)
{
	t_list	*cur_node;
	t_list	*removed_node;

	if (list == NULL || *list == NULL)
		return ;
	cur_node = *list;
	while (cur_node)
	{
		removed_node = cur_node;
		free_node(&removed_node);
		cur_node = cur_node->next;
	}
}
