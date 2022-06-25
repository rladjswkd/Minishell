/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:19:15 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 19:24:31 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

/*
	t_token_type에 대한 대분류 필요
	추가적으로 더 들어갈 것들은 무엇인가?
*/
typedef enum e_token_type
{
	NONE,
	WORD,
	OPERATOR,
	META_CHARATER,
	CTL_OPERATOR,
	REDIREC_OPERATOR,
	CMD,
	PIPE,
	S_QUOTE,
	D_QUOTE,
}			t_token_type;

typedef enum e_null_char
{
	NULL_CHAR = 1,
}			t_null_char;

typedef struct s_buf
{
	char	*str;
	t_type	type;
	size_t	alloc_size;
	size_t	cur_size;
	bool	quote_flag;
	bool	parenthesis_flag;
}				t_buf;

#endif
