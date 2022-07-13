/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 16:17:37 by jim               #+#    #+#             */
/*   Updated: 2022/07/13 16:22:49 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirec.h"

int	redirection(t_redirection_flag redirection_flag, char *file_name)
{
	int	file_fd;

	file_fd = -1;
	if (redirection_flag == INPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == OUTPUT)
		file_fd = file_open(FILE_READ, file_name);
	else if (redirection_flag == HERE_DOC)
		file_fd = file_open(FILE_RDWR, file_name);
	else if (redirection_flag == APPEND)
		file_fd = file_open(FILE_APPEND, file_name);
	else
		write(2, &"unknown redirection_flag\n.", \
				ft_strlen("unknown redirection_flag\n."));
	return (file_fd);
}
