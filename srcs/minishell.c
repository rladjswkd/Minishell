/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/06/25 14:42:19 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

/*
	- tokenize
		- 문자와 그렇지 않는것으로 나눈다.
		- 기준은 blank
			" ", "\t", 개행도 포함시켜야하는가? 마지막에 개행이 들어가고서 \0이 들어간다. 그때를 위해 \n을 끼는것같다.
	- 입력행을 문자단위로 하나씩 읽어서 토큰인지 아닌지 판단한다.
		- 일반 문자이면 이전에 일반문자가 있었다면 같이 이어붙인다.
	- 토큰인것이 확정되면 연결리스트의 노드로 연결한다.
	- 전체가 quote에 감싸져 있다면 어떻게 할것인가?
	-
*/

void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main(void)
{
	char	*input;
	int		fd;

	// signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handler);
	while (1)
	{
		// isatty(STDIN)
		input = readline("pepsi zero>");
		// "12345 "6
		// printf("%lu\n", strlen(input));
		preprocess(input);
		add_history(input);
	}
	return (0);
}
