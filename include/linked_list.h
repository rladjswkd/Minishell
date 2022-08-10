/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:20 by jim               #+#    #+#             */
/*   Updated: 2022/08/10 17:09:09 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H

typedef struct s_list
{
	void			*node;
	struct s_list	*next;
}				t_list;

void	free_node(t_list **list);
void	safe_free_token(t_list **token);
void	safe_free_token_list(t_list *list);
int		wrapper_free_token_list(t_list *list, int return_val);
int		wrapper_free_list(char ***word_list);

#endif
