/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_simple.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:41 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:42 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_SIMPLE_H
# define STRUCTURE_SIMPLE_H
# include "structure_linked_list.h"

typedef struct s_simple
{
	t_list	*args;
	t_list	*redirs;
	int		type;
}	t_simple;
#endif
