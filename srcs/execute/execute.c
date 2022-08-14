/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 15:58:05 by jim               #+#    #+#             */
/*   Updated: 2022/08/14 22:56:59 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "command.h"
#include "command_simple.h"
#include "command_compound.h"
#include "env_list.h"
#include "redirect.h"
#include "heredoc.h"
#include "execute.h"
#include "expansion.h"
#include "exit.h"
#include "utils.h"

static int	init_and_parse_extern_cmd(t_env_list *env_list, char ***envp, \
										int *status, char **cmd)
{
	*status = 0;
	*envp = env_list_to_array(env_list);
	if (*envp == NULL)
	{
		free(cmd);
		return (-1);
	}
	return (0);
}

static int	extern_cmd(t_env_list *env_list, char **cmd, int is_child)
{
	char	**envp;
	int		pid;
	int		status;

	if (init_and_parse_extern_cmd(env_list, &envp, &status, cmd) < 0)
	{
		if (is_child)
			exit(1);
		return (1);
	}
	if (is_child)
		execute_cmd(envp, cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit(1);
		else if (pid == 0)
			execute_cmd(envp, cmd);
		free_list(&envp);
		free(cmd);
		waitpid(pid, &status, 0);
		status = handle_status(status);
	}
	return (status);
}

int	simple_cmd(t_env_list *env_list, t_simple *scmd_list, int is_child)
{
	int		status;
	char	**cmd;

	if ((expansion(env_list, scmd_list) < 0)
		|| (wildcard_for_curdir(scmd_list) < 0)
		|| (concat_list(scmd_list) < 0))
		return (1);
	status = redirection(scmd_list->redirs, is_child);
	if (status != 0)
	{
		if (is_child)
			exit(status);
		return (status);
	}
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
	int	_operator;

	_operator = get_command_type(parse_list);
	if (_operator & SIMPLE_AND && *get_exit_status() != 0)
		return (1);
	else if (_operator & SIMPLE_OR && *get_exit_status() == 0)
		return (1);
	else
		return (0);
}

int	execute_processing(t_env_list *env_list, t_list *parse_list, \
						int is_child, int io_backup[2])
{
	if (env_list == NULL || parse_list == NULL)
		return (1);
	if (get_command_type(parse_list) == SIMPLE_NORMAL)
		update_exit_status(simple_cmd(env_list, get_simple(parse_list), \
							is_child));
	else if (get_command_type(parse_list) == COMPOUND_PIPELINE)
		update_exit_status(pipeline_processing(env_list, \
								get_compound(parse_list)->list, io_backup));
	else if (get_command_type(parse_list) == COMPOUND_SUBSHELL)
		update_exit_status(execute_processing(env_list, \
								get_compound(parse_list)->list, \
											is_child, io_backup));
	if (parse_list->next)
	{
		if (reset_in_out_fd(io_backup) < 0)
			return (1);
		parse_list = parse_list->next;
		while (parse_list && check_execute_operator_skip(parse_list))
			parse_list = parse_list->next->next;
		if (parse_list != NULL)
			update_exit_status(execute_processing(env_list, parse_list, \
												is_child, io_backup));
	}
	return (*(get_exit_status()));
}
