/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/08/13 21:58:05 by jim              ###   ########seoul.kr  */
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
#include "heredoc.h"
#include "ft_signal.h"
#include "structure_linked_list.h"
#include "lexer.h"
#include "parser.h"
#include "constants.h"
#include "lexer_util.h"
#include "destruct.h"
#include <stdlib.h>

static int	preprocess(char *input, t_list *parsed_header)
{
	t_list	token_header;

	if (!lexer(input, &token_header)
		|| !parser(token_header.next, parsed_header))
	{
		free(input);
		return (1);
	}
	return (0);
}

static int	reset_in_out_fd(int io_backup[2])
{
	if (dup2(io_backup[0], STDIN_FILENO) < 0
		|| dup2(io_backup[1], STDOUT_FILENO) < 0)
		return (-1);
	return (0);
}

static int	check_input(char **input)
{
	*input = readline("pepsi zero> ");
	if (*input == NULL)
	{
		printf("exit\n");
		exit(EXIT_FAILURE);
	}
	if (is_all_whitespaces(*input))
	{
		free(*input);
		return (1);
	}
	return (0);
}

static int	wrapper_free_input_and_parse(char **input, t_list *parse_list, \
										int ret_val)
{
	safe_free(input);
	free_command_list(parse_list);
	parse_list = NULL;
	return (ret_val);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_env_list	*env_list;
	t_list		parsed_header;
	int			io_backup[2];

	(void)argc;
	(void)argv;
	signal_processing();
	if (init_value(&env_list, envp, io_backup) < 0)
		return (1);
	while (1)
	{
		if (check_input(&input))
			continue ;
		if (preprocess(input, &parsed_header))
			continue ;
		execute_processing(env_list, parsed_header.next, FALSE);
		add_history(input);
		if (reset_in_out_fd(io_backup) < 0)
			return (wrapper_free_input_and_parse(&input, \
					parsed_header.next, 1));
	}	
	delete_env_list(&env_list);
	return (0);
}
