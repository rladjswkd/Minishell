/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:32:38 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:20:47 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H
# include "structure_linked_list.h"

typedef struct s_heredoc_node
{
	int		fd;
}				t_heredoc_node;

int	heredoc_routine(char *heredoc_word);
int	create_heredoc_tmp_file(char **file_name);
int	concat_heredoc_word_list(t_list *list);

#endif
