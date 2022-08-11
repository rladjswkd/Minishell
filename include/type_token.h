/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_token.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:49 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:59 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_TOKEN_H
# define TYPE_TOKEN_H

typedef enum e_token_type
{
	TOKEN_NORMAL = 1,
	TOKEN_REDIR = 2,
	TOKEN_HEREDOC = 4,
	TOKEN_REDIRARG = 8,
	TOKEN_SQUOTE = 16,
	TOKEN_DQUOTE = 32,
	TOKEN_CONCAT = 64,
	TOKEN_PIPE = 128,
	TOKEN_LBRACKET = 256,
	TOKEN_RBRACKET = 512,
	TOKEN_LOGICAL = 1024,
	TOKEN_WILDCARD = 2048,
	TOKEN_IGNORE = 4096
}	t_token_type;
#endif
