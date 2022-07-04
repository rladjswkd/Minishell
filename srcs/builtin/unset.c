/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:18:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/04 22:29:04 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_list.h"


/*
 - 삭제해야할 항목이 여러개라면?
 - valid한지부터 확인?
    - C언어 변수명 기준?

*/
int	unset_cmd(t_env_list *env_list, char **argument)
{
	// get_env_node();
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		cur_node = cur_node->next_node;
	}
	return (0);
}
