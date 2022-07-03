/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/07/02 16:08:56 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/errno.h>
// t_pipe_info;
// cat a > b > c

size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

static void	save_free(char **something)
{
	free(*something);
	*something = NULL;
}

static char	**free_word_list(char **word_list, int idx)
{
	while (idx >= 0)
	{
		save_free(&word_list[idx]);
		free(word_list);
		word_list = NULL;
		idx--;
	}
	return (word_list);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (src[i] != '\0')
		i++;
	if (dstsize == 0)
		return (i);
	while ((k < dstsize - 1) && src[k])
	{
		dst[k] = src[k];
		k++;
	}
	dst[k] = '\0';
	return (i);
}

static char	**alloc_word(int argc, char **argv)
{
	char	**word_list;
	size_t	idx;

	word_list = (char **)malloc(sizeof(char *) * argc);
	if (word_list == NULL)
		return (NULL);
	idx = 1;
	while (idx < argc)
	{
		word_list[idx] = (char *)malloc(sizeof(char) * (ft_strlen(argv[idx]) + 1));
		if (word_list[idx] == NULL)
			return (free_word_list(word_list, (int)idx));
		ft_strlcpy(word_list[idx], argv[idx], ft_strlen(argv[idx]) + 1);
		idx++;
	}
	return (word_list);
}

int	dup_from_to(t_fd from, t_fd to)
{
	if (dup2(from, to) < 0)
		return (ERROR);
	return (SUCCESS);
}

// file == 3
// STDOUT = 1
/*
	fd는 같다 하지만 dup2를 쓰면 가리키곳이 달라진다.
*/
int	redirec_out(char *file_name, int *from, int *to, int idx)
{
	*from = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (dup2(*from, *to) < 0)
		return (ERROR);
	close(*to);
	return (SUCCESS);
}

int	main(int argc, char **argv)
{
	char	**file_list;
	int		open_fd;
	size_t	idx;
	t_fd	as_is;
	t_fd	to_be;
	char	buf[42];

	if (argc < 2)
		return (1);
	file_list = alloc_word(argc, argv);
	if (file_list == NULL)
		return(1);
	as_is = -1;
	to_be = STDOUT_FILENO;
	idx = 1;
	open_fd = open(argv[1], O_RDONLY, 0777);
	printf("argv[1] : %s\n", argv[1]);
	printf("open_fd : %d\n", open_fd);
	dup2(open_fd, STDIN_FILENO);
	close(open_fd);
	printf("read size : %zd\n", read(STDIN_FILENO, buf, 42));
	printf("read from STDIN_FILENO fd  : %s\n", buf);
	// open(argv[1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	// while (idx < argc)
	// {
	// 	redirec_out(file_list[idx], &as_is, &to_be, idx);
	// 	// to_be
	// 	idx++;
	// }
	// printf("as_is : %d\n", as_is);
	// printf("to_be : %d\n", to_be);
	// write(to_be, "test\n", 6);
	// close(to_be);
	return (0);
}

/*
	- 파이프를 열고 이전 명령어 블록에서 다음 명령어 블록으로 이어준다.
	- 즉, 첫번째 자식의 STDOUT을 pipe[WRITE_END]에 저장한다.
		두번쨰 자식의 STDINd을 pipe[READ_END]에 저장한다.
*/