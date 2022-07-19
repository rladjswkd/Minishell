/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_scmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:30:38 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 12:33:44 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "linked_list.h"
#include "env_list.h"
#include "utils.h"
#include "execute.h"
//debug
#include <stdlib.h>
#include <unistd.h>

char	**list_to_array(t_list *plist);

static int	safe_strjoin(char **dst, char *s1, char *s2, char **depend_list)
{
	*dst = ft_strjoin(s1, s2);
	if (*dst == NULL)
	{
		free_list(&depend_list);
		return (-1);
	}
	return (0);
}


char	**list_to_array(t_list *plist)
{
	char		**arr_list;
	int			idx;
	int			list_len;
	t_c_token	*token;
	t_list		*cur_node;
	char		*tmp_str;

	arr_list = NULL;
	list_len = 0;
	cur_node = plist->next;
	while (cur_node)
	{
		cur_node = cur_node->next;
		list_len++;
	}
	arr_list = (char **)malloc(sizeof(char *) * (list_len + 1));
	if (arr_list == NULL)
		return (NULL);
	idx = 0;
	cur_node = plist->next;
	while (idx < list_len)
	{
		token = (t_c_token *)(cur_node->node);
		arr_list[idx] = token->str;
		idx++;
		cur_node = cur_node->next;
	}
	arr_list[list_len] = '\0';
	return (arr_list);
}
/**/

char	**env_list_to_array(t_env_list *env_list)
{
	char		**arr_list;
	int			idx;
	t_env_node	*cur_node;
	char		*tmp_str;

	arr_list = (char **)malloc(sizeof(char *) * (env_list->list_length + 1));
	if (arr_list == NULL)
		return (NULL);
	idx = 0;
	cur_node = env_list->header_node;
	while (cur_node || idx < env_list->list_length)
	{
		if (safe_strjoin(&tmp_str, cur_node->key, "=", arr_list)
			|| safe_strjoin(&arr_list[idx], tmp_str, \
							cur_node->value, arr_list))
		{
			free(tmp_str);
			free_list(&arr_list);
			return (NULL);
		}
		free(tmp_str);
		cur_node = cur_node->next_node;
		idx++;
	}
	arr_list[env_list->list_length] = '\0';
	return (arr_list);
}

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
    // print_err
	free_list(&cmd);
	free_list(&path_list);
	free_list(&envp);
	return (0);
}