/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 20:01:02 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:21:40 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "structure_linked_list.h"

typedef struct s_pattern_info
{
	char	*pattern;
	int		*wildcard_pattern_flag;
	char	*normal_str;
	char	prev_char;
}				t_pattern_info;

char	**get_cur_dir_file_list(void);

int		get_pattern_alloc_size(t_list *start_node, t_list *end_node);
char	*get_organized_pattern(t_list *start_node, t_list *end_node, \
								int *wildcard_pattern_flag);
int		*get_wildcard_pattern_flag(t_list *start_node, t_list *end_node);

t_list	*get_pattern_matched_list(char *pattern, \
								char **cur_dir_file_list, \
								int *wildcard_pattern_flag);
int		concat_matched_list_to_org_list(t_list **start_node, \
										t_list **end_node, \
										t_list *matched_list);

#endif
