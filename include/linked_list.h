/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:20 by jim               #+#    #+#             */
/*   Updated: 2022/07/17 13:14:46 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <stddef.h>

typedef struct s_LinkedListNode
{
	t_LinkedListNode	*next_node;
	void				*node;
}				t_LinkedListNode;

/*
typedef struct s_parse_node
{
	char			*token_val;
	t_token_type	type;
}				t_parse_node;
*/

typedef struct s_LinkedList
{
	t_LinkedListNode	*header_node;
	size_t				list_length;
}				t_LinkedList;

typedef struct s_list
{
	void			*node;
	struct s_list	*next;
}				t_list;

/*
	for builtin test
*/
// typedef struct	cm

t_LinkedList		*create_linked_list(void);
t_parse_node		*create_parse_node(char *token_val, t_token_type type);
t_LinkedListNode	*create_linked_node(char	*str, t_token_type type);
t_LinkedListNode	*get_linked_node(t_LinkedList *pLinkedList, \
											char *data_str);
int					add_back_linked_node(t_LinkedList *pLinkedList, \
										t_LinkedListNode *newLinkedListNode);
int					remove_linked_node(t_LinkedList *pLinkedList, \
											char *data_str);
int					clear_linked_list(t_LinkedList *pLinkedList);
int					delete_linked_list(t_LinkedList **PLinkedList);
int					display_linked_list(t_LinkedList *pLinkedList);

void				free_linked_list(t_list **list);

#endif
