/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_compound.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:08 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:09 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_compound.h"

int	get_compound_type(t_list *parsed)
{
	return (((t_compound *)(parsed->node))->type);
}

t_compound	*get_compound(t_list *parsed)
{
	return ((t_compound *)(parsed->node));
}
