/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 19:53:36 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/11 12:11:39 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command_compound.h"
#include "command.h"
#include "token.h"

void	print_command_content(t_list *command);

void	print_token_content(t_list *token_list, char *tab)
{
	int			types;
	int			i;
	static char	*token_names[13] = {"TOKEN_NORMAL", "TOKEN_REDIR",
		"TOKEN_HEREDOC", "TOKEN_REDIRARG", "TOKEN_SQUOTE",
		"TOKEN_DQUOTE", "TOKEN_CONCAT", "TOKEN_PIPE", "TOKEN_LBRACKET",
		"TOKEN_RBRACKET", "TOKEN_LOGICAL", "TOKEN_WILDCARD",
		"TOKEN_IGNORE"};

	while (token_list)
	{
		types = get_token_type(token_list);
		printf("\n");
		printf("\033[0;35m%stoken content:\t%s\033[m\n", tab,
			((t_token *)(token_list->node))->data);
		printf("\033[0;35m%stoken types:\033[m\t", tab);
		i = -1;
		while (++i < 13)
			if (types >> i & 1)
				printf("\033[0;35m%s \033[m", token_names[i]);
		printf("\n");
		token_list = token_list->next;
	}
}

void	print_simple_content(t_list *command, char *tab)
{
	int			types;
	int			i;
	static char	*simple_names[5] = {"SIMPLE_PIPE", "SIMPLE_LBRACKET",
		"SIMPLE_RBRACKET", "SIMPLE_AND", "SIMPLE_OR"};

	types = get_command_type(command);
	printf("\n");
	if (types & SIMPLE_NORMAL)
	{
		printf("%s\033[0;36m%s \033[m", tab, "SIMPLE_NORMAL");
		if (get_command(command)->l1)
		{
			printf("%s\033[0;36m\n\n\t%s\033[m\n", tab, "ARGUMENTS");
			print_token_content(get_command(command)->l1, "\t");
		}
		if (get_command(command)->l2)
		{
			printf("\033[0;36m\n\t%s\033[m\n", "RERIECTIONS");
			print_token_content(get_command(command)->l2, "\t");
		}
	}
	i = -1;
	while (++i < 5)
		if (types >> i & 1)
			printf("\033[0;35m%s \033[m\n", simple_names[i]);
}

void	print_compound_content(t_list *command)
{
	printf("\n");
	if (get_command_type(command) == COMPOUND_PIPELINE)
		printf("\033[0;31m%s \033[m\n", "COMPOUND_PIPELINE::START");
	else
		printf("\033[0;31m%s \033[m\n", "COMPOUND_SUBSHELL::START");
	print_command_content(get_command(command)->l1);
	printf("\033[0;31m::END \033[m\n");
}

void	print_command_content(t_list *command)
{
	while (command)
	{
		if (get_command_type(command) & (COMPOUND_PIPELINE | COMPOUND_SUBSHELL))
			print_compound_content(command);
		else
			print_simple_content(command, "");
		command = command->next;
	}
}
