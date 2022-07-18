/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/07/18 20:57:30 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "execute.h"
#include "env_list.h"
#include "utils.h"
#include <stdio.h>

/*
	- 자료구조
*/

/*
	- prepair
		- expansion
		- wildcard
	- builtin check
	- redir
	- execve()
*/


/*
	- builtin check
	- redirection
	- execve()
*/

typedef struct  s_cmd
{
	t_list	*args;
	t_list	*redirs;
}				t_cmd;

int     simple_cmd(t_env_list *env_list, t_list *cmd_list)
// int     simple_cmd(t_env_list *env_list, t_list *cmd_list)
{
	// execute_cmd(env_list, char *argv)
	char    **envp;
	char	**cmd;

	envp = list_to_array(env_list);
	if (envp == NULL)
		return (-1);
	cmd = list_to_array(cmd_list);
	if (cmd == NULL)
	{
		free_list(&envp);
		return (-1);
	}
	execute_cmd(envp, cmd);
	return (0);
}

static void	display_list(t_list	*plist)
{
	t_list		*cur_node;
	t_c_token	*token;

	cur_node = plist->next;
	while (cur_node)
	{
		token = (t_c_token *)cur_node;
		printf("token->str : %s\n", token->str);
		cur_node = cur_node->next;
	}
}

int	execute_process(t_env_list *env_list, t_list *cmd_list)
{
	// and_or_cmd();
	// pipeline();
	// builtin routine
	if (env_list == NULL || cmd_list == NULL)
		return (-1);
	display_list(cmd_list);
	simple_cmd(env_list, cmd_list);
	return (1);
}

