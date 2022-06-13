#ifndef LINKED_LIST_H
# define LINKED_LIST_H
# include <stddef.h>

typedef struct  s_LinkedListNode
{
	struct s_LinkedListNode		*nextNode;
	char						*nodeStr;
}				t_LinkedListNode;

typedef struct  s_LinkedList
{
	t_LinkedListNode	*headNode;
	size_t				listLength;

}				t_LinkedList;


t_LinkedList		*create_linked_list(void);
t_LinkedListNode	*create_linked_list_node(char	*str);
t_LinkedListNode	*get_linked_list_node(t_LinkedList *pLinkedList, \
											char *dataStr, int position);
int					add_linked_list_node(t_LinkedList *pLinkedList, \
											t_LinkedListNode *newLinkedListNode, \
											int position);
int					remove_linked_list_node(t_LinkedList *pLinkedList, \
											char *dataStr, int position);
int					cleare_linked_list(t_LinkedList *pLinkedList);
int					delete_linked_list(t_LinkedList **PLinkedList);
int					display_linked_list(t_LinkedList *pLinkedList);

#endif