/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 15:42:23 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 15:48:19 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "ft_atoi.h"

/*
	- exit status를 여기서 처리할지
		exit_cmd 빌트인 함수를 이용할지는 추가적인 고민필요.
*/

void	error_handler(char *error_statement, int exit_status)
{
	exit_cmd(exit_status);
}
