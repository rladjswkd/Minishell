/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:20 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 18:45:02 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <stddef.h>
# include <type.h>

typedef struct s_LinkedListNode
{
	void			*next_node;
	void			*data;
}				t_LinkedListNode;

typedef struct s_env_node
{
	char	*key;
	char	*value;
}				t_env_node;

typedef struct s_parse_node
{
	char			*token_val;
	t_token_type	type;
}				t_parse_node;

typedef struct s_LinkedList
{
	t_LinkedListNode	*header_node;
	size_t				list_length;
}				t_LinkedList;

t_LinkedList		*create_linked_list(void);
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

#endif
