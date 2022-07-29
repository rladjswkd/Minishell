/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/07/29 11:39:38 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "linked_list.h"
#include "redirect.h"
#include "heredoc.h"
#include "execute.h"
#include "lexer.h"
#include "env_list.h"
#include "utils.h"
//debug
#include <stdio.h>
/*
	- prepair
		- expansion
		- wildcard
	- redir
	- builtin check
	- execve()
*/

/*
	- status에 대한 처리가 필요하다.
*/
static int	extern_cmd(t_env_list *env_list, t_list *cmd_list, int is_child)
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
	if (is_child)
		status = execute_cmd(envp, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		// 자식프로세스에서도 부모가 heap에 할당한 데이터에 대해서 같은 메모리 공간을 가리키는가?
		else if (pid == 0)
			execute_cmd(envp, cmd);
		free_list(&envp);
		free_list(&cmd);
		waitpid(pid, &status, 0);
	}
	return (status);
}
/*< a << b >> c >> e << df
	- 어떤 redir type인지 읽어서 처리한다.
	- expansion 처리되었다는 가정하에 실행한다.
*/


static int	wildcard_for_curdir(t_list *parse_list)
{
	return (0);
}

/*
	-simple cmd에서만 실행됨
	- redirs, args에서 읽어와서 $, "", ''로 된 것들을 변환하고 하나의 node로 붙인다.
	- "", '' 어떤식으로 되어있는지 확인 필요
	- $$ 어떻게 해석할 것인가?
	- 
*/
static int	expansion(t_list *parse_list)
{
	get_simple(parse_list)->redirs;
	get_simple(parse_list)->args;
	return (0);
}

int	simple_cmd(t_env_list *env_list, t_list *parse_list, int is_child)
{
	int		status;

	expansion(parse_list);
	// wildcard(parse_list);
	status = redirection(get_simple(parse_list)->redirs, is_child);
	if (check_builtin(get_simple(parse_list)->args))
		status = builtin_process(env_list, get_simple(parse_list)->args, is_child);
	else
		status = extern_cmd(env_list, get_simple(parse_list)->args, is_child);
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


static int check_execute_operator(t_list *parse_list)
{
	parse_list->node;
	return (1);
}

int	execute_processing(t_env_list *env_list, t_list *parse_list, int is_child)
{
	if (env_list == NULL || parse_list == NULL)
		return (2);
	if (get_command_type(parse_list) == SIMPLE_NORMAL)
		update_exit_status(simple_cmd(env_list, parse_list, is_child));
	else if (get_command_type(parse_list) == COMPOUND_PIPELINE)
		update_exit_status(pipeline_processing(env_list, \
											get_compound(parse_list)->list));
	else if (get_command_type(parse_list) == COMPOUND_SUBSHELL)
		update_exit_status(execute_processing(env_list, \
											get_compound(parse_list)->list,\
											is_child));
	// echo abc | (echo a | cat) || echo asdf 의 경우 어떻게 동작할것인가?
	// PL || SCMD
	// SCMD | SUBSHELL || SCMD
	// if (parse_list->next)
	// {
	// 	parse_list = parse_list->next;
	// 	while (parse_list && check_execute_operator(parse_list))
	// 		parse_list = parse_list->next->next;
	// 	if (parse_list != NULL)
	// 		update_exit_status(\
	// 				execute_processing(env_list, parse_list, is_child));
	// }
	return (*(get_exit_status()));
}
