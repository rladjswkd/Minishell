/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:15:57 by jim               #+#    #+#             */
/*   Updated: 2022/06/30 17:25:14 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "env_list.h"

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

int		cd_cmd(char **path);
char	*pwd_cmd(void);
int		echo_cmd(const char **arg_list);
void	exit_cmd(const char **status);
int		env_cmd(t_env_list *env_list, const char **argument);
int		export_cmd(t_env_list *env_list, const char **argument);
int		unset_cmd(t_env_list *env_list, const char **argument);

#endif
