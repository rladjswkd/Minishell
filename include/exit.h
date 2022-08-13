/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:36:30 by jim               #+#    #+#             */
/*   Updated: 2022/08/13 20:56:20 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "env_list.h"
# include "structure_linked_list.h"
# include <sys/wait.h>

int		*get_exit_status(void);
void	update_exit_status(int status);
int		handle_status(int status);

#endif
