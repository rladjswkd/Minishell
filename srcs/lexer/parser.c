/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:28 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:29 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_simple.h"
#include "parser_compound.h"

int	parser(t_list *token_list, t_list *parsed_header)
{
	if (!parse_simple(token_list, parsed_header))
		return (0);
	if (!parse_compound(&(parsed_header->next)))
		return (0);
	return (1);
}
