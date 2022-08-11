/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:40 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:41 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_token.h"
#include "structure_linked_list.h"
#include "type_token.h"
#include "construct.h"

t_token	*get_token(t_list *token_list)
{
	return ((t_token *)(token_list->node));
}

int	get_token_type(t_list *token_list)
{
	return (((t_token *)(token_list->node))->types);
}

int	create_token(t_list **token_list, char *str, int len, int types)
{
	t_token	*token;

	if (types & TOKEN_IGNORE)
		return (1);
	if (len < 0)
		return (0);
	if (!malloc_wrapper(sizeof(t_list), (void **)token_list))
		return (0);
	if (!malloc_wrapper(sizeof(t_token), (void **)&(*token_list)->node))
		return (0);
	len -= (!!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE))) << 1;
	str += !!(types & (TOKEN_SQUOTE | TOKEN_DQUOTE));
	token = get_token(*token_list);
	if (!malloc_wrapper(len + 1, (void **)&(token->data)))
		return (0);
	while (len--)
		(token->data)[len] = str[len];
	token->types = types;
	return (1);
}
