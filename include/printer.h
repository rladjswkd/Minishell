/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:33 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:35 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTER_H
# define PRINTER_H
# include <stdio.h>
# include "command_compound.h"
# include "command.h"
# include "token.h"

void	print_token_content(t_list *token_list, char *tab);
void	print_simple_content(t_list *command, char *tab);
void	print_compound_content(t_list *command);
void	print_command_content(t_list *command);
#endif
