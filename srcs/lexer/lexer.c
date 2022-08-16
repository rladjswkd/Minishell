/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:22 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/16 13:40:05 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "token.h"
#include "destruct_wrapper.h"
#include "extractor.h"
#include "syntax.h"
#include "ft_error.h"

static int	get_index(char c1, char c2)
{
	return ((c1 == CHAR_LREDIR || c1 == CHAR_RREDIR) * 1
		| (c1 == CHAR_SQUOTE || c1 == CHAR_DQUOTE) * 2
		| (c1 == CHAR_LBRACKET || c1 == CHAR_RBRACKET) * 3
		| ((c1 == CHAR_AMPERSAND && c2 == CHAR_AMPERSAND)
			|| c1 == CHAR_VERBAR) * 4
		| (c1 == CHAR_SPACE || c1 == CHAR_TAB) * 5);
}

static void	mask_redirarg_type(t_list *token_list)
{
	while (token_list)
	{
		if (get_token_type(token_list) & TOKEN_REDIR)
		{
			token_list = token_list->next;
			get_token(token_list)->types |= TOKEN_REDIRARG;
			while (get_token_type(token_list) & TOKEN_CONCAT)
			{
				token_list = token_list->next;
				get_token(token_list)->types |= TOKEN_REDIRARG;
			}
		}
		token_list = token_list->next;
	}
}

static int	check_syntax(t_list *token_list)
{
	int		type;
	int		next;
	int		pair;
	t_list	*cur;

	if (get_token_type(token_list)
		& (TOKEN_PIPE | TOKEN_LOGICAL | TOKEN_RBRACKET))
		return (0);
	pair = 0;
	cur = token_list;
	while (cur)
	{
		type = get_token_type(cur);
		next = 0;
		if (cur->next)
			next = get_token_type(cur->next);
		if (is_error(type, next, &pair))
			return (0);
		cur = cur->next;
	}
	return (pair == 0);
}

static int	tokenize_input(char *str, t_list *token_header)
{
	int			len;
	int			types;
	t_list		*cur;
	static int	(*len_fp[6])(char *, int *) = {
		&extract_normal, &extract_redir, &extract_quote,
		&extract_bracket, &extract_logical_pipe, &ignore_blank};

	while (*str)
	{	
		len = (len_fp[get_index(*str, *(str + 1))])(str, &types);
		if (len == -1)
			return (len);
		if (!create_token(&cur, str, len, types))
			return (0);
		if (!(types & TOKEN_IGNORE))
		{
			token_header->next = cur;
			token_header = token_header->next;
		}
		types = 0;
		str += len;
	}
	token_header->next = 0;
	return (1);
}

int	lexer(char *input, t_list *token_header)
{
	int	ret;

	ret = tokenize_input(input, token_header);
	if (!ret)
	{
		safe_free_token_list(token_header->next);
		print_error(SHELL_NAME, NULL, NULL, ALLOC_FAIL);
		exit(EXIT_FAILURE);
	}
	if (ret == -1 || !check_syntax(token_header->next))
	{
		safe_free_token_list(token_header->next);
		return (error_handler(NULL, NULL, SYNTAX_ERR, 0));
	}
	mask_redirarg_type(token_header->next);
	return (1);
}
