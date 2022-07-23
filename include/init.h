/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:27:31 by jim               #+#    #+#             */
/*   Updated: 2022/07/23 13:15:58 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "env_list.h"

// int	init_value(t_env_list	*env_list, char **envp);
int	init_value(t_env_list	**env_list, char **envp, int io_backup[2]);

#endif
