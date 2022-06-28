/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/29 18:15:57 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 21:38:42 by jim              ###   ########seoul.kr  */
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

// int		change_directory_cmd(char const **path);
int		change_directory_cmd(const char *path);
char	*print_current_working_directory_cmd(void);
int		echo_cmd(char **arg_list);
void	exit_cmd(char **status);
// int		echo_cmd(char **arg_list, char **option);
int		env_cmd(t_env_list *env_list, char **argument);
int		export_cmd(t_env_list *env_list, char **argument);
int		unset_cmd(t_env_list *env_list, char **argument);

#endif
