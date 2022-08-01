/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/08/01 23:52:10 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "redirect.h"
#include "heredoc.h"
#include "execute.h"
#include "expansion.h"
#include "exit.h"
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

	if (cmd_list == NULL)
		return (0);
	cmd = list_to_array(cmd_list);
	if (cmd == NULL)
		return (-1);
	envp = env_list_to_array(env_list);
	if (envp == NULL)
	{
		free_list(&cmd);
		return (-1);
	}
	if (is_child) // 이미 fork 되어서 execve 실패해도 exit으로 종료되어서 메모리 반환에는 문제없겠지만 일관성이 문제
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

int	simple_cmd(t_env_list *env_list, t_simple *scmd_list, int is_child)
{
	int		status;

	if (expansion(env_list, scmd_list) < 0)
		return (-1);
	// wildcard(parse_list);
	status = redirection(scmd_list->redirs, is_child);
	if (check_builtin(scmd_list->args))
		status = builtin_process(env_list, scmd_list->args, is_child);
	else
		status = extern_cmd(env_list, scmd_list->args, is_child);
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

// SIMPLE_AND = 16,
// 	SIMPLE_OR = 32,
static int check_execute_operator_skip(t_list *parse_list)
{
	int	operator;

	operator = get_command_type(parse_list->node);
	if (operator & SIMPLE_AND && *get_exit_status() != 0)
		(1);
	else if (operator & SIMPLE_OR && *get_exit_status() == 0)
		(1);
	else
		(0);//error
}

int	execute_processing(t_env_list *env_list, t_list *parse_list, int is_child, \
						t_list *org_list)
{
	t_simple	*scmd_list;

	scmd_list = get_simple(parse_list);
	if (env_list == NULL || parse_list == NULL)
		return (2);
	if (get_command_type(parse_list) == SIMPLE_NORMAL)
		update_exit_status(simple_cmd(env_list, scmd_list, is_child),\
							org_list);
	else if (get_command_type(parse_list) == COMPOUND_PIPELINE)
		update_exit_status(pipeline_processing(env_list, \
											get_compound(parse_list)->list, \
											org_list), org_list);
	else if (get_command_type(parse_list) == COMPOUND_SUBSHELL)
		update_exit_status(execute_processing(env_list, \
											get_compound(parse_list)->list,\
											is_child, org_list), org_list);
	if (parse_list->next)
	{
		parse_list = parse_list->next;
		while (parse_list && check_execute_operator_skip(parse_list))
			parse_list = parse_list->next->next;
		if (parse_list != NULL)
			update_exit_status(\
					execute_processing(env_list, parse_list, is_child, org_list), org_list);
	}
	return (*(get_exit_status()));
}
