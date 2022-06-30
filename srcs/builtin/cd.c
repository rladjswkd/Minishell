/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/06/30 20:17:58 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <sys/errno.h>
#include <string.h>
#include "utils.h"

/*
- ~
- ~-
- cd
-
*/
// debug
// int	cd_cmd(char **path, t_env_list *env_list)
int	cd_cmd(char **path)
{
	int		ret;
	int		idx;
	// char	*path

	idx = 0;
	ret = chdir(path[0]);
	if (ret < 0)
		error_handler("cd", path[0], strerror(errno), 1);
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
