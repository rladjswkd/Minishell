/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:46:10 by jim               #+#    #+#             */
/*   Updated: 2022/07/30 17:25:03 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

#include "linked_list.h"
#include "env_list.h"

typedef enum e_dollar_expansion_flag
{
	VARIABLE,
	NORMAL,
}			t_dollar_expansion_flag;

typedef enum e_check_dollar_expansion_flag
{
	NOT_CHANGED,
	CHANGED,
}			t_check_dollar_expansion_flag;

typedef struct s_sub_str_info
{
	size_t	len;
	char	*start_of_word;
}				t_sub_str_info;

int	dollar_sign_conversion(t_env_list *env_list, t_token *token);

#endif