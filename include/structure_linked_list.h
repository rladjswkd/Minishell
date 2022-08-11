/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_linked_list.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:40 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:41 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_LINKED_LIST_H
# define STRUCTURE_LINKED_LIST_H

typedef struct s_list
{
	void			*node;
	struct s_list	*next;
}	t_list;
#endif
