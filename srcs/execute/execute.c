/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 19:32:59 by jim              ###   ########.fr       */
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

static int	check_builtin(t_list *cmd_list)
{
	char	*cmd;

	cmd = ((t_c_token *)(cmd_list->next->node))->str;
	if (ft_strncmp("exit", cmd, max_nonnegative("exit", cmd)) == 0
		|| ft_strncmp("echo", cmd, max_nonnegative("echo", cmd)) == 0
		|| ft_strncmp("cd", cmd, max_nonnegative("cd", cmd)) == 0
		|| ft_strncmp("pwd", cmd, max_nonnegative("pwd", cmd)) == 0
		|| ft_strncmp("env", cmd, max_nonnegative("env", cmd)) == 0
		|| ft_strncmp("export", cmd, max_nonnegative("export", cmd)) == 0
		|| ft_strncmp("unset", cmd, max_nonnegative("unset", cmd)) == 0)
		return (1);
	return (0);
}

int	simple_cmd(t_env_list *env_list, t_list *cmd_list)
{
	char	**envp;
	char	**cmd;
	int		pid;
	int		status;

	cmd = list_to_array(cmd_list);
	if (check_builtin(cmd_list))
		return (builtin_process(env_list, cmd));
	envp = env_list_to_array(env_list);
	if (envp == NULL)
		return (-1);
	if (cmd == NULL)
	{
		free_list(&envp);
		return (-1);
	}
	// display_array_list(envp);
	// printf("\n\n");
	// display_array_list(cmd);
	pid = fork();
	if (pid == -1)
		exit(1);
	 // 자식프로세스에서도 부모가 heap에 할당한 데이터에 대해서 같은 메모리 공간을 가리키는가?
	else if (pid == 0)
		execute_cmd(envp, cmd);
	free_list(&envp);
	free_list(&cmd);
	waitpid(pid, &status, 0);
	return (status);
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
	// redir()
	// pipe()
	// builtin()
	// heredoc
	// (echo a ) | (echo b)
	return (1);
}

