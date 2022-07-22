/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/07/22 21:00:03 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "linked_list.h"
#include "execute.h"
#include "lexer.h"
#include "env_list.h"
#include "utils.h"
#include "redirec.h"
/*
	- prepair
		- expansion
		- wildcard
	- redir
	- builtin check
	- execve()
*/

/*
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

static void	display_list(t_list	*plist)
{
	t_list		*cur_node;
	t_token		*token;

	cur_node = plist->next;
	while (cur_node)
	{
		token = (t_token *)(cur_node->node);
		printf("token->str : %s\n", token->data);
		cur_node = cur_node->next;
	}
}

*/

/*
	- status에 대한 처리가 필요하다.
*/
static int	extern_cmd(t_env_list *env_list, t_list *cmd_list)
{
	char	**envp;
	char	**cmd;
	int		pid;
	int		status;

	cmd = list_to_array(cmd_list);
	if (cmd == NULL)
		return (-1);
	envp = env_list_to_array(env_list);
	if (envp == NULL)
	{
		free_list(&cmd);
		return (-1);
	}
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

/*< a << b >> c >> e << df
	- 어떤 redir type인지 읽어서 처리한다.
	- expansion 처리되었다는 가정하에 실행한다.
*/


/*
	- 
*/
int	simple_cmd(t_env_list *env_list, t_list *parse_list)
{
	int	status;

	// preperation
	// wildcard
	// redir()
	status = redirection(get_simple(parse_list)->redirs);
	if (check_builtin(get_simple(parse_list)->args))
		status = builtin_process(env_list, get_simple(parse_list)->args);
	else
		status = extern_cmd(env_list, get_simple(parse_list)->args);
	return (status);
}
/**/

/*
	- 현재 타입을 비교한다.
	- 다단계
		- t_command (t_command_type 이용)
			- t_compound ||  t_simple
			- t_compound
				- COMPOUND_PIPELINE
				- COMPOUND_SUBSHELL
			- t_simple
				- SIMPLE_NORMAL
*/
int	execute_processing(t_env_list *env_list, t_list *parse_list)
{
	if (env_list == NULL || parse_list == NULL)
		return (-1);
	// print_command_content(parse_list);
	// get_command_type(parse_list);
	if (get_command_type(parse_list) == SIMPLE_NORMAL)
		simple_cmd(env_list, parse_list);
	else if (get_command_type(parse_list) == COMPOUND_PIPELINE)
		;
	else if (get_command_type(parse_list) == COMPOUND_SUBSHELL)
		;
	// display_list(parse_list);
	// simple_cmd(env_list, parse_list);
	return (1);
}

