/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:24 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:25 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "constants.h"
#include "type_token.h"

int	is_delimiter(char *s)
{
	char	c;

	c = *s;
	return (c == CHAR_LREDIR || c == CHAR_RREDIR || c == CHAR_VERBAR
		|| c == CHAR_LBRACKET || c == CHAR_RBRACKET
		|| c == CHAR_SPACE || c == CHAR_TAB
		|| (c == CHAR_AMPERSAND && *(s + 1) == CHAR_AMPERSAND));
}

int	is_quote(char c)
{
	return (c == CHAR_SQUOTE || c == CHAR_DQUOTE);
}

int	ignore_blank(char *str, int *types)
{
	int	len;

	*types = TOKEN_IGNORE;
	len = 0;
	while (str[len] == CHAR_SPACE || str[len] == CHAR_TAB)
		len++;
	return (len);
}

int	is_all_whitespaces(char *input)
{
	while (*input == CHAR_SPACE || *input == CHAR_TAB || *input == '\n'
		|| *input == '\v' || *input == '\f' || *input == '\r')
		input++;
	return (!(*input));
}
