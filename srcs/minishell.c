/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 22:49:58 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 18:24:50 by jim              ###   ########.fr       */
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

static void	builtin_test(char *input, t_env_list *env_list)
{
	char		**word_list;
	char		*cmd;
	char		**argv;

	word_list = ft_split(input, ' ');
	if (word_list == NULL)
		return ;
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

t_c_token   *create_token()
{
    t_c_token    *token_node;

    token_node = (t_c_token *)malloc(sizeof(t_c_token));
    if (token_node == NULL)
		return (NULL);
	token_node->str = NULL;
	token_node->flags = 0;
    return (token_node);
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

t_c_scmd   *create_t_c_scmd()
{
    t_c_scmd    *scmd_node;

    scmd_node = (t_c_scmd *)malloc(sizeof(t_c_scmd));
    if (scmd_node == NULL)
		return (NULL);
	scmd_node->redirs = NULL;
	scmd_node->args = NULL;
    return (scmd_node);
}

/*
- 첫 노드는 header로 쓴다. 값을 담지 않는다.
- pipe 혹은 ()a맏
*/
static int	add_parse_list(t_list *plist)
{
	t_list		*cur_node;
	t_c_scmd	*scmd_node;
	t_c_token	*token;
	int			idx;

	if (plist == NULL)
		return (-1);
	cur_node = plist;
	// pipe단위로 추가된다.
	// (t_c_scmd *)와 세트로 다닌다.
	while (cur_node && cur_node->next)
		cur_node = cur_node->next;
	if (add_node(&(cur_node->next)) == -1)
	{
		free_linked_list(&plist);
		return (-1);
	}
	// 첫번쨰 노드는 header로 둔다.(아무 값도 넣지 않는다.)
	cur_node = cur_node->next;
	scmd_node = create_t_c_scmd();
	if (scmd_node == NULL)
	{
		free_linked_list(&plist);
		return (-1);
	}
	cur_node->node = scmd_node;
	return (1);
}

static t_list	*str_to_list(t_list *parse_list, char *str)
{
	t_list		*args_list;
	t_list		*cur_node;
	char		**arr_list;
	int			idx;

	arr_list = ft_split(str, ' ');
	if (arr_list == NULL)
	{
		free(parse_list);
		return (NULL);
	}
	if (add_parse_list(parse_list) < 0)
	{
		free(parse_list);
		return (NULL);
	}
	// cur_node->next = NULL;
	idx = 0;
	cur_node = create_list();
	if (cur_node == NULL)
		return (NULL);
	((t_c_scmd *)(parse_list->next->node))->args = cur_node;
	while (arr_list[idx])
	{
		if (add_node(&(cur_node->next)) == -1)
		{
			free_list(&arr_list);
			free_linked_list(&parse_list);
			return (NULL);
		}
		cur_node = cur_node->next;
		cur_node->node = create_token();
		if (cur_node->node == NULL)
		{
			free_list(&arr_list);
			free_linked_list(&parse_list);
		}
		((t_c_token *)(cur_node->node))->str = ft_strdup(arr_list[idx]);
		if (((t_c_token *)(cur_node->node))->str == NULL)
		{
			// token의 str list를 지워야한다.
			free_list(&arr_list);
			free_linked_list(&parse_list);
			return (NULL);
		}
		idx++;
		
	}
	args_list = ((t_c_scmd *)(parse_list->next->node))->args;
	return (args_list);
	
}


static void	display_list(t_list	*plist)
{
	t_list		*cur_node;
	t_c_token	*token;

	cur_node = plist->next;
	while (cur_node)
	{
		token = (t_c_token *)(cur_node->node);
		printf("token->str : %s\n", token->str);
		cur_node = cur_node->next;
	}
}
/*
	- input str to linked list
		to using split
	- execute_process(t_env_list *env_list, t_list *cmd_list)
*/
static int	scmd_test(char *input, t_env_list *env_list)
{
	t_list	*parse_list;
	t_list	*cmd_list;

	parse_list = create_list();
	if (parse_list == NULL)
		return (-1);
	if (add_parse_list(parse_list) < 0)
		return (-1);
	cmd_list = str_to_list(parse_list, input);
	// display_list(cmd_list);
	execute_process(env_list, cmd_list);
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
	// display_env_list(env_list);
	while (1)
	{
		// isatty(STDIN)
		input = readline("pepsi zero>");
		// builtin_test(input, env_list);
		// display_linked_list
		scmd_test(input, env_list);
		// preprocess(input);
		// add_history(input);
	}
	/*	*/
	/**/
	return (0);
}
