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
#include "destruct.h"
#include "ft_error.h"

static void	parser_alloc_error(t_list *parsed_header)
{
	free_command_list(parsed_header->next);
	print_error(SHELL_NAME, NULL, NULL, ALLOC_FAIL);
	exit(EXIT_FAILURE);
}

static int	parser_syntax_error(t_list *parsed_header)
{
	free_command_list(parsed_header->next);
	return (error_handler(NULL, NULL, SYNTAX_ERR, 0));
}

int	parser(t_list *token_list, t_list *parsed_header)
{
	int	ret;

	if (!parse_simple(token_list, parsed_header))
		parser_alloc_error(parsed_header);
	ret = parse_compound(&(parsed_header->next));
	if (!ret)
		parser_alloc_error(parsed_header);
	else if (ret == -1)
		return (parser_syntax_error(parsed_header));
	return (1);
}
