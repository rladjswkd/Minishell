/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/19 20:32:40 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 01:02:06 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include <sys/types.h>
# include "linked_list.h"

typedef struct s_process_info
{
	pid_t	pid;
	int		status;
	int		process_count;
}			t_process_info;

typedef struct s_pipelist_info
{
	t_list	*start_node;
	t_list	*cur_node;
}				t_pipelist_info;

#endif