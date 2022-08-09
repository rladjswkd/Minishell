/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:36:30 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 17:27:00 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "env_list.h"
# include "linked_list.h"
#include <sys/wait.h>

int		*get_exit_status();
void	update_exit_status(int status, t_list *org_list);
int	    handle_status(int status);

#endif