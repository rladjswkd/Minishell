/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/08/12 13:19:12 by jim              ###   ########.fr       */
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
- env_list는 singleton으로 처리한다.
*/
// debug
// int	cd_cmd(char **path, t_env_list *env_list)

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

/*
테스트 필요
포인터로만 넘겨받기 때문에 정상적으로 업데이트 되는지 확인이 필요하다.
안된다면 set_path_env()필요
*/
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
			return (0);
		}
		cur_env_node = cur_env_node->next_node;
	}
	return (1);
}

static void	update_path_env(t_env_list *env_list, char *be_old_pwd, \
							char *be_pwd)
{
	set_path_env(env_list, "OLDPWD", be_old_pwd);
	set_path_env(env_list, "PWD", be_pwd);
}

/*
 - home이 없는경우 error statement가 다르다 25줄에 맞출려다보면 문제가 생기는데 별도로 맞출것인가>
 - exit status 관련해서도 서로 달라지는 지점이 생긴다.
   어떤식으로 exit status를 처리할 것이며 통일시킬것인가?
	에러가 있는 경우이거나 그렇지 않은 경우 모두 일관적인 룰로 처리할 수 있는 방법은 무엇인가
 - malloc error면 exit해야하는가?
*/
/*
	- lst
		- data
*/
int	cd_cmd(char **path, t_env_list *env_list)
{
	int		ret;
	char	*cmd_path;
	char	*be_old_pwd;
	char	path_buf[PATH_MAX];
	char	*cur_pwd;

	if (path[0] && path[1])
		return (error_handler("cd", NULL, "too many arguments", 1));
	if (*path == NULL)
		cmd_path = get_env_value(env_list, "HOME");
	else
		cmd_path = *path;
	ret = chdir(cmd_path);
	if (ret < 0)
		return (error_handler("cd", cmd_path, strerror(errno), 1));
	else if (getcwd(path_buf, sizeof(path_buf)) == NULL)
		return (error_handler(NULL, NULL, strerror(errno), errno));
	be_old_pwd = ft_strdup(get_env_value(env_list, "PWD"));
	if (be_old_pwd == NULL)
		error_handler(NULL, NULL, strerror(errno), errno); // 실패시 처리 필요
	cur_pwd = ft_strdup(path_buf);
	if (cur_pwd == NULL)
		return (error_handler(NULL, NULL, strerror(errno), errno));
	update_path_env(env_list, be_old_pwd, cur_pwd);
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
