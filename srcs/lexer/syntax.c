/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 17:01:09 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:39 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "type_token.h"

static int	is_redir_error(int curr, int next)
{
	return (curr & TOKEN_REDIR && !(next & TOKEN_NORMAL));
}

static int	is_normal_error(int curr, int next)
{
	return (curr & TOKEN_NORMAL && next && next & TOKEN_LBRACKET);
}

static int	is_pipe_logical_error(int curr, int next)
{
	return (curr & (TOKEN_PIPE | TOKEN_LOGICAL)
		&& !(next & (TOKEN_NORMAL | TOKEN_REDIR | TOKEN_LBRACKET)));
}

static int	is_bracket_error(int curr, int next)
{
	int	lmask;
	int	rmask;

	lmask = TOKEN_NORMAL | TOKEN_REDIR | TOKEN_LBRACKET;
	rmask = TOKEN_PIPE | TOKEN_LOGICAL | TOKEN_RBRACKET;
	return ((curr & TOKEN_LBRACKET && !(next & lmask))
		|| (curr & TOKEN_RBRACKET && next && !(next & rmask)));
}

int	is_error(int curr, int next, int *pair)
{
	*pair += curr == TOKEN_LBRACKET;
	*pair -= curr == TOKEN_RBRACKET;
	return (*pair < 0 || is_redir_error(curr, next)
		|| is_normal_error(curr, next) || is_pipe_logical_error(curr, next)
		|| is_bracket_error(curr, next));
}
