/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 21:37:00 by jim               #+#    #+#             */
/*   Updated: 2022/06/24 21:42:37 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

int main(int argc, char **argv, char **envp)
{
	int	pid;

	pid = fork();
	if (pid < 0)
		printf("error occured\n");
	else if (pid == 0) // child
		execve("/bin/cat" , &argv[1], envp);
	waitpid(pid, NULL, 0);
	return (0);
}
