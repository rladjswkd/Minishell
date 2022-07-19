/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 12:47:57 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "execute.h"
#include "env_list.h"
#include "utils.h"
// debug
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

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


static void     display_array_list(char **arr_list)
{
	int	idx;

	if (arr_list == NULL || *arr_list == NULL)
		return ;
	idx = 0;
	while (arr_list[idx])
	{
		printf("arr_list[idx] : %s\n", arr_list[idx]);
		idx++;
	}
}

int     simple_cmd(t_env_list *env_list, t_list *cmd_list)
{
	char    **envp;
	char	**cmd;
	int		pid;

	envp = env_list_to_array(env_list);
	if (envp == NULL)
		return (-1);
	display_array_list(envp);
	cmd = list_to_array(cmd_list);
	if (cmd == NULL)
	{
		// free_list(&envp);
		return (-1);
	}
	display_array_list(envp);
	printf("\n\n");
	display_array_list(cmd);
	pid = fork();
	if (pid == -1)
		exit(1);
	else if (pid == 0)
		execute_cmd(envp, cmd);
	waitpid(pid, NULL, 0);
	return (0);
}

static void	display_list(t_list	*plist)
{
	t_list		*cur_node;
	t_c_token	*token;

	cur_node = plist->next;
	while (cur_node)
	{
		token = (t_c_token *)(cur_node->node);
		printf("token->str : %s\n", token->str);
		cur_node = cur_node->next;
	}
}

int	execute_process(t_env_list *env_list, t_list *cmd_list)
{
	
	if (env_list == NULL || cmd_list == NULL)
		return (-1);
	// display_list(cmd_list);
	simple_cmd(env_list, cmd_list);
	// redir
	// pipe
	// builtin
	// heredoc
	return (1);
}

