/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_scmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:30:38 by jim               #+#    #+#             */
/*   Updated: 2022/08/03 19:32:14 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/errno.h>
#include <stddef.h>
#include "linked_list.h"
#include "env_list.h"
#include "utils.h"
#include "execute.h"
#include "lexer.h"
#include "ft_error.h"
//debug
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**/

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

int	execute_cmd(char **envp, char **cmd)
{
	char	*cmd_path;
	char	**path_list;
	char	*path_with_slash;
	size_t	idx;
	int		status;

	if (preprocess_path(&path_list, envp) == -1)
		return (-1);
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
	execve(cmd[0], cmd, envp);
	// cmd not executable
	free_list(&path_list);
	if (errno == ENOENT)
	{
		print_error(SHELL_NAME, cmd[0], NULL, "command not found.");
		status = 127;
	}
	else
	{
		print_error(SHELL_NAME, cmd[0], NULL, "command not an executable.");
		status = 126;
	}
	exit(status);
}