/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_compound.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:09 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:11 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_COMPOUND_H
# define COMMAND_COMPOUND_H
# include "structure_compound.h"

int			get_compound_type(t_list *parsed);
t_compound	*get_compound(t_list *parsed);
#endif
