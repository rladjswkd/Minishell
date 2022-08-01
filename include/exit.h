/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:36:30 by jim               #+#    #+#             */
/*   Updated: 2022/08/01 23:49:44 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "env_list.h"
# include "linked_list.h"

int *get_exit_status();
int update_exit_status(int status, t_list *org_list);

#endif