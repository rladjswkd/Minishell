/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:01 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:09 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H
# include "structure_command.h"
# include "type_command.h"
# include "construct.h"

t_command	*get_command(t_list *parsed);
int			get_command_type(t_list *parsed);
int			create_command(t_list **neu, int type);
void		get_prev_command(t_list *parsed, t_list *node, t_list **prev);

#endif
