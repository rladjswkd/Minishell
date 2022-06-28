/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_working_directory.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:29 by jim               #+#    #+#             */
/*   Updated: 2022/06/26 18:22:17 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <limits.h>
#include <unistd.h>
#include "utils.h"
/*
 * pwd cmd
 * size에 어떤값을 넣어줘야하는지 애매, buf 사이즈라고 하지만 0을 주어도 동작한다.
 * 적절한 값을 무엇인가?
 * buf에 값이 담기는 것인가 했는데 그렇지 않다. buf가 NULL이면 getwcwd에서 malloc해서 준다고한다.
 * 우선은 NULL로하여 구현
 * 세부사항에 대한 확인 필요.
 * 파라미터 안쓰는 것은 어떻게처리 할 것인가?
 * 아예 안받고 파싱부에서 다 지워버린다?
 * 그렇게되면 builtin별로 처리가 달라지므로
 * 모든 builtin 함수에서 통일성 있게 파라미터를 받고 처리는 거기서 한다.
 */
void	print_current_working_directory_cmd(void)
{
	char	buf[PATH_MAX];
	size_t	size;

	if (getcwd(buf, sizeof(buf)) != NULL)
	{
		ft_putstr_fd(buf, STDOUT_FILENO);
		print_newline_fd(STDOUT_FILENO);
	}
	else
	{
		// error handling
		// ft_putstr_fd(buf, STDERR_FILENO);
		// print_newline_fd(STDERR_FILENO);
	}
}
