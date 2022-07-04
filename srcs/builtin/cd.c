/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/07/04 11:55:28 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "env_list.h"
/*
- ~
- ~-
- cd만 입력되면 $HOME으로 이동된다.
- env_list는 singleton으로 처리한다.
*/
// debug
// int	cd_cmd(char **path, t_env_list *env_list)


static char	*get_home_path(t_env_list *env_list)
{
	char		*home_path;
	t_env_node	*cur_env_node;
	size_t		cmp_len;

	printf("in get home path\n");
	home_path = NULL;
	cur_env_node = env_list->header_node;
	while (cur_env_node)
	{
		cmp_len = max_nonnegative(cur_env_node->key, "HOME=");
		if (ft_strncmp(cur_env_node->key, "HOME=", cmp_len) == 0)
		{
			home_path = cur_env_node->value;
			break ;
		}
		cur_env_node = cur_env_node->next_node;
	}
	if (home_path == NULL)
		error_handler("cd", NULL, "HOME not set", 1);
	return (home_path);
}

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
			printf("env_key in get_env_value(): %s\n", cur_env_node->key);
			env_value = cur_env_node->value;
			break ;
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (env_value);
}

/*
테스트 필요
포인터로만 넘겨받기 때문에 정상적으로 업데이트 되는지 확인이 필요하다.
안된다면 set_path_env()필요
*/
static int	set_path_env(t_env_list *env_list, char *env_key, char *set_value)
{
	char		*env_value;
	t_env_node	*cur_env_node;
	size_t		cmp_len;

	env_value = NULL;
	cur_env_node = env_list->header_node;
	printf("== env_key : %s\n", env_key);
	while (cur_env_node)
	{
		cmp_len = max_nonnegative(cur_env_node->key, env_key);
		if (ft_strncmp(cur_env_node->key, env_key, cmp_len) == 0)
		{
			free(cur_env_node->value);
			cur_env_node->value = set_value;
			printf("## cur_env_node->value : %s\n", cur_env_node->value);
			return (0);
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (1);
}

static void	update_path_env(t_env_list *env_list, char *be_old_pwd, \
							char *be_pwd)
{
	t_env_node	*cur_env_node;
	char		*pwd;
	char		*old_pwd;

	printf("be_pwd : %s\n", be_pwd);
	printf("be_old_pwd : %s\n", be_old_pwd);
	set_path_env(env_list, "PWD", be_pwd);
	set_path_env(env_list, "OLDPWD", be_old_pwd);
}

int	cd_cmd(char **path, t_env_list *env_list)
{
	int		ret;
	char	*cmd_path;
	char	*be_old_pwd;

	be_old_pwd = get_env_value(env_list, "PWD");	
	if (*path == NULL)
		cmd_path = get_env_value(env_list, "HOME");
	else
		cmd_path = *path;
	printf("be_old_pwd : %s\n", be_old_pwd);
	printf("cmd_path : %s\n", cmd_path);
	ret = chdir(cmd_path);
	if (ret < 0)
		error_handler("cd", cmd_path, strerror(errno), 1);
	update_path_env(env_list, be_old_pwd, cmd_path);
	printf("curruent OLDPWD : %s\n",  get_env_value(env_list, "OLDPWD"));
	printf("curruent pwd : %s\n",  get_env_value(env_list, "PWD"));
	return (ret);
}

/*
*/

/*
	시스템콜 에러가 발생하면 exit하는게 맞는가?
	그러고서 exit code를 주면 되는가?
*/
/*
signal 들어왔을때 exit code전달을 어떻게할지 애매하므로 전역변수가 필요하다.
signal이 들어왔을때 호출되는 함수가 있고
ctrl + c(SIGINT)만 처리하면 된다.(1로 처리)
echo $?
*/
