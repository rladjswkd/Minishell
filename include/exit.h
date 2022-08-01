/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 17:36:30 by jim               #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/08/01 08:17:15 by jim              ###   ########.fr       */
=======
/*   Updated: 2022/08/01 13:50:52 by jim              ###   ########.fr       */
>>>>>>> c885569a85f37038920567a5b0483fffaa655a79
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H
# include "env_list.h"
# include "linked_list.h"

int *get_exit_status();
<<<<<<< HEAD
int update_exit_status(int status, t_list *parse_list);
=======
int update_exit_status(int status, t_list *org_list);
>>>>>>> c885569a85f37038920567a5b0483fffaa655a79

#endif