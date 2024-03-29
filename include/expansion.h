/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:46:10 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:55:05 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "structure_linked_list.h"
# include "structure_token.h"
# include "structure_simple.h"
# include "env_list.h"

typedef enum e_dollar_expansion_flag
{
	VARIABLE,
	NORMAL,
}			t_dollar_expansion_flag;

typedef enum e_check_dollar_flag
{
	NOT_CHANGED,
	CHANGED,
}			t_check_dollar_flag;

typedef struct s_sub_str_info
{
	t_token		*token;
	const char	*as_is_str;
	int			idx;
	size_t		len;
	size_t		start_idx;
}				t_sub_str_info;

int	expansion(t_env_list *env_list, t_simple *scmd_list);
int	expand_dollar_sign_in_every_node(t_env_list *env_list, \
								t_list **list);
int	dollar_sign_conversion(t_env_list *env_list, t_token *token);
int	expansion_str_split(t_token *token, t_list *tmp_expansion_list);
int	concat_tmp_expansion_list(t_token *token, t_list *tmp_expansion_list);
int	check_dollar_flag(int flag, t_sub_str_info sub_str_info);
int	wildcard_for_curdir(t_simple *scmd_list);

int	concat_list(t_simple *scmd_list);
int	concat_list_in_condition(t_list *list);

#endif
