/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 11:51:44 by jim              ###   ########.fr       */
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
#include "execute.h"
#include "lexer.h"
#include "heredoc.h"
//debug
#include <stdlib.h>
#include "linked_list.h"

/*
void	handler(int signum)
{
	if (signum != SIGINT)
		return ;
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}
*/

// for display, will be removed
static void	display_env_list(t_env_list	*env_list)
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

static int	add_node(t_list **new_node)
{
	*new_node = (t_list *)malloc(sizeof(t_list));
	if (*new_node == NULL)
		return (-1);
	(*new_node)->next = NULL;
	(*new_node)->node = NULL;
	return (1);
}

static t_list	*create_list()
{
	t_list	*new_list;

	new_list = (t_list *)malloc(sizeof(t_list));
	if (new_list == NULL)
		return (NULL);
	new_list->next = NULL;
	new_list->node = NULL;
	return (new_list);
}

static int	preprocess(char *input, t_list *parsed_header)
{
	t_list		token_header;

	if (!lexer(input, &token_header))
	{
		printf("%s\n", "syntax error");
		return (1);
	}
	if (!parser(token_header.next, parsed_header))
	{
		printf("%s\n", "parser error");
		// free(token_header);
		// free(parsed_header);
		return (2);
	}
	// heredoc_processing();
	return (0);
		
}

static int	reset_in_out_fd(int io_backup[2])
{
	if (dup2(io_backup[0], STDIN_FILENO) < 0
		|| dup2(io_backup[1], STDOUT_FILENO) < 0)
		return (-1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env_list	*env_list;
	t_list		parsed_header;
	t_list		heredoc_list;
	int			io_backup[2];

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handler);
	if (init_value(&env_list, envp, io_backup) < 0)
		return (1);
	while (1)
	{
		input = readline("pepsi zero> ");
		if (input == NULL)
			exit(1);
		if (!input[0])
			continue ;
		if (preprocess(input, &parsed_header))
			continue ;
		parse_to_heredoc(parsed_header.next, &heredoc_list);
		execute_processing(env_list, parsed_header.next, FALSE);
		add_history(input);
		// error 발생시 free시키는 조건을 일괄적으로 할 필요가 있다.
		if (reset_in_out_fd(io_backup) < 0)
			return (1); // free
	}
	/*	free_init_value*/
	return (0);
}
