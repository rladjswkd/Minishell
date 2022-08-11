/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:27 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:28 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTIL_H
# define LEXER_UTIL_H
# include "constants.h"
# include "type_token.h"

int	is_delimiter(char *s);
int	is_quote(char c);
int	ignore_blank(char *str, int *types);
#endif
