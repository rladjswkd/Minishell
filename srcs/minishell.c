/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/03 20:35:45 by jim              ###   ########seoul.kr  */
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
#include "utils.h"
#include "builtin.h"
//debug
#include <stdlib.h>
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

// for display, will be removed
static void	display_list(t_env_list	*env_list)
{
	t_env_node	*cur_node;

	cur_node = env_list->header_node;
	while (cur_node)
	{
		printf("cur_node.key : %s\n", cur_node->key);
		printf("cur_node.value : %s\n", cur_node->value);
		cur_node = cur_node->next_node;
	}
}
/*
	- cmd argment순서로 입력
	- free();

	// const char	*cmd_list = {"exit_cmd", "env_cmd", "export_cmd", "unset_cmd", \
	// 						"cd_cmd", "pwd_cmd", "echo_cmd"};
	// int			(*builtin)(char **);
*/
static void	builtin_test(char *input, t_env_list *env_list)
{
	char		**word_list;
	char		*cmd;
	char		**argv;

	word_list = ft_split(input, ' ');
	if (word_list == NULL)
		ft_putstr_fd("word list is null", STDERR_FILENO);
	cmd = word_list[0];
	argv = &word_list[1];
	printf("cmd : %s\n*argv : %s\n", cmd, *argv);
	if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		exit_cmd(argv);
	else if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		echo_cmd(argv);
	else if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		cd_cmd(argv, env_list);
	else if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		pwd_cmd();
	else if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		env_cmd(env_list, argv);
	else if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		export_cmd(env_list, argv);
	else if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		unset_cmd(env_list, argv);
	free_list(&word_list);
	free(input);
	input = NULL;
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	int			fd;
	t_env_list	*env_list;

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handler);
	env_list = create_env_list();
	if (env_list == NULL)
		return (1);
	if (init_value(env_list, envp) < 0)
		return (1);
	while (1)
	{
		// isatty(STDIN)
		input = readline("pepsi zero>");
		builtin_test(input, env_list);
		// preprocess(input);
		// add_history(input);
	}
	/**/
	return (0);
}
