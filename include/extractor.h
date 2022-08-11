/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractor.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:20 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:22 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACTOR_H
# define EXTRACTOR_H
# include "lexer_util.h"

int	extract_normal(char *str, int *types);
int	extract_redir(char *str, int *types);
int	extract_quote(char *str, int *types);
int	extract_bracket(char *str, int *types);
int	extract_logical_pipe(char *str, int *types);
#endif
