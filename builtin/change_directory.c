/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/06/21 20:00:14 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include "utils.h"

/*
 * change directory
 * chdir 명령어의 return 값이 int이므로 성공시에는 0이라서
 * 언제나 chdir의 반환값을 전달하기로 결정
 * 해당값에 대한 strerror처리 필요
 * cd만 들어오는 경우에는 $HOME으로 이동필요
 * 파싱결과를 자료구조에 어떻게 저장하느냐에 따라 달라짐
 * PWD, OLDPWD에 저장이 필요하다.
 */
int	change_directory_cmd(const char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		print_newline_fd(STDERR_FILENO);
	}
	else
	{
		;
		// PWD
		// OLDPWD에 저장필요
	}
	return (ret);
}
