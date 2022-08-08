/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/25 17:37:51 by jim               #+#    #+#             */
/*   Updated: 2022/07/05 17:17:50 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

static int	ft_alloc_word(char const *s, char c, char **word_list)
{
	size_t	idx;
	size_t	word_idx;
	size_t	begin_of_word;

	idx = 0;
	word_idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			idx++;
		else
		{
			begin_of_word = idx;
			while (s[idx] && s[idx] != c)
				idx++;
			word_list[word_idx] = \
			ft_substr(s, begin_of_word, (idx - begin_of_word));
			if (word_list[word_idx] == NULL)
				return (free_list(&word_list));
			word_idx++;
		}
	}
	word_list[word_idx] = 0;
	return (1);
}

static size_t	ft_word_cnt(char const *s, char c)
{
	size_t	word_cnt;
	size_t	idx;

	word_cnt = 0;
	idx = 0;
	while (s[idx])
	{
		if (s[idx] == c)
			idx++;
		else
		{
			word_cnt++;
			while (s[idx] && s[idx] != c)
				idx++;
		}
	}
	return (word_cnt);
}

int	free_list(char ***word_list)
{
	size_t			idx;

	if (word_list == NULL || *word_list == NULL)
		return (0);
	idx = 0;
	while ((*word_list)[idx])
	{
		free((*word_list)[idx]);
		(*word_list)[idx] = NULL;
		idx++;
	}
	free(*word_list);
	*word_list = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**word_list;
	size_t	word_cnt;
	int		alloc_flag;

	word_cnt = ft_word_cnt(s, c);
	if (word_cnt == 0)
		return (NULL);
	word_list = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (word_list == 0)
		return (0);
	alloc_flag = ft_alloc_word(s, c, word_list);
	if (alloc_flag == -1)
		return ((char **) NULL);
	return (word_list);
}
