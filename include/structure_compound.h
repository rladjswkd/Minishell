/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_compound.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:38 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:39 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_COMPOUND_H
# define STURCUTRE_COMPOUND_H
# include "structure_linked_list.h"

typedef struct s_compound
{
	t_list	*list;
	t_list	*padding;
	int		type;
}	t_compound;
#endif
