/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:32:31 by jim               #+#    #+#             */
/*   Updated: 2022/06/05 22:31:17 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "stddef.h"
# define OPEN_MAX 10240

typedef enum e_buffer_len
{
	BUFFER_SIZE = 42,
}			t_buffer_len;

char	*get_next_line(int fd);
char	*get_next_line_from_save(char **save, int newline_idx);
size_t	ft_strlcat(char *dst, char *src, size_t dstsize);
char	*return_remain(char **save, int read_siz);

char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, int c);

#endif
