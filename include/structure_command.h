/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_command.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:35 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:37 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_COMMAND_H
# define STRUCTURE_COMMAND_H
# include "structure_linked_list.h"

typedef struct s_command
{
	t_list	*l1;
	t_list	*l2;
	int		type;
}	t_command;
#endif
