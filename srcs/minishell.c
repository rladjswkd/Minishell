/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/31 11:02:34 by jim              ###   ########.fr       */
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

static int	test_heredoc_fd(t_list **redirect_list)
{
	t_list	*redirect_node;
	t_list	*heredoc_word_node;
	// test
	int    read_size;
	char   buf[1152];

	redirect_node = *redirect_list;
	while (redirect_node && redirect_node->next)
	{
		if (get_token(redirect_node)->types & TOKEN_HEREDOC)
		{
			heredoc_word_node = redirect_node->next;
			// get_token(heredoc_word_node)->heredoc_fd = heredoc_fd;
			read(get_token(heredoc_word_node)->heredoc_fd, buf, 1152);
			printf("buf in test_heredoc_hd() : %s\n", buf);
		}
		redirect_node = redirect_node->next->next;
	}
	if (redirect_node)
		return (-1);
	return (1);
}

int test_read_herdoc(t_list *parse_list)
{
	t_list	*parse_node;
	t_list	*redirect_list;

	if (parse_list == NULL)
		return (-1);
	parse_node = parse_list;
	while (parse_node)
	{
		if (get_command_type(parse_node) == SIMPLE_NORMAL)
		{
			redirect_list = get_simple(parse_node)->redirs;
			test_heredoc_fd(&redirect_list);
			parse_node = parse_node->next;
		}
		else if (get_command_type(parse_node) == COMPOUND_PIPELINE \
				|| get_command_type(parse_node) == COMPOUND_SUBSHELL)
			parse_node = get_compound(parse_node)->list;
	}
	return (1);
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
		print_command_content(parsed_header.next);
		execute_processing(env_list, parsed_header.next, FALSE);
		add_history(input);
		// error 발생시 free시키는 조건을 일괄적으로 할 필요가 있다.
		if (reset_in_out_fd(io_backup) < 0)
			return (1); // free
	}
	/*	free_init_value*/
	return (0);
}
