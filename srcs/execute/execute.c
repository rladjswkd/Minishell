/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:31:11 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "structure_linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "redirect.h"
#include "heredoc.h"
#include "execute.h"
#include "expansion.h"
#include "exit.h"
#include "utils.h"

/*
static int	execute_subshell(t_env_list *env_list, t_list *parse_list, \
							int is_child, t_list *org_list)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		status = execute_processing(env_list, \
									parse_list, \
									1, org_list);
		exit(status);
	}
	waitpid(pid, &status, 0);
	status = handle_status(status);
	return (status);
}
*/

static int	extern_cmd(t_env_list *env_list, char **cmd, int is_child)
{
	char	**envp;
	int		pid;
	int		status;

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
		else if (pid == 0)
			execute_cmd(envp, cmd);
		free_list(&envp);
		free_list(&cmd);
		waitpid(pid, &status, 0);
		status = handle_status(status);
	}
	return (status);
}

int	simple_cmd(t_env_list *env_list, t_simple *scmd_list, int is_child)
{
	int		status;
	char	**cmd;

	if (expansion(env_list, scmd_list) < 0)
		return (1);
	if (wildcard_for_curdir(scmd_list) < 0)
		return (1);
	if (concat_list(scmd_list) < 0)
		return (1);
	status = redirection(scmd_list->redirs, is_child);
	if (status != 0)
		return (status);
	if (scmd_list->args == NULL)
		return (0);
	cmd = list_to_array(scmd_list->args);
	if (cmd == NULL)
		return (1);
	if (check_builtin(scmd_list->args))
		status = builtin_process(env_list, cmd, is_child);
	else
		status = extern_cmd(env_list, cmd, is_child);
	return (status);
}

static int	check_execute_operator_skip(t_list *parse_list)
{
	int	operator;

	operator = get_command_type(parse_list);
	if (operator & SIMPLE_AND && *get_exit_status() != 0)
		return (1);
	else if (operator & SIMPLE_OR && *get_exit_status() == 0)
		return (1);
	else
		return (0);
}

int	execute_processing(t_env_list *env_list, t_list *parse_list, int is_child, \
						t_list *org_list)
{
	t_simple	*scmd_list;

	scmd_list = get_simple(parse_list);
	if (env_list == NULL || parse_list == NULL)
		return (1);
	if (get_command_type(parse_list) == SIMPLE_NORMAL)
		update_exit_status(simple_cmd(env_list, scmd_list, is_child), org_list);
	else if (get_command_type(parse_list) == COMPOUND_PIPELINE)
		update_exit_status(pipeline_processing(env_list, \
											get_compound(parse_list)->list, \
											org_list), org_list);
	else if (get_command_type(parse_list) == COMPOUND_SUBSHELL)
		update_exit_status(execute_processing(env_list, \
											get_compound(parse_list)->list, \
											is_child, org_list), org_list);
	if (parse_list->next)
	{
		parse_list = parse_list->next;
		while (parse_list && check_execute_operator_skip(parse_list))
			parse_list = parse_list->next->next;
		if (parse_list != NULL)
			update_exit_status(execute_processing(env_list, parse_list, \
												is_child, org_list), org_list);
	}
	return (*(get_exit_status()));
}
