/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:32:38 by jim               #+#    #+#             */
/*   Updated: 2022/08/10 18:08:58 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "linked_list.h"

typedef struct s_heredoc_node
{
	int		fd;
}				t_heredoc_node;

int	heredoc_routine(char *heredoc_word);
int	create_heredoc_tmp_file(char **file_name);
int	concat_heredoc_word_list(t_list *list);

#endif