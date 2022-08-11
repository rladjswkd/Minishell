/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_command.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:47 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:49 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPE_COMMAND_H
# define TYPE_COMMAND_H

typedef enum e_command_type
{
	SIMPLE_NORMAL = 1,
	SIMPLE_PIPE = 2,
	SIMPLE_LBRACKET = 4,
	SIMPLE_RBRACKET = 8,
	SIMPLE_AND = 16,
	SIMPLE_OR = 32,
	COMPOUND_PIPELINE = 64,
	COMPOUND_SUBSHELL = 128
}	t_command_type;
#endif
