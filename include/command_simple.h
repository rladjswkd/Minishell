/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_simple.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:13 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:14 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_SIMPLE_H
# define COMMAND_SIMPLE_H
# include "structure_simple.h"

int			get_simple_type(t_list *parsed);
t_simple	*get_simple(t_list *parsed);
#endif
