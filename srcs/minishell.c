/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/08/01 16:27:27 by jim              ###   ########.fr       */
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
#include <string.h>
#include <sys/errno.h>

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
	int			io_backup[2];

	// signal(SIGQUIT, SIG_IGN);
	// signal(SIGINT, handler);
	if (init_value(&env_list, envp, io_backup) < 0)
		return (1);
	while (1)
	{
		// printf("error code before readline : %s\n", strerror(errno));
		input = readline("pepsi zero> ");
		if (input == NULL)
			exit(1);
		if (!input[0])
			continue ;
		if (preprocess(input, &parsed_header))
			continue ;
		// expansion_and_heredoc(env_list, parsed_header.next);
		// print_command_content(parsed_header.next);
		execute_processing(env_list, parsed_header.next, FALSE, &parsed_header);
		add_history(input);
		// error 발생시 free시키는 조건을 일괄적으로 할 필요가 있다.
		if (reset_in_out_fd(io_backup) < 0)
			return (1); // free
	}
	/*	free_init_value*/
	return (0);
}
