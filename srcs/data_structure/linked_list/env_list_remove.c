/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list_remove.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:01 by jim               #+#    #+#             */
/*   Updated: 2022/07/04 11:44:51 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env_list.h"
#include "utils.h"

static void	free_env_node(t_env_node **cur_node)
{
	free((*cur_node)->key);
	(*cur_node)->key = NULL;
	free((*cur_node)->value);
	(*cur_node)->value = NULL;
	free(*cur_node);
	(*cur_node) = NULL;
}

int	remove_env_node(t_env_list *env_list, char *key)
{
	t_env_node	*cur_node;
	t_env_node	*prev_node;
	size_t		cmp_len;

	if (env_list == NULL)
		return (-1);
	cur_node = env_list->header_node;
	prev_node = env_list->header_node;
	while (cur_node)
	{
		cmp_len = max_nonnegative(cur_node->key, key);
		if (ft_strncmp(cur_node->key, key, cmp_len) == 0)
		{
			prev_node->next_node = cur_node->next_node;
			free_env_node(&cur_node);
			env_list->list_length--;
			break ;
		}
		prev_node = cur_node;
		cur_node = cur_node->next_node;
	}
	return (env_list->list_length);
}

int	clear_env_list(t_env_list *env_list)
{
	t_env_node	*be_removed_node;
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		be_removed_node = cur_node;
		cur_node = cur_node->next_node;
		free_env_node(&be_removed_node);
		env_list->list_length--;
	}
	return (env_list->list_length);
}

void	delete_env_list(t_env_list **env_list)
{
	t_env_node	*cur_node;

	clear_env_list(*env_list);
	free(*env_list);
	*env_list = NULL;
}