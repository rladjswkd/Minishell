/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/06/26 18:21:35 by jim              ###   ########seoul.kr  */
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
 * cd ../ a 
 * 이동된다 하지만 cd a ../는 안된다.
 * cd (유효경로) (유효하지 않은 경로)
 * builtin에 대한 에러니까 builtint
 * .., ../ 처리 "/"위치에서의 ../ 처리 필요
 * chdir()함수 자체에서 root directory에서 더이상 상위로 이동이 안된다. 별도 에러도 없으므로 처리 필요없음
 * 인자가 여러개일때 함수 호출해주는 부분에서 어떻게 넘겨줄것인가? char **, 그렇다면 마지막 문자 null이어야한다. 혹은 
 */
static size_t	word_cnt(char const **path)
{
	size_t	cnt;

	cnt = 0;
	if (path == NULL)
		return (cnt);
		
	// while ((*(path + cnt))[0] && cnt <= 1)
	while (*(path + cnt)[0])
	{
		printf("path : %s\n", *(path + cnt));
		cnt++;
	}
	return (cnt);
}

int	change_directory_cmd(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		print_newline_fd(STDERR_FILENO);
	}
	// else
	// 	exit(1);
	
	return (ret);
}

/*
*/


/*
	시스템콜 에러가 발생하면 exit하는게 맞는가?
	그러고서 exit code를 주면 되는가?
*/
/*
signal 들어왔을때 exit code전달을 어떻게할지 애매하므로 전역변수가 필요하다.
signal이 들어왔을때 호출되는 함수가 있고
ctrl + c(SIGINT)만 처리하면 된다.(1로 처리)
echo $?
*/
