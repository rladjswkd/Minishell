/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:23:56 by jim               #+#    #+#             */
/*   Updated: 2022/08/08 16:18:20 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "expansion.h"
#include "utils.h"
#include <stdlib.h>

static int	do_expansion(t_env_list *env_list, t_list **list)
{
	t_list	*cur_node;

	if (env_list == NULL || list == NULL || *list == NULL)
		return (0);
	if (expand_dollar_sign_in_every_node(env_list, list))
		return (-1);
	return (0);
}

int	expansion(t_env_list *env_list, t_simple *scmd_list)
{
	if (env_list == NULL || scmd_list == NULL)
		return (-1);
	if (do_expansion(env_list, &(scmd_list->redirs)) < 0)
		return (-1);
	if (do_expansion(env_list, &(scmd_list->args)) < 0)
		return (-1);
	return (0);
}
