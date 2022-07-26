/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:32:38 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 17:16:22 by jim              ###   ########seoul.kr  */
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
int	heredoc_fd_to_list(t_list *list, int fd);

int	create_heredoc_tmp_file(char **file_name);
int parse_to_heredoc(t_list *parse_list, t_list *heredoc_list);

#endif