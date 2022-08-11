/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:17 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:19 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer_util.h"

int	extract_normal(char *str, int *types)
{
	int	len;

	*types = TOKEN_NORMAL;
	len = 0;
	while (str[len] && !(is_delimiter(&(str[len])) || is_quote(str[len])))
		len++;
	if (is_quote(str[len]))
		*types |= TOKEN_CONCAT;
	return (len);
}

int	extract_redir(char *str, int *types)
{
	*types = TOKEN_REDIR;
	if (*str != *(str + 1))
		return (1);
	if (*str == CHAR_LREDIR)
		*types |= TOKEN_HEREDOC;
	return (2);
}

int	extract_quote(char *str, int *types)
{
	char	quote;
	int		len;

	quote = *str;
	len = 1;
	*types = TOKEN_NORMAL | TOKEN_DQUOTE;
	if (quote == CHAR_SQUOTE)
		*types = TOKEN_NORMAL | TOKEN_SQUOTE;
	while (*(++str) && *str != quote)
		len++;
	if (!(*str))
		return (-1);
	if (*(str + 1) && !is_delimiter(str + 1))
		*types |= TOKEN_CONCAT;
	return (len + 1);
}

int	extract_bracket(char *str, int *types)
{
	*types = TOKEN_LBRACKET;
	if (*str == CHAR_RBRACKET)
		*types = TOKEN_RBRACKET;
	return (1);
}

int	extract_logical_pipe(char *str, int *types)
{
	if (*str == CHAR_VERBAR && *(str + 1) != CHAR_VERBAR)
	{
		*types = TOKEN_PIPE;
		return (1);
	}
	*types = TOKEN_LOGICAL;
	return (2);
}
