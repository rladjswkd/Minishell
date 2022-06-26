/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_variable.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:19:06 by jim               #+#    #+#             */
/*   Updated: 2022/06/21 20:21:06 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

extern char	**environ;

/*
 * test
 * environ은 전역변수를 쓰지말고 main에서 처음에 init한다.
 * linked list에 넣어둔다.
 * 명령어가 들어오면 해당 linked list를 가져온다.
 */
int	env_cmd()
{
	int i = 0;

	while(environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
