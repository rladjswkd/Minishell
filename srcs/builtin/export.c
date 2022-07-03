/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:01 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 23:26:17 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "builtin.h"
#include "utils.h"
// debug
#include <stdio.h>
#include <stdlib.h>

static int	check_valid(char *argv);
static void	print_export_list(t_env_list *env_list)
{
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		printf("declare -x %s=%s\n", cur_node->key, cur_node->value);
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
		return (-1); //할당에러처리 이곳에서 호출한 다음에 exit()한다. , 자식프로세스에서 하는것이라 종료값($?)을 받을 수 있다.
	value = NULL;
	if (delimiter_idx >= 0)
	{
		value = ft_strndup(&(argv[delimiter_idx + 1]), \
					ft_strlen(argv) - (delimiter_idx + 1));
		if (value == NULL)
			return (-1);
	}
}

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
		if (arg_list == NULL)
			check_valid(arg_list[idx]);
		// find_key_value_str return 값을 받아서 error msg 처리할 것인가?
		find_key_value_str(arg_list[idx], key, value);
		found_node = find_export_key(env_list, key);
		if (found_node != NULL)
		{
			if (found_node->value != NULL)
				free(found_node->value);
			found_node->value = value;
		}
		else
		{
			//linked list에서 포인터를 가지고 있으니까 leak 안나는가?
			new_node = create_env_node(key, value);
			if (new_node == NULL)
				return (-1);
			add_back_env_node(env_list, new_node);
		}
		idx++;
	}
	return (0);
}

/*
 - = + file스타일의 이름명이 아니면 error인것으로 판단된다.
 isalpha_num과 under_bar까지만 된다.
*/
/*
	첫번째 문자 말고 나머지에 -같은 기호가 나와도 문제이다.
	첫번쨰 문자에는 문자와 _까지만 가능하다.
	gnu bash 참조
*/
static int	check_valid(char *argv)
{
	if (ft_is_alpha(argv[0]) == TRUE \
		|| argv[0] == '_')
		return (TRUE);
	return (FALSE);
}

int	export_cmd(t_env_list *env_list, char **argument)
{
	if (env_list == NULL)
	{
		print_error(SHELL_NAME, "env", NULL, "env list is NULL");
		return (1);
	}
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
