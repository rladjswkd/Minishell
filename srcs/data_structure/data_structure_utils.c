/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_structure_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 16:23:52 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:52:01 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "structure_linked_list.h"
#include "destruct.h"
#include "token.h"
#include "utils.h"

int	wrapper_free_list(char ***word_list)
{
	free_list(word_list);
	return (-1);
}

void	safe_free_token(t_list **token)
{
	free_token(*token);
	*token = NULL;
}

void	safe_free_token_list(t_list *list)
{
	free_token_list(list);
	list = NULL;
}

int	wrapper_free_token_list(t_list *list, int return_val)
{
	safe_free_token_list(list);
	return (return_val);
}
