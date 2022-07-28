/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:06 by jim               #+#    #+#             */
/*   Updated: 2022/07/28 19:27:29 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "env_list.h"
#include "utils.h"
#include "ft_error.h"
#include "builtin.h"

/*
 * test
 * environ은 전역변수를 쓰지말고 main에서 처음에 init한다.
 * linked list에 넣어둔다.
 * 명령어가 들어오면 해당 linked list를 가져온다.
 */
int	env_cmd(t_env_list	*env_list, char **argument)
{
	t_env_node	*cur_node;

	if (env_list == NULL)
		return (error_handler("env", NULL, "env list is NULL", 2));
	cur_node = env_list->header_node;
	while (cur_node)
	{
		if (cur_node->value != NULL)
			printf("%s=%s\n", cur_node->key, cur_node->value);
		cur_node = cur_node->next_node;
	}
	return (0);
}
