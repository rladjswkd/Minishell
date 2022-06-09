/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_current_working_directory.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:29 by jim               #+#    #+#             */
/*   Updated: 2022/05/29 18:19:32 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <unistd.h>
/*
 * pwd cmd
 * size에 어떤값을 넣어줘야하는지 애매, buf 사이즈라고 하지만 0을 주어도 동작한다.
 * 적절한 값을 무엇인가?
 * buf에 값이 담기는 것인가 했는데 그렇지 않다. buf가 NULL이면 getwcwd에서 malloc해서 준다고한다.
 * 우선은 NULL로하여 구현
 * 세부사항에 대한 확인 필요.
 */
char*	print_current_working_directory_cmd(void)
{
	char	*buf;
	size_t	size;

	buf = NULL;
	size = 0;
	/*
		-ing 수정 필요
		- size, buf에 대한 체크
		- getcwd반환값에 대한 체크는 밖에서 하게 할것인가?
	*/
	return (getcwd(buf, size));
}
