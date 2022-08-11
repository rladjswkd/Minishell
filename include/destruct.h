/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:18 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:19 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTRUCT_H
# define DESTRUCT_H
# include <stdlib.h>
# include "token.h"
# include "command.h"

void	free_token(t_list *list);
void	free_token_list(t_list *list);
void	free_command(t_list *list);
void	free_command_list(t_list *list);
#endif
