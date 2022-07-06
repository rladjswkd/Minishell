/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:01 by jim               #+#    #+#             */
/*   Updated: 2022/07/06 16:01:22 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "builtin.h"
#include "utils.h"
#include "ft_error.h"
#include <stdio.h>
#include <stdlib.h>

static void	print_export_list(t_env_list *env_list)
{
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		if (cur_node->value == NULL)
			printf("declare -x %s\n", cur_node->key);
		else
			printf("declare -x %s=\"%s\"\n", cur_node->key, cur_node->value);
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
	- 종류별 에러는 에러문구를 define을 통해서 처리할수도 있다.
*/
static int	find_key_value_str(char *argv, char *key, char *value)
{
	int			delimiter_idx;

	delimiter_idx = ft_strchr(argv, '=');
	key = ft_strndup(argv, delimiter_idx);
	if (key == NULL)
		return (-1);
	value = NULL;
	if (delimiter_idx >= 0)
	{
		value = ft_strndup(&(argv[delimiter_idx + 1]), \
					ft_strlen(argv) - (delimiter_idx + 1));
		if (value == NULL)
			return (-1);
	}
	return (0);
}

/*
export a b c=42같은 케이스 처리되게 해야한다.
기존에 있던 환경변수라면 새로 들어온 값에 value가 있는지 확인한다.
그렇지 않으면 제거
*/
static int	add_to_export_list(t_env_list *env_list, char **arg_list)
{
	t_env_node	*new_node;
	t_env_node	*found_node;
	size_t		idx;
	char		*key;
	char		*value;

	idx = 0;
	while (arg_list[idx])
	{	
		if (split_key_value(arg_list[idx], &key, &value) == -1)
			error_handler(NULL, NULL, ALLOC_FAIL, 1);
		if	(check_valid_name(key) == 0)
		{
			print_error(SHELL_NAME, "export", key, NONVALID);
			idx++;
			continue ;
		}
		found_node = find_export_key(env_list, key);
		if (found_node != NULL && value != NULL)
		{
			if (found_node->value != NULL)
				free(found_node->value);
			found_node->value = value;
		}
		else if (found_node == NULL)
		{
			new_node = create_env_node(key, value);
			if (new_node == NULL)
				return (-1);
			add_back_env_node(env_list, new_node);
		}
		idx++;
	}
	return (0);
}

int	export_cmd(t_env_list *env_list, char **argument)
{
	if (env_list == NULL)
	{
		print_error(SHELL_NAME, NULL, NULL, "env list is NULL");
		return (1);
	}
	else if (*argument == NULL)
		print_export_list(env_list);
	else
	{
		if (add_to_export_list(env_list, argument) < 0)
			return (1);// error_msg();
	}
	return (0);
}
