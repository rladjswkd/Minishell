/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:32:31 by jim               #+#    #+#             */
/*   Updated: 2022/06/14 15:47:42 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define OPEN_MAX 255
# define BUFFER_SIZE 42

# include <unistd.h>
# include <stdlib.h>

typedef enum e_bool_flag
{
	FALSE = 0,
	TRUE = 1,
}				t_e_bool_flag;

/* orign */
char	*get_next_line(int fd);
char	*get_next_line_from_save(char **save, int newline_idx);
char	*return_remain(char **save, int read_siz);
/* util */
int		ft_strchr(char *s, int c);

#endif
