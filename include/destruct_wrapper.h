/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_wrapper.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:20 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:18:04 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DESTRUCT_WRAPPER_H
# define DESTRUCT_WRAPPER_H
# include "structure_linked_list.h"

void	free_node(t_list **list);
void	safe_free_token(t_list **token);
void	safe_free_token_list(t_list *list);
int		wrapper_free_token_list(t_list *list, int return_val);
int		wrapper_free_list(char ***word_list);

#endif
