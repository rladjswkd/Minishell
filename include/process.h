/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:32:40 by jim               #+#    #+#             */
/*   Updated: 2022/07/20 19:35:18 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
#include <sys/types.h>


typedef struct s_process_info
{
	pid_t	pid;
	int		status;
}			t_process_info;

#endif