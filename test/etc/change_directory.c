/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_directory.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:10 by jim               #+#    #+#             */
/*   Updated: 2022/06/26 17:45:26 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stddef.h>
#include <stdio.h>
#include <sys/errno.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

/*
 * change directory
 * chdir 명령어의 return 값이 int이므로 성공시에는 0이라서
 * 언제나 chdir의 반환값을 전달하기로 결정
 * 해당값에 대한 strerror처리 필요
 * cd만 들어오는 경우에는 $HOME으로 이동필요
 * 파싱결과를 자료구조에 어떻게 저장하느냐에 따라 달라짐
 * PWD, OLDPWD에 저장이 필요하다.
 */

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	ft_putstr_fd(char const *str, int fd)
{
	write(fd, str, ft_strlen(str));
}


/*
	환경변수를 가지고 있어야한다.
	path가 없을 때 HOME으로 이동되어야한다.
	OLDPWD, PWD
*/
int	change_directory_cmd(const char *path, char *home_path)
{
	int	ret;

	ret = chdir(path);
	if (ret < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		// print_newline_fd(STDERR_FILENO);
	}
	else
		exit(1);
	/*
		시스템콜 에러가 발생하면 exit하는게 맞는가?
		그러고서 exit code를 주면 되는가?
	*/
	return (ret);
}

int main(int argc, char **argv)
{
	char	buf[PATH_MAX];

	if (argc > 1)
		chdir(argv[1]);
	else
		chdir("");
	printf("cur path : %s\n", getcwd(buf, sizeof(buf)));
	return (0);
}
/*
signal 들어왔을때 exit code전달을 어떻게할지 애매하므로 전역변수가 필요하다.
signal이 들어왔을때 호출되는 함수가 있고
ctrl + c(SIGINT)만 처리하면 된다.(1로 처리)
echo $?
*/
