/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 19:32:34 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 18:58:39 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
 * 토큰화
 * 토큰의 종류는 무엇인가
 * ls -al
 * " ", "\t"
 * " ", "\t", "\n"
 * TOKEN := Word Operator
 * Word
 * Operator := Control operator Redirection operator
	with Metacharater
 * metacharacter := space, tab, newline, |, (, ), <, >
 * Control operator := |, ||,
 * WORD
 * pipe
 */

#include "linked_list.h"
#include "utils.h"
#include "token.h"
#include <stdlib.h> // for exit(), error_handler사용시 제거 예정.
#include <stdbool.h>
/*
	함수형 포인터를 이용하여 operator인지 아닌지 확인
	operator면 control operator, redireciton operator인지 확인
	하지만 metacharacter와 cmd(word의 한 갈래)는 blank를 기준으로 나뉜다
	metacharacter 경우 " ", "\t", "\n",
	blank의 경우 " ", "\t"으로만 나뉜다.
	나누는 기준
	- 공백이 있다면 넘어간다.
		그런데 이전까지 저장해놓은게 있다면?
		저장해놓은 문자열을 list node로 저장한다.
		그렇다면 처음부터 받는 문자를 저장한다?
		통일성있게 처리한다는 점에서는 장점이 있지만
		1개짜리에 대해서도 할당한다는 것은 비효율적일 수 있다.
		공백이고 이전에 저장해놓은것이 있다면 저장해놓은 것을 word로 뺀다?
		word에서
	- 이전까지 저장된게 있다면 리스트 노드로 뺸다.
		빼면서 저장해놓았던 것은 free하고 기존 변수에는 NULL로 dangling방지를 한다.
		- 이전까지 저장한 문자열에는 type을 저장한다.
			word이거나 operator이거나
*/

static void	init_buf(t_buf *buf);
{
	if (buf->str != NULL)
		free(buf->str);
	buf->str = (char *)malloc(sizeof(char) * 7);
	if (buf->str == NULL)
		exit(1);// error handling 필요
	buf->str = "";
	buf->type = NONE;
	buf->alloc_size = 7;
	buf->cur_size = 0;
	buf->quote_flag = FALSE;
	buf->parenthesis_flag = FALSE;
}

static void	on_the_double_buf(t_buf *buf)
{
	char	*tmp_str;

	tmp_str = (char *)malloc(sizeof(char) * buf->alloc_size * 2);
	if (tmp_str == NULL)
		exit(1);
	ft_strlcpy(tmp_str, buf->str);
	free(buf->str);
	buf->str = tmp_str;
	buf->alloc_size = buf->alloc_size * 2;
}

static bool	is_full(size_t const size)
{
	if (size > 0)
		return (TRUE);
	return (FALSE);
}

static void	copy_buf_to_node(t_LinkedList *token_list, t_buf *buf)
{
	t_LinkedListNode	*list_node;

	list_node = create_linked_node(buf->str, buf->type);
	if (list_node == NULL)
		exit(1);// to be error_handler;
	add_back_linked_node(token_list, list_node);
}

static bool	is_quote_status(bool quote_flag)
{
	if (type == S_QUOTE || type == D_QUOTE)
		return (TRUE);
	return (FALSE);
}

static void	char_to_buf(t_buf *buf, char const ch)
{
	char	*tmp_str;

	if (buf->alloc_size <= buf->cur_size + NULL_CHAR)
		on_the_double_buf(buf);
	buf->str[buf->cur_size] = ch;
	buf->str[buf->cur_size + 1] = '\0';
	buf->cur_size++;
}

int	tokenize(char const *line, t_LinkedList *token_list)
{
	size_t	idx;
	t_buf	buf;

	idx = 0;
	if (init_buf(&buf) < 0)
		return (-1);
	/* 상태확인과 할당을 어떻게 분리할것인가? */
	while (line[idx])
	{
		if (is_quote_status(buf.quote_flag))
			char_to_buf(&buf, line[idx]);
		else if (is_metacharacter(line[idx]))
		{
			if (is_full(buf.cur_size))
			{
				copy_buf_to_node(token_list, &buf);
				init_buf(&buf);
			}
			// 이전까지 받은것과 현재 것도 저장해야한다.
			// whitespace이면 skip whitespace가 아닌 metachar이면 그것별로 저장
		}
		else if (is_quote(line[idx]))

		char_to_buf(&buf, line[idx]);
		idx++;
	}
}
