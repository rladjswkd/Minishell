/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finder_compound.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:23 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:24 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FINDER_COMPOUND_H
# define FINDER_COMPOUND_H
# include "structure_linked_list.h"
# include "command_simple.h"
# include "command.h"

int		find_lbracket(t_list *parsed, t_list *rbracket, t_list **lbracket);
int		find_rbracket(t_list *parsed, t_list **rbracket);
int		find_pipe(t_list *parsed);
void	find_pipeline(t_list *parsed, t_list **start, t_list **end);
#endif
