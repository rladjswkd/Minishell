/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 14:08:25 by jim               #+#    #+#             */
/*   Updated: 2022/08/14 01:20:24 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>  // readline이전에 stdio를 include해야한다 왜?
#include <readline/readline.h>
#include "token.h"
#include "heredoc.h"
#include "expansion.h"
#include "utils.h"
#include "ft_error.h"

static int	get_readline(int tmp_file_fd, char *heredoc_word)
{
	char	*read_str;
	char	*with_newline;

	while (1)
	{
		read_str = readline("$>");
		if (read_str == NULL)
			return (-1);
		if (ft_strncmp(read_str, heredoc_word, \
			max_nonnegative(read_str, heredoc_word)) == 0)
		{
			safe_free(&read_str);
			break ;
		}
		with_newline = ft_strjoin(read_str, "\n");
		safe_free(&read_str);
		if (with_newline == NULL)
			return (error_handler(NULL, heredoc_word, ALLOC_FAIL, -1));
		write(tmp_file_fd, with_newline, ft_strlen(with_newline));
		safe_free(&with_newline);
	}
	return (1);
}

static int	get_tmp_file_fd_for_read(char *file_name)
{
	int	open_fd;

	open_fd = open(file_name, O_RDONLY, 0666);
	unlink(file_name);
	if (open_fd < 0)
		return (-1);
	return (open_fd);
}

int	concat_heredoc_word_list(t_list *list)
{
	if (get_token(list)->types & TOKEN_CONCAT
		&& list->next)
	{
		if (concat_list_in_condition(list) < 0)
			return (-1);
	}
	return (0);
}

/*
	- 반환값은 fd이다!
	- heredoc 입력값을 임시파일에 저장하며 
	  처리가 끝나면 임시파일을 삭제한 뒤 
	  미리 open한 임시파일을 fd를 반환한다.
	  만약 error가 중간에 발생했다면 STDIN_FILENO로 반환한다.
*/
int	heredoc_routine(char *heredoc_word)
{
	int		tmp_file_fd;
	char	*file_name;

	tmp_file_fd = create_heredoc_tmp_file(&file_name);
	if (tmp_file_fd < 0)
		return (STDIN_FILENO);
	if (get_readline(tmp_file_fd, heredoc_word) < 0)
	{
		unlink(file_name);
		close(tmp_file_fd);
		safe_free(&file_name);
		return (STDIN_FILENO);
	}
	close(tmp_file_fd);
	tmp_file_fd = get_tmp_file_fd_for_read(file_name);
	safe_free(&file_name);
	if (tmp_file_fd < 0)
		return (STDIN_FILENO);
	return (tmp_file_fd);
}
