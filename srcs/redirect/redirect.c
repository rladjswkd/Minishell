/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:17:37 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 09:36:13 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "linked_list.h"
#include "lexer.h"
#include "redirect.h"
#include "utils.h"


/*
	- redirection check
	- open file using that redireciton option and then return the fd!
	- dup2으로 연결
*/

static int	get_redirection_flag(t_token *token)
{
	char	*redir_val;

	redir_val = token->data;
	if (token->types & TOKEN_HEREDOC)
		return (HERE_DOC);
	else if (ft_strncmp(">>", redir_val, max_nonnegative(">>", redir_val)) == 0)
		return (APPEND);
	else if (ft_strncmp("<", redir_val, max_nonnegative("<", redir_val)) == 0)
		return (INPUT);
	else if (ft_strncmp(">", redir_val, max_nonnegative(">", redir_val)) == 0)
		return (OUTPUT);
	return (-1);
}

/*
static int	check_redirect_bound(t_token *token)
{
	if (token == NULL)
		return (-1);
	if (token->types & TOKEN_HEREDOC
		|| ft_strncmp("<" ,token->data , max_nonnegative("<" , token->data)))
		return (INBOUND);
	else if (ft_strncmp(">>" ,token->data , max_nonnegative(">>" , token->data))
		|| ft_strncmp(">" ,token->data , max_nonnegative(">" , token->data)))
		return (OUTBOUND);
	return (-1);
}
*/

static int	get_redirect_fd(t_redirection_flag redirection_flag, char *file_name)
{
	int	file_fd;

	if (file_name == NULL)
		return (-1);
	file_fd = -1;
	if (redirection_flag == INPUT)
		file_fd = open(file_name, O_RDONLY, 0644);
	else if (redirection_flag == OUTPUT)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else if (redirection_flag == HERE_DOC)
		file_fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (redirection_flag == APPEND)
		file_fd = open(file_name, O_CREAT | O_RDWR, 0644);
	else
		ft_putstr_fd("unknown redirection_flag.\n", STDERR_FILENO);
	return (file_fd);
}

// bound, 
static int redirect_bound_process(t_list *redirect_node, t_list *data_node)
{
	int		redirect_flag;
	char	*file_name;
	int		status;

	status = 0;
	if (redirect_node == NULL || data_node == NULL)
		return (-1);
	file_name = get_token(data_node)->data;
	if (file_name == NULL )
		return (-1);
	redirect_flag = get_redirection_flag(get_token(redirect_node));
	if (redirect_flag == HERE_DOC || redirect_flag == INPUT)
		status = input_redirect(file_name);
	else if (redirect_flag == OUTPUT)
		status = output_redirect(file_name);
	else if (redirect_flag == APPEND)
		status = append_redirect(file_name);
	else
		status = -1;
	return (status);
}

/*
	- expasion으로 합쳐주었다는 가정!
	그러므로 짝수개씩 들어오게 된다.
	그렇지 않다면 이전에 parse 혹은 expansion에서 걸러준다.
	- 시작이 redirec type을 가지고 있어야만하며, 그 다음은 꼭 인자들이어야한다.
*/
int	redirection(t_list *redir_list)
{
	t_list	*cur_node;
	t_token	*token;
	int		fd;
	int		status;

	cur_node = redir_list;
	status = 0;
	while (cur_node)
	{
		token = get_token(cur_node);
		if (token->types & TOKEN_REDIR && cur_node->next)
		{
			// redirec status는 어떻게 처리할 것인가?
			status = redirect_bound_process(cur_node, cur_node->next);
			if (cur_node->next == NULL || cur_node->next->next == NULL)
				return (status);
			cur_node = cur_node->next->next; 
		}
		else if (redir_list != cur_node)// expansion에서 합칠것이긴 하지만 혹시 모르므로 REDIR 타입이 아니면 서로 합친다?
			cur_node = cur_node->next; // < file_name_ing"add_filename" 이런 형식으로 되어있는 경우를 대비.
		else
			return (-1);//error
		// printf("token->data : %s\n", token->data);
		// printf("token->types : %d\n", token->types);
		// cur_node = cur_node->next;
	}
	return (status);
}
/**/