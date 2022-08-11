/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_simple.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:32 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:33 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_SIMPLE_H
# define PARSER_SIMPLE_H
# include "constants.h"
# include "linked_list.h"
# include "command_simple.h"
# include "destruct.h"
//#include heredoc blahblah
int	parse_simple(t_list *token_list, t_list *header);
#endif
