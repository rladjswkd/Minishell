/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocess.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 23:30:53 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 18:38:18 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "linked_list.h"

/*
	- tokenize를 진행한다.
	- token list를 기반으로 한 자씩 이어붙인다.
*/
t_LinkedList	*preprocess(char const *input)
{
	token_list = create_linked_list();
	if (token_list == NULL)
		return (NULL);
	tokenize(input, token_list);
}
