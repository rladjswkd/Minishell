/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 18:28:18 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 16:35:43 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "execute.h"
#include "builtin.h"
#include "utils.h"
#include "lexer.h"
#include <stdlib.h>
//debug
#include <stdio.h>

int	check_builtin(t_list *cmd_list)
{
	char	*cmd;

	if (cmd_list == NULL)
		return (0);
	cmd = ((t_token *)(cmd_list->node))->data;
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

int	builtin_process(t_env_list *env_list, char **cmd, int is_child)
{
	int		status;
	char	**argv;

	status = 0;
	argv = &(cmd[1]);
	if (ft_strncmp("exit", *cmd, max_nonnegative("exit", *cmd)) == 0)
		status = exit_cmd(argv, is_child);
	else if (ft_strncmp("echo", *cmd, max_nonnegative("echo", *cmd)) == 0)
		status = echo_cmd(argv);
	else if (ft_strncmp("cd", *cmd, max_nonnegative("cd", *cmd)) == 0)
		status = cd_cmd(argv, env_list);
	else if (ft_strncmp("pwd", *cmd, max_nonnegative("pwd", *cmd)) == 0)
		status = pwd_cmd();
	else if (ft_strncmp("env", *cmd, max_nonnegative("env", *cmd)) == 0)
		status = env_cmd(env_list);
	else if (ft_strncmp("export", *cmd, max_nonnegative("export", *cmd)) == 0)
		status = export_cmd(env_list, argv);
	else if (ft_strncmp("unset", *cmd, max_nonnegative("unset", *cmd)) == 0)
		status = unset_cmd(env_list, argv);
	if (is_child)
		exit(status);
	free_list(&cmd);
	return (status);
}
