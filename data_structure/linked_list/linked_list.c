/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 20:23:01 by jim               #+#    #+#             */
/*   Updated: 2022/06/21 22:37:08 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "linked_list.h"
#include "utils.h"

/*
	create List
	create ListNode

	find
	add
	remove
	delete
	clear
	display
*/

t_LinkedList	*create_linked_list(void)
{
	t_LinkedList	*plinked_list;

	plinked_list->list_length = 0;
	plinked_list->header_node = NULL;
	return (plinked_list);
}

t_LinkedListNode	*create_linked_node(char *str)
{
	t_LinkedListNode	*plinked_node;

	plinked_node = (t_LinkedListNode *)malloc(sizeof(t_LinkedListNode));
	if (plinked_node == NULL)
		return (NULL);
	plinked_node->node_str = str;
	plinked_node->next_node = NULL;
	return (plinked_node);
}

static t_LinkedListNode	*get_linked_node_using_position(\
										t_LinkedList *pLinkedList, int position)
{
	int					idx;
	t_LinkedListNode	*cur_linked_node;

	if (pLinkedList == NULL)
		return (NULL);
	idx = 0;
	cur_linked_node = pLinkedList->header_node;
	while (cur_linked_node && idx < position)
	{
		cur_linked_node = cur_linked_node->next_node;
		idx++;
	}
	return (cur_linked_node);
}

t_LinkedListNode	*get_linked_node(t_LinkedList *pLinkedList, \
											char *data_str, int position)
{
	int					idx;
	t_LinkedListNode	*cur_linked_node;

	if (pLinkedList == NULL)
		return (NULL);
	idx = 0;
	cur_linked_node = pLinkedList->header_node;
	if (position >= 0)
		return (get_linked_node_using_position(pLinkedList, position));
	else
	{
		while (cur_linked_node)
		{
			if (ft_strncmp(cur_linked_node->node_str, data_str, \
							max_nonnegative(cur_linked_node->node_str, \
											data_str)) == 0)
				break ;
			cur_linked_node = cur_linked_node->next_node;
		}
	}
	return (cur_linked_node);
}

/*
	position이 0일때를 감안
*/
int	add_linked_node(t_LinkedList *pLinkedList, \
						t_LinkedListNode *newLinkedListNode, \
						int position)
{
	t_LinkedListNode	*cur_linked_node;
	t_LinkedListNode	*prev_linked_node;

	if (pLinkedList == NULL || newLinkedListNode == NULL || position < 0
		|| position > pLinkedList->list_length)
		return (-1);
	cur_linked_node = pLinkedList->header_node;
	if (pLinkedList->list_length == 0)
		pLinkedList->header_node = newLinkedListNode;
	// 길이 0에 position 0이어도 안걸리겠지만 혹시 모르므로 조건을 준다.
	else if (position == 0 && pLinkedList->list_length != 0)
	{
		prev_linked_node = pLinkedList->header_node;
		pLinkedList->header_node = newLinkedListNode;
		newLinkedListNode->next_node = prev_linked_node;
	}
	else
	{
		prev_linked_node = get_linked_node(pLinkedList, NULL, position - 1);
		newLinkedListNode->next_node = prev_linked_node->next_node;
		prev_linked_node->next_node = newLinkedListNode;
	}
	pLinkedList->list_length++;
	return (pLinkedList->list_length);
}

int	remove_linked_node(t_LinkedList *pLinkedList, \
							char *data_str, int position)
{
	/*
		특정값이나 positon을 이용해서 제거한다.
		find_linked_node를 이용한다.
		길이가 0 이하이면 바로 return
		return값을 무엇으로 할지는 고민필요
		삭제 실패해서 그런경우와는 다를 필요가 있다.
	*/
	t_LinkedListNode	*curNode;
	t_LinkedListNode	*prevNode;

	if (pLinkedList == NULL || position >= pLinkedList->list_length)
		return (-1);
	// data_str로 찾을 경우 이전 node가 몇번쨰 위치인지 몰라서 애매하다.
	// 해결할려면 양방향으로 짜거나, get_linked_node 파라미터로 *prevPostion같은 변수를 넘겨줘서 받아야한다.
	if (pLinkedList->list_length == 1)
	{
		free(pLinkedList->header_node);
		pLinkedList->header_node = NULL;
		pLinkedList->list_length--;
	}
	prevNode = get_linked_node(pLinkedList, data_str, position - 1);
	if (curNode == NULL)
		return (-1);

}

int	clear_linked_list(t_LinkedList *pLinkedList)
{
	/*
		pLinkedList 모든 node를 삭제하고 remove함수 활용
		header_node만 NULL가리키게한다.
	*/
	if (pLinkedList == NULL)
		return (-1);
	while (pLinkedList->list_length)
		remove_linked_node(pLinkedList, NULL, pLinkedList->list_length - 1);
	return (0);
}

int	delete_linked_list(t_LinkedList **pLinkedList)
{
	/*
		cleare한 뒤에 PLinkedList자체도 삭제한다.
		PLinkedList = NULL을 할당하여 dangling도 방지한다.
	*/
	// pLinkedList 작 동작하는지 확인 필요
	if (pLinkedList == NULL || *pLinkedList == NULL)
		return (-1);
	clear_linked_list(*pLinkedList);
	*pLinkedList = NULL;
	return (0);
}

int	display_linked_list(t_LinkedList *pLinkedList)
{
	/*
		값이 잘 있는지 출력한다.
	*/
	t_LinkedListNode	*curNode;

	if (pLinkedList == NULL)
		return (-1);
	curNode = pLinkedList->header_node;
	while (curNode)
	{
		printf("curNode->node_str %s\n", curNode->node_str);
		curNode = curNode->next_node;
	}
	return (0);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_LinkedList	*pLinkedList;
	t_LinkedList	*plinked_node;
	size_t			idx;
	/*
		test
		sentence
		4242
	*/
	if (argc < 2)
		return (1);
	pLinkedList = create_linked_list();
	if (pLinkedList == NULL)
		return (1);
	idx = 1;
	while (argc > idx)
	{
		plinked_node = create_linked_node(argv[idx]);
		if (plinked_node == NULL)
		{
			// delete처리
			add_linked_node(pLinkedList, plinked_node, idx - 1);
			return (1);
		}
		idx++;
	}

	//delete pLinkedList
	return (0);
}
