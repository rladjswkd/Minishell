/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:18:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/06 16:04:02 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"
#include "utils.h"
#include "ft_error.h"

/*
 - 삭제해야할 항목이 여러개라면?
 - valid한지부터 확인?
    - C언어 변수명 기준?
 - 여러인자가 있는동안 다 제거한다.
	만약에 없는 인자라면 무시하고 다음 스텝진행
	check valid name 이용
*/
int	unset_cmd(t_env_list *env_list, char **argument)
{
	t_env_node	*cur_node;
	size_t		idx;

	idx = 0;
	while (argument[idx])
	{
		if (check_valid_name(argument[idx]) == 0)
		{
			print_error(SHELL_NAME, "unset", argument[idx], NONVALID);
			idx++;
			continue ;
		}
		remove_env_node(env_list, argument[idx]);
		idx++;
	}
	return (0);
}
