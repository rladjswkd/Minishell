/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:01 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 16:16:05 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "env_list.h"
#include "utils.h"

t_env_node	*create_env_node(char *key, char *value)
{
	t_env_node	*env_node;

	if (key == NULL)
		return (NULL);
	env_node = (t_env_node *)malloc(sizeof(t_env_node));
	if (env_node == NULL)
		return (NULL);
	env_node->key = key;
	env_node->value = value;
	env_node->next_node = NULL;
	return (env_node);
}

t_env_list	*create_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)malloc(sizeof(t_env_list));
	env_list->header_node = NULL;
	env_list->list_length = 0;
	return (env_list);
}

int	add_back_env_node(t_env_list *env_list, t_env_node *new_node)
{
	t_env_node	*cur_node;

	if (env_list == NULL || new_node == NULL)
		return (-1);
	if (env_list->list_length == 0)
	{
		env_list->header_node = new_node;
		return (env_list->list_length++);
	}
	cur_node = env_list->header_node;
	while (cur_node->next_node)
		cur_node = cur_node->next_node;
	cur_node->next_node = new_node;
	env_list->list_length++;
	return (env_list->list_length);
}

t_env_node	*get_env_node(t_env_list *env_list, char *key)
{
	t_env_node	*cur_node;
	size_t		cmp_len;

	if (env_list == NULL || key == NULL)
		return (NULL);
	cur_node = env_list->header_node;
	while (cur_node)
	{
		cmp_len = max_nonnegative(cur_node->key, key);
		if (ft_strncmp(cur_node->key, key, cmp_len) == 0)
			break ;
		cur_node = cur_node->next_node;
	}
	return (cur_node);
}
