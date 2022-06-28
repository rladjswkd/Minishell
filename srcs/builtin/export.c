/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:01 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 22:46:45 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
	첫번쨰 =를 기준으로 저장한다.
*/

#include "env_list.h"
#include "builtin.h"
#include "utils.h"

static void	print_export_list(t_env_list *env_list)
{
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		printf("%s=%s\n", cur_node->key, cur_node->value);
		cur_node = cur_node->next_node;
	}
}

static t_env_node	*find_export_key(t_env_list *env_list, char *key)
{
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		if (ft_strncmp(key, cur_node->key, \
						max_nonnegative(key, cur_node->key)) == 0)
			return (cur_node);
		cur_node = cur_node->next_node;
	}
	return (NULL);
}

/*
	- "="이 있는지 확인한다.
	- 없으면 해당 인자를 key로만 넣고 value를  NULL로 처리힌다.
*/
static int	str_to_export_list(t_env_list *env_list, char *str)
{

}

static int	add_to_export_list(t_env_list *env_list, char **argument)
{
	t_env_node	*cur_node;
	t_env_node	*found_node;
	size_t		idx;
	char		*key;
	int			delimiter_idx;

	cur_node = env_list->header_node;
	idx = 0;
	while (argument[idx])
	{
		delimiter_idx = ft_strchr(argument[idx], '=');
		key = ft_strndup(argument[idx], delimiter_idx);
		if (key == NULL)
			return (-1);
		found_node = find_export_key(env_list, key);
		idx++;
	}
	add_back_env_node(env_list,);
	return (0);
}

int	export_cmd(t_env_list *env_list, char **argument)
{
	if (env_list == NULL)
		return (-1); // system 종료해야할 문제
	if (argument == NULL)
		print_export_list(env_list);
	else
	{
		if (add_to_export_list(env_list, argument) < 0)
			return (1);// error_msg();
		print_export_list(env_list);
	}
	return (0);
}
