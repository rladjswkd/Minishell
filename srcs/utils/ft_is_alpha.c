/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_alpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:35:37 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 17:41:34 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_alpha(int ch)
{
	if ('a' <= ch && ch <= 'z'
		|| 'A' <= ch && ch <= 'Z')
		return (1);
	return (0);
}