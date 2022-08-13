/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/08/13 20:44:17 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"
#include "ft_error.h"
#include "env_list.h"

/*
- ~
- ~-
- cd만 입력되면 $HOME으로 이동된다.
*/
static char	*get_env_value(t_env_list	*env_list, char *env_key)
{
	char		*env_value;
	t_env_node	*cur_env_node;
	size_t		cmp_len;

	env_value = NULL;
	cur_env_node = env_list->header_node;
	while (cur_env_node)
	{
		cmp_len = max_nonnegative(cur_env_node->key, env_key);
		if (ft_strncmp(cur_env_node->key, env_key, cmp_len) == 0)
		{
			env_value = cur_env_node->value;
			break ;
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (env_value);
}

static int	set_path_env(t_env_list *env_list, char *env_key, char *set_value)
{
	t_env_node	*cur_env_node;
	size_t		cmp_len;

	cur_env_node = env_list->header_node;
	while (cur_env_node)
	{
		cmp_len = max_nonnegative(cur_env_node->key, env_key);
		if (ft_strncmp(cur_env_node->key, env_key, cmp_len) == 0)
		{
			if (cur_env_node->value)
				free(cur_env_node->value);
			cur_env_node->value = set_value;
			return (1);
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (0);
}

static void	update_path_env(t_env_list *env_list, char *be_old_pwd, \
							char *be_pwd)
{
	if (set_path_env(env_list, "OLDPWD", be_old_pwd) == 0)
		free(be_old_pwd);
	if (set_path_env(env_list, "PWD", be_pwd) == 0)
		free(be_pwd);
}

static int	cd_cmd_change_dir_routine(char *cmd_path, char **be_old_pwd, \
										char **cur_pwd, int *ret)
{
	char	path_buf[PATH_MAX];

	if (getcwd(path_buf, sizeof(path_buf)) == NULL)
		return (error_handler(NULL, NULL, strerror(errno), errno));
	*be_old_pwd = ft_strdup(path_buf);
	if (*be_old_pwd == NULL)
		return (error_handler(NULL, NULL, strerror(errno), errno));
	*ret = chdir(cmd_path);
	if (*ret < 0)
	{
		free(*be_old_pwd);
		return (error_handler("cd", cmd_path, strerror(errno), 1));
	}
	else if (getcwd(path_buf, sizeof(path_buf)) == NULL)
	{
		free(*be_old_pwd);
		return (error_handler(NULL, NULL, strerror(errno), errno));
	}
	*cur_pwd = ft_strdup(path_buf);
	if (*cur_pwd == NULL)
	{
		free(*be_old_pwd);
		return (error_handler(NULL, NULL, strerror(errno), errno));
	}
	return (0);
}

int	cd_cmd(char **path, t_env_list *env_list)
{
	int		ret;
	int		error_ret;
	char	*cmd_path;
	char	*be_old_pwd;
	char	*cur_pwd;

	if (path[0] && path[1])
		return (error_handler("cd", NULL, "too many arguments", 1));
	cmd_path = *path;
	if (*path == NULL)
	{
		cmd_path = get_env_value(env_list, "HOME");
		if (cmd_path == NULL)
			return (error_handler("cd", NULL, "HOME not set", 1));
	}
	error_ret = \
			cd_cmd_change_dir_routine(cmd_path, &be_old_pwd, &cur_pwd, &ret);
	if (error_ret)
		return (error_ret);
	update_path_env(env_list, be_old_pwd, cur_pwd);
	return (ret);
}
