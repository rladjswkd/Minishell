/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:33:03 by jim               #+#    #+#             */
/*   Updated: 2022/07/21 16:12:05 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "linked_list.h"
#include "env_list.h"
// temp
typedef struct s_scmd_content
{
	int		type;
	t_list	*args;
	t_list	*redirs;
}	t_c_scmd;

int		execute_processing(t_env_list *env_list, t_list *parse_list);
int		pipeline_processing(t_env_list *env_list, t_list *cmd_list);
int		execute_cmd(char **envp, char **cmd);
char	**list_to_array(t_list *env_list);
char	**env_list_to_array(t_env_list *env_list);

//debug
void	print_command_content(t_list *command); // remove

int		builtin_process(t_env_list *env_list, char **cmd);

#endif