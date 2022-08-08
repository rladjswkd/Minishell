/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:00:32 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 18:52:14 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

static bool	is_metacharacter(char const ch);
static bool	is_control_operator(char const ch);
static bool	is_redirect_operator(char const ch);

static bool	is_metacharacter(char const ch)
{
	if (ch == '|' || ch == '<' || ch == '>' || ch == '&' \
		|| ch == '(' || ch == ')')
		return (TRUE);
	return (FALSE);
}

static bool	is_control_operator(char const ch)
{
	return (FALSE);
}

static bool	is_redirect_operator(char const ch)
{
	return (FALSE);
}

/*
	meta-character가 아닌 것은 어떻게 알 것인가?

*/
bool	is_operator(char const ch)
{
	if (is_metacharacter(ch))
		return (TRUE);
	return (FALSE);
}
