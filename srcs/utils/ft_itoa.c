/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 16:38:03 by jim               #+#    #+#             */
/*   Updated: 2022/06/14 16:54:40 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

size_t	count_digits(int n)
{
	size_t	expo;

	expo = 0;
	if (n < 0)
	{
		n *= -1;
		expo++;
	}
	while (n)
	{
		expo++;
		n /= 10;
	}
	return (expo);
}

char	*ft_itoa(int n)
{
	size_t	digits;
	char	*to_be_s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	digits = count_digits(n);
	to_be_s = (char *)malloc(sizeof(char) * (digits + 1));
	if (!to_be_s)
		return (0);
	if (n < 0)
	{
		n = -n;
		to_be_s[0] = '-';
	}
	to_be_s[digits] = '\0';
	digits--;
	while (n)
	{
		to_be_s[digits] = (n % 10) + '0';
		digits--;
		n /= 10;
	}
	return (to_be_s);
}
