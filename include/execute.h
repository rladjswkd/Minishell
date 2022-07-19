/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 16:33:03 by jim               #+#    #+#             */
/*   Updated: 2022/07/19 08:10:54 by jim              ###   ########.fr       */
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

typedef struct s_token_content
{
	int		flags;
	char	*str;
}	t_c_token;

int		execute_process(t_env_list *env_list, t_list *cmd_list);
int		execute_cmd(char **envp, char **cmd);
char	**list_to_array(t_list *env_list);
char	**env_list_to_array(t_env_list *env_list);

#endif