/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:10 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/08 19:53:12 by gyepark          ###   ########.kr       */
/*                                                                            */
/* ************************************************************************** */

#include "structure_simple.h"

int	get_simple_type(t_list *parsed)
{
	return (((t_simple *)(parsed->node))->type);
}

t_simple	*get_simple(t_list *parsed)
{
	return ((t_simple *)(parsed->node));
}
