/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:15:57 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 16:37:19 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env_list.h"
# define LONGLONG_MAX_STR "9223372036854775807"
# define LONGLONG_MIN_STR "-9223372036854775808"

typedef enum e_tf_flag
{
	FALSE,
	TRUE,
}			t_tf_flag;

typedef enum e_sf_flag
{
	FAIL = -1,
	SUCCESS,
}			t_sf_flag;

int		cd_cmd(char **path, t_env_list *env_list);
int		pwd_cmd(void);
int		echo_cmd(char **argument);
int		exit_cmd(char **status, int is_child);
int		env_cmd(t_env_list *env_list);
int		export_cmd(t_env_list *env_list, char **argument);
int		unset_cmd(t_env_list *env_list, char **argument);

#endif
