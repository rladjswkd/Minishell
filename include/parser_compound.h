/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_compound.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:31 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:32 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_COMPOUND_H
# define PARSER_COMPOUND_H
# include "linked_list.h"
# include "command_compound.h"
# include "destruct.h"
# include "finder_compound.h"

int	parse_compound(t_list **parsed);
#endif
