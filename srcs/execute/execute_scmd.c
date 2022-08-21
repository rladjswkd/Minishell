/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_scmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:30:38 by jim               #+#    #+#             */
/*   Updated: 2022/08/17 00:19:44 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stddef.h>
#include "env_list.h"
#include "utils.h"
#include "execute.h"
#include "ft_error.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static char	**find_path_list(char **envp)
{
	char	*path;

	path = NULL;
	while (*envp && path == NULL)
	{
		path = ft_strnstr(*envp, "PATH", ft_strlen("PATH="));
		envp++;
	}
	if (path == NULL)
		return (NULL);
	path += sizeof(char) * ft_strlen("PATH=");
	return (ft_split(path, ':'));
}

static int	preprocess_path(char ***path_list, char **envp)
{
	*path_list = find_path_list(envp);
	if (*path_list == NULL)
		return (-1);
	return (1);
}

static void	execute_cmd_in_cur_path(char **path_list, char **cmd, char **envp)
{
	int	status;

	if (path_list)
		free_list(&path_list);
	execve(cmd[0], cmd, envp);
	exit_status_handling(&status, cmd[0]);
	exit(status);
}

static int	is_absolute_path(char *cmd)
{
	if (cmd[0] == '.'
		|| cmd[0] == '/')
		return (1);
	return (0);
}

void	execute_cmd(char **envp, char **cmd)
{
	char	*cmd_path;
	char	**path_list;
	char	*path_with_slash;
	size_t	idx;

	if (preprocess_path(&path_list, envp) == -1 || is_absolute_path(cmd[0]))
	{
		if (errno != 0)
			print_error(SHELL_NAME, cmd[0], NULL, strerror(errno));
		execute_cmd_in_cur_path(path_list, cmd, envp);
	}
	else
	{
		idx = 0;
		while (path_list[idx])
		{
			path_with_slash = ft_strjoin(path_list[idx], "/");
			cmd_path = ft_strjoin(path_with_slash, cmd[0]);
			safe_free(&path_with_slash);
			execve(cmd_path, cmd, envp);
			safe_free(&cmd_path);
			idx++;
		}
		execute_cmd_in_cur_path(path_list, cmd, envp);
	}
}
