/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 20:23:33 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/errno.h>
#include <string.h>
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
	char		*old_pwd;
	t_env_node	*cur_env_node;
	size_t		cmp_len;

	old_pwd = env_list;
	cur_env_node = env_list->header_node;
	while (cur_env_node)
	{
		cmp_len = max_nonnegative(cur_env_node->key, env_key);
		if (ft_strncmp(cur_env_node->key, env_key, cmp_len) == 0)
		{
			old_pwd = cur_env_node->value;
			break ;
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (old_pwd);
}

/*
테스트 필요
포인터로만 넘겨받기 때문에 정상적으로 업데이트 되는지 확인이 필요하다.
안된다면 set_path_env()필요
*/
static void	update_path_env(t_env_list *env_list, char *be_old_pwd, \
							char *be_pwd)
{
	t_env_node	*cur_env_node;
	char		*pwd;
	char		*old_pwd;

	old_pwd = get_env_value(env_list, "OLDPWD");
	old_pwd = be_old_pwd;
	pwd = get_env_value(env_list, "PWD");
	pwd = be_pwd;
}

int	cd_cmd(const char **path, t_env_list *env_list)
{
	int		ret;
	int		idx;
	char	*cmd_path;
	char	*be_old_pwd;

	be_old_pwd = get_env_value(env_list, "PWD");
	cmd_path = &path[0];
	if (path == NULL)
		cmd_path = get_home_path(env_list);
	idx = 0;
	ret = chdir(cmd_path);
	if (ret < 0)
		error_handler("cd", path[0], strerror(errno), 1);
	update_path_env(env_list, be_old_pwd, cmd_path);
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
