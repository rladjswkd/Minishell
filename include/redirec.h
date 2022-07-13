/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 15:35:06 by jim               #+#    #+#             */
/*   Updated: 2022/07/13 15:36:27 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIREC_H
# define REDIREC_H

typedef enum e_redirection_flag
{
	NONE,
	INPUT,
	OUTPUT,
	HERE_DOC,
	APPEND,
}				t_redirection_flag;

typedef enum e_file_flag
{
	FILE_READ,
	FILE_WRITE,
	FILE_APPEND,
	FILE_RDWR,
	FILE_WRONLY,
}				t_file_flag;


#endif
