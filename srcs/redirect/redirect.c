/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:17:37 by jim               #+#    #+#             */
/*   Updated: 2022/08/14 17:27:46 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
#include <string.h>
#include <stdlib.h>
#include "heredoc.h"
#include "redirect.h"
#include "token.h"
#include "utils.h"
#include "ft_error.h"

static int	get_redirection_flag(t_token *token)
{
	char	*redir_val;

	redir_val = token->data;
	if (token->types & TOKEN_HEREDOC)
		return (HEREDOC);
	else if (ft_strncmp(">>", redir_val, max_nonnegative(">>", redir_val)) == 0)
		return (APPEND);
	else if (ft_strncmp("<", redir_val, max_nonnegative("<", redir_val)) == 0)
		return (INPUT);
	else if (ft_strncmp(">", redir_val, max_nonnegative(">", redir_val)) == 0)
		return (OUTPUT);
	return (-1);
}

static int	redirect_bound_process(t_list *redirect_node, t_list *data_node)
{
	int		redirect_flag;
	char	*file_name;
	int		status;

	status = 0;
	if (redirect_node == NULL || data_node == NULL)
		return (1);
	file_name = get_token(data_node)->data;
	if (file_name == NULL )
		return (1);
	redirect_flag = get_redirection_flag(get_token(redirect_node));
	if (redirect_flag == HEREDOC)
		status = heredoc_redirect(get_token(data_node));
	else if (redirect_flag == INPUT)
		status = input_redirect(file_name);
	else if (redirect_flag == OUTPUT)
		status = output_redirect(file_name);
	else if (redirect_flag == APPEND)
		status = append_redirect(file_name);
	else
		status = 1;
	return (status);
}

static int	redirect_ordinary_case(t_list *cur_node, int is_child)
{
	int	status;

	status = redirect_bound_process(cur_node, cur_node->next);
	if (status < 0)
	{
		print_error(SHELL_NAME, NULL, get_token(cur_node->next)->data, \
					strerror(errno));
		status = 1;
		if (is_child)
			exit(status);
	}
	return (status);
}

/*
	- redirect 데이터가 1개도 없거나
	- 2개이상일때 ambiguous(중의적) redirect error 발생
*/
static int	is_ambiguous_redirect(t_list **cur_node)
{
	if (get_token_type(*cur_node) & TOKEN_REDIR
		&& (*cur_node)->next == NULL)
		return (1);
	else if (get_token_type(*cur_node) & TOKEN_REDIR \
			&& (*cur_node)->next \
			&& ((*cur_node)->next->next \
				&& !(get_token_type((*cur_node)->next->next) & TOKEN_REDIR) \
				) \
			)
	{
		(*cur_node) = (*cur_node)->next;
		return (1);
	}
	return (0);
}

/*
	- expasion으로 합쳐주었다는 가정!
	그러므로 짝수개씩 들어오게 된다.
	그렇지 않다면 이전에 parse 혹은 expansion에서 걸러준다.
	- 시작이 redirec type을 가지고 있어야만하며, 그 다음은 꼭 인자들이어야한다.
	- * 같은 경우 2개 이상의 파일이 들어올수 있다 이런경우 
	bash: **redi*rect.***: ambiguous redirect를 출력한다.
*/
int	redirection(t_list *redir_list, int is_child)
{
	t_list	*cur_node;
	int		status;

	cur_node = redir_list;
	while (cur_node)
	{
		if (is_ambiguous_redirect(&cur_node))
			return (error_handler(NULL, get_token(cur_node)->data, \
					AMBIGUOUS_REDIRECT, 1));
		else if (get_token(cur_node)->types & TOKEN_REDIR && cur_node->next)
		{
			status = redirect_ordinary_case(cur_node, is_child);
			if (status)
				return (status);
			if (cur_node->next == NULL || cur_node->next->next == NULL)
				return (0);
			cur_node = cur_node->next->next;
		}
		else if (redir_list != cur_node)
			cur_node = cur_node->next;
		else
			return (1);
	}
	return (0);
}
