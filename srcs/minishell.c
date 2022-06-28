/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 22:02:55 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stddef.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include "init.h"
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

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int			fd;
	t_env_list	*env_list;
	t_env_node	*cur_node;

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handler);
	size_t	idx = 0;
	env_list = create_env_list();
	if (env_list == NULL)
		return (1);
	init_value(env_list, envp);
	// cur_node = env_list->header_node;
	// while (cur_node)
	// {
	// 	printf("cur_node.key : %s\n", cur_node->key);
	// 	printf("cur_node.value : %s\n", cur_node->value);
	// 	cur_node = cur_node->next_node;
	// }
	// env_cmd(env_list, char **argument);
	// export_cmd(env_list, char **argument);
	// unset_cmd(env_cmd(env_list))
	/*
	while (1)
	{
		// isatty(STDIN)
		input = readline("pepsi zero>");
		// "12345 "6
		// printf("%lu\n", strlen(input));
		preprocess(input);
		add_history(input);
	}
	*/
	return (0);
}
