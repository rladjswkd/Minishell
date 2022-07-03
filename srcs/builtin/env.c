/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:06 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 17:40:39 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "env_list.h"
#include "utils.h"
#include "builtin.h"

/*
 * test
 * environ은 전역변수를 쓰지말고 main에서 처음에 init한다.
 * linked list에 넣어둔다.
 * 명령어가 들어오면 해당 linked list를 가져온다.
 */
int	env_cmd(t_env_list	*env_list, const char **argument)
{
	t_env_node	*cur_node;

	// 넘어오는 인자는 free처리한다.
	if (env_list == NULL)
		error_handler("env", NULL, "env list is NULL", 1);
	cur_node = env_list->header_node;
	while (cur_node)
	{
		if (cur_node->value != NULL)
			printf("%s=%s\n", cur_node->key, cur_node->value);
		cur_node = cur_node->next_node;
	}
	return (0);
}
