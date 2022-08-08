/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:23:52 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 00:59:37 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "linked_list.h"
#include "lexer.h"
#include "utils.h"

int	wrapper_free_list(char ***word_list)
{
	free_list(word_list);
	return (-1);
}

void	safe_free_token(t_list **token)
{
	free(get_token(*token)->data);
	get_token(*token)->data = NULL;
	free((*token)->node);
	(*token)->node = NULL;
	free(*token);
	*token = NULL;
}

void	safe_free_token_list(t_list *list)
{
	t_list	*next_node;
	t_list	*cur_node;

	cur_node = list;
	while (cur_node)
	{
		next_node = cur_node->next;
		safe_free_token(&cur_node);
		cur_node = next_node;
	}
	list = NULL;
}

int	wrapper_free_token_list(t_list *list, int return_val)
{
	safe_free_token_list(list);
	return (return_val);
}
