/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:15 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:16 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "token.h"
#include "command.h"

void	free_token(t_list *list)
{
	free(get_token(list)->data);
	free(list->node);
	free(list);
}

static void	free_token_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free_token(list);
		list = next;
	}
}

void	free_command(t_list *list)
{
	t_command	*command;
	t_list		*next;

	command = get_command(list);
	if (command->type & SIMPLE_NORMAL)
	{
		free_token_list(command->l1);
		free_token_list(command->l2);
	}
	else if (command->type & (COMPOUND_PIPELINE | COMPOUND_SUBSHELL))
	{
		while (command->l1)
		{
			next = command->l1->next;
			free_command(command->l1);
			command->l1 = next;
		}
	}
	free(command);
	free(list);
}

void	free_command_list(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free_command(list);
		list = next;
	}
}
