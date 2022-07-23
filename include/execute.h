/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:33:03 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 21:25:35 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include "linked_list.h"
#include "env_list.h"

int		execute_processing(t_env_list *env_list, t_list *parse_list);
int		pipeline_processing(t_env_list *env_list, t_list *pipeline_list);
int		execute_cmd(char **envp, char **cmd);
int	    simple_cmd(t_env_list *env_list, t_list *parse_list);

char	**list_to_array(t_list *env_list);
char	**env_list_to_array(t_env_list *env_list);

int		check_builtin(t_list *cmd_list);
int		builtin_process(t_env_list *env_list, t_list *parse_list);

//debug
void	print_command_content(t_list *command); // remove

#endif