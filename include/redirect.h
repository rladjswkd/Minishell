/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:35:06 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 09:40:50 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H
# include "linked_list.h"

typedef enum e_redirection_flag
{
	NONE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}				t_redirection_flag;

typedef enum e_file_flag
{
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
	FILE_RDWR,
	FILE_WRONLY,
}				t_file_flag;


int	redirection(t_list *redir_list);
int	append_redirect(char *file_name);
int	output_redirect(char *file_name);
int	input_redirect(char *file_name);

#endif
