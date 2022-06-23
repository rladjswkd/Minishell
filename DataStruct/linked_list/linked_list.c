#include <stdlib.h>
#include "linked_list.h"
#include "utils.h"

t_LinkedList	*create_linked_list(void)
{
	t_LinkedList    *pLinkedList;

	pLinkedList->listLength = 0;
	pLinkedList->headNode = NULL;
	return (pLinkedList);
}

t_LinkedListNode	*create_linked_list_node(char *str)
{
	t_LinkedListNode	*pLinkedListNode;

	pLinkedListNode = (t_LinkedListNode	*)malloc(sizeof(t_LinkedListNode));
	if (pLinkedListNode == NULL)
		return (NULL);
	pLinkedListNode->nodeStr = str;
	pLinkedListNode->nextNode = NULL;
	return (pLinkedListNode);
}

t_LinkedListNode	*get_linked_list_node(t_LinkedList *pLinkedList, \
											char *dataStr, int position)
{
	int					idx;
	t_LinkedListNode	*curLinkedListNode;

	if (pLinkedList == NULL)
		return (NULL);
	idx = 0;
	curLinkedListNode = pLinkedList->headNode;
	if (position >= 0)
	{
		while (curLinkedListNode && idx < position)
		{
			curLinkedListNode = curLinkedListNode->nextNode;
			idx++;
		}
	}
	else
	{
		while (curLinkedListNode)
		{
			if (ft_strncmp(curLinkedListNode->nodeStr, dataStr, \
							max_nonnegative(curLinkedListNode->nodeStr, \
											dataStr)) == 0)
				break ;
			curLinkedListNode = curLinkedListNode->nextNode;
		}
	}
	return (curLinkedListNode);
}

/*
	position이 0일때를 감안
*/
int	add_linked_list_node(t_LinkedList *pLinkedList, \
						t_LinkedListNode *newLinkedListNode, \
						int position)
{
	t_LinkedListNode	*curLinkedListNode;
	t_LinkedListNode	*prevLinkedListNode;

	if (pLinkedList == NULL || newLinkedListNode == NULL || position < 0 ||
		position > pLinkedList->listLength)
		return (-1);
	curLinkedListNode = pLinkedList->headNode;
	if (pLinkedList->listLength == 0)
		pLinkedList->headNode = newLinkedListNode;
	// 길이 0에 position 0이어도 안걸리겠지만 혹시 모르므로 조건을 준다.
	else if (position == 0 && pLinkedList->listLength != 0)
	{
		prevLinkedListNode = pLinkedList->headNode;
		pLinkedList->headNode = newLinkedListNode;
		newLinkedListNode->nextNode = prevLinkedListNode;
	}
	else
	{
		prevLinkedListNode = get_linked_list_node(pLinkedList, NULL, position - 1);
		newLinkedListNode->nextNode = prevLinkedListNode->nextNode;
		prevLinkedListNode->nextNode = newLinkedListNode;
	}
	pLinkedList->listLength++;
	return (pLinkedList->listLength);
}

int	remove_linked_list_node(t_LinkedList *pLinkedList, \
							char *dataStr, int position)
{
	/*
		특정값이나 positon을 이용해서 제거한다.
		find_linked_list_node를 이용한다.
		길이가 0 이하이면 바로 return
		return값을 무엇으로 할지는 고민필요
		삭제 실패해서 그런경우와는 다를 필요가 있다.
	*/
	t_LinkedListNode	*curNode;
	t_LinkedListNode	*prevNode;

	if (pLinkedList == NULL || position >= pLinkedList->listLength)
		return (-1);
	// datastr로 찾을 경우 이전 node가 몇번쨰 위치인지 몰라서 애매하다.
	// 해결할려면 양방향으로 짜거나, get_linked_list_node 파라미터로 *prevPostion같은 변수를 넘겨줘서 받아야한다.
	if (pLinkedList->listLength == 1)
	{
		free(pLinkedList->headNode);
		pLinkedList->headNode = NULL;
		pLinkedList->listLength--;
	}
	prevNode = get_linked_list_node(pLinkedList, dataStr, position - 1);
	if (curNode == NULL)
		return (-1);
	
}

int	cleare_linked_list(t_LinkedList *pLinkedList)
{
	/*
		pLinkedList 모든 node를 삭제하고 remove함수 활용
		headnode만 NULL가리키게한다.
	*/
	if (pLinkedList == NULL)
		return (-1);
	while (pLinkedList->listLength)
		remove_linked_list_node(pLinkedList, NULL, pLinkedList->listLength - 1);
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
	cleare_linked_list(*pLinkedList);
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
	curNode = pLinkedList->headNode;
	while (curNode)
	{
		printf("curNode->nodeStr %s\n", curNode->nodeStr);
		curNode = curNode->nextNode;
	}
	return (0);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	t_LinkedList	*pLinkedList;
	t_LinkedList	*pLinkedListNode;
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
		pLinkedListNode = create_linked_list_node(argv[idx]);
		if (pLinkedListNode == NULL)
		{
			// delete처리
			add_linked_list_node(pLinkedList, pLinkedListNode, idx - 1);
			return (1);
		}
		idx++;
	}

	//delete pLinkedList
	return (0);
}
