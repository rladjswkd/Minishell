/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:25:48 by jim               #+#    #+#             */
/*   Updated: 2022/08/05 12:56:14 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <dirent.h>
#include "linked_list.h"
#include "lexer.h"
#include "utils.h"

/*
  매칭되는 것이 없다면 literal로 취급
  *만 들어오는 경우 현재 디렉토리에 있는 file or directory들을 넘겨준다.
  .*이 있는 경우에만 .을 가져온다
  *.* (총  2자 이상이야어햔다.   .으로 시작하는 것은 포함되지 않으며, .으로 끝나는건 가능하다.)
  pattern은 별도 함수에서 매칭시킨다.
  매칭된 것은 연결리스트로 준다?
  $> cat < a*
	minishell: ambiguous redirection
	$> cat < ab*
	abab
*/

static int	get_alloc_size(void)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	char			buf[PATH_MAX];
	int				size;

	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
		return (-1);
	file = readdir(dir_ptr);
	size = 0;
	while (file != NULL)
	{
		file = readdir(dir_ptr);
		size++;
	}
	closedir(dir_ptr);
	return (size);
}

static char	**alloc_word_list(void)
{
	int		alloc_size;
	char	**word_list;
	int		idx;

	alloc_size = get_alloc_size() + 1;
	word_list = (char **)malloc(sizeof(char *) * alloc_size);
	if (word_list == NULL)
		return (NULL);
	idx = 0;
	while (idx < alloc_size)
	{
		word_list[idx] = NULL;
		idx++;
	}
	return (word_list);
}

static int	copy_cur_dir_file_list(DIR *dir_ptr, char buf[PATH_MAX], \
									char ***cur_dir_file_list)
{
	struct dirent	*file;
	int				idx;

	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
	{
		free_list(cur_dir_file_list);
		return (-1);
	}
	file = readdir(dir_ptr);
	idx = 0;
	while (file != NULL)
	{
		(*cur_dir_file_list)[idx] = ft_strdup(file->d_name);
		if ((*cur_dir_file_list)[idx] == NULL)
		{
			free_list(cur_dir_file_list);
			return (-1);
		}
		file = readdir(dir_ptr);
		idx++;
	}
	(*cur_dir_file_list)[idx] = NULL;
	return (0);
}

static char	**get_cur_dir_file_list(void)
{
	char			**cur_dir_file_list;
	DIR				*dir_ptr;
	char			buf[PATH_MAX];

	cur_dir_file_list = alloc_word_list();
	if (cur_dir_file_list == NULL)
		return (NULL);
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (NULL);
	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
		return (NULL);
	if (copy_cur_dir_file_list(dir_ptr, buf, &cur_dir_file_list) < 0)
		return (NULL);
	closedir(dir_ptr);
	return (cur_dir_file_list);
}

static int	is_there_any_wildcard(t_list *cur_node)
{
	char	*str;

	if (get_token(cur_node)->types & TOKEN_SQUOTE
		|| get_token(cur_node)->types & TOKEN_DQUOTE)
		return (0);
	str = get_token(cur_node)->data;
	if (ft_strchr(str, '*') < 0)
		return (0);
	return (1);
}

static int	wrapper_free_list(char ***word_list)
{
	free_list(word_list);
	return (-1);
}


static int	get_normal_case_pattern_size(t_list *cur_node)
{
	int		idx;
	int		alloc_size;
	char	prev_char;

	idx = 0;
	alloc_size = 0;
	while ((get_token(cur_node)->data)[idx])
	{
		if ((get_token(cur_node)->data)[idx] != '*')
			alloc_size += 1;
		else
		{
			if (prev_char != '*')
				alloc_size += 1;
		}
		prev_char = (get_token(cur_node)->data)[idx];
		idx++;
	}
	return (alloc_size);
}
/*
	- pattern이 정리되었을 경우의 사이즈를 재서 return해준다.
	e.g) **.** -> *.* size 3
		"***".'***' -> ***.*** size 7
	"", '' 신경써서 처리
*/
static int	get_pattern_alloc_size(t_list *start_node, t_list *end_node)
{
	t_list	*cur_node;
	int		alloc_size;
	int		idx;
	char	prev_char;
	
	if (start_node == NULL || end_node == NULL)
		return (0);
	alloc_size = 0;
	cur_node = start_node;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_SQUOTE
			|| get_token(cur_node)->types & TOKEN_DQUOTE)
			alloc_size += ft_strlen(get_token(cur_node)->data);
		else
			alloc_size += get_normal_case_pattern_size(cur_node);
		if (cur_node == end_node)
			break ;
		cur_node = cur_node->next;
	}
	return (alloc_size);
}

// 마지막 '\0' 넣는것에 대해 제대로 되는지 테스트 필요, 엣지 케이스는 없는가?
void	copy_normal_case_pattern(char *pattern, t_list *cur_node, int alloc_size)
{
	int		idx;
	int 	pattern_idx;
	char	prev_char;

	idx = 0;
	pattern_idx = 0;
	while (idx < alloc_size)
	{
		if ((get_token(cur_node)->data)[idx] != '*')
		{
			pattern[pattern_idx] = '*';
			pattern_idx++;
		}
		else
		{
			if (prev_char != '*')
			{
				pattern[pattern_idx] += (get_token(cur_node)->data)[idx];
				pattern_idx++;
			}
		}
		prev_char = (get_token(cur_node)->data)[idx];
		idx++;
	}
	pattern[pattern_idx] = '\0';
}
/*
	새로운 공간에 organize된것을 담고있다가
	기존 공간에 넘겨줄것인가?(기존공간은 free)
	만일 동일한 경우 낭비가 될수 있다.
	패턴이 일치하는게 없을 경우 기존것을 바꾸는 것은 정의한 동작이 아니므로 문제가 될수 있다.
	organize 하면 안된다.ㄴ
	"", ''분간해야한다.
	**로 여러개가 들어오면 이어붙인다.
*/
static char	*get_organized_pattern(t_list *start_node, t_list *end_node)
{
	t_list	*cur_node;
	char	*pattern;
	int		alloc_size;

	if (start_node == NULL || end_node == NULL)
		return (NULL);
	alloc_size = get_pattern_alloc_size(start_node, end_node) + 1;
	pattern = (char *)malloc(sizeof(char) * alloc_size);
	if (pattern == NULL)
		return (NULL);
	pattern[0] = '\0';
	cur_node = start_node;
	while (cur_node)
	{
		if (get_token(cur_node)->types & TOKEN_SQUOTE
			|| get_token(cur_node)->types & TOKEN_DQUOTE)
			ft_strlcat(pattern, get_token(cur_node)->data, alloc_size);
		else
			copy_normal_case_pattern(pattern, cur_node, alloc_size);
		if (cur_node == end_node)
			break ;
		cur_node = cur_node->next;
	}
	return (pattern);
}

int	add_pattern_list(t_list **pattern_list, char *dir_file_name)
{
	t_list	*cur_node;

	cur_node = *pattern_list;
	while (cur_node)
		cur_node = cur_node->next;
	cur_node = (t_list *)malloc(sizeof(t_list));
	if (pattern_list == NULL)
		return (NULL);
	cur_node->node = (t_token *)malloc(sizeof(t_token));
	if (cur_node->node == NULL)
		return (-1); // free pattern_list, node, data free는 할당의 역순!
	// get_token(pattern_list)->data = (char *)malloc(sizeof(char) * ())
	if (get_token(cur_node)->data == NULL)
		return (-1); // free pattern_list, node, data
}

/*
아래 타입들에 대해서 어떤식으로 패턴 매칭할것인가?
	다음패턴을 확인한다.
	e.g) *l*
		중간에 l이들어가거나, l로 시작하거나 l로 끝날 수 있다.
- *
- .*
- .*.
- *.*.
- *.*.*
- ..으로만 시작하는건 또 다르다.
*/
static int	match_pattern(const char *pattern, const char *dir_file_name)
{
	int	idx;
	int	pattern_idx;

	idx = 0;
	pattern_idx = 0;
	//.
	if (pattern[pattern_idx])
		;
	while (pattern[pattern_idx] && dir_file_name[idx])
	{
		if (pattern[pattern_idx] != '*')
		idx++;
		pattern_idx++;
	}
	return (0);
}
/*
	cur_dir_file_list 문자열들을 돌면서 pattern에 매칭되는것을 찾는다.
	매칭된것은 해당 문자열을 포함하는 list(node멤버변수에 token을 포함함)를 만든다.
	매칭된것을 찾으면 리스트를 만든다.
*/
static t_list	*get_pattern_matched_list(char *pattern, char **cur_dir_file_list)
{
	t_list	*pattern_list;
	int		idx;

	idx = 0;
	pattern_list = NULL;
	while (cur_dir_file_list[idx])
	{
		if (match_pattern(pattern, cur_dir_file_list[idx]))
			add_pattern_list(&pattern_list, cur_dir_file_list[idx]);
		idx++;
	}
	return (pattern_list);
}

/*
	TOKEN_CONCAT이 있을 수 있으므로 "."*"."같이 들어오는 경우 혹은 ls* 같이 1개 노드만 들어오는 경우를 가정

	** 여러개 있는 경우는 skip하고 * 한개로 만든다.
	pattern을 가져와서 cur_dir_file_list에 문자열들을 돌면서 매칭되는것을 찾는다.
	- 매칭되는 것을 찾았다면
		- 해당 문자열을 포함하는 list(node멤버변수에 token을 포함함)를 만든다.
		- 매칭되는 것이 있을때만 만들고 기존 값을 없애고 새로운 노드를 이어붙인다.
	- 매칭되는 것이 없으면 원본을 건들지 않는다.
*/
static int	wildcard_conversion(t_list **start_node, t_list *end_node, \
								char **cur_dir_file_list)
{
	char	*pattern;
	t_list	*matched_list;

	pattern = get_organized_pattern(*start_node, end_node);
	if (pattern == NULL)
		return (-1);
	matched_list = get_pattern_matched_list(pattern, cur_dir_file_list);
	if (matched_list)
		; // match된 list들을 start_node에는 첫번쨰 list 값을 넣어주며 이후 노드들에 이어붙인다.
		// 그리고 기존 start_node 이후부터 end_node까지는 제거한다. matched_list마지막이 end_node->next 노드를 가리켜야한다.
	safe_free(&pattern);
	return (0);
}

static int	do_wildcard(t_list *list, char **cur_dir_file_list)
{
	t_list	*cur_node;
	t_list	*start_node;

	if (list == NULL || cur_dir_file_list == NULL)
		return (0);
	cur_node = list;
	start_node = NULL;
	while (cur_node)
	{
		if (start_node == NULL)
			start_node = cur_node;
		if (is_there_any_wildcard(&cur_node))
		{
			while (cur_node && get_token(cur_node)->types & TOKEN_CONCAT)
				cur_node = cur_node->next;
			if (wildcard_conversion(&start_node, cur_node, \
									cur_dir_file_list) < 0)
				return (-1);
		}
		if (!(get_token(cur_node)->types & TOKEN_CONCAT))
			start_node = NULL;
		cur_node = cur_node->next;
	}
	return (0);
}

/*< a << b >> c >> e << df
	- 어떤 redir type인지 읽어서 처리한다.
	- expansion 처리되었다는 가정하에 실행한다.
	- ex
*/
int	wildcard_for_curdir(t_simple *scmd_list)
{
	char	**cur_dir_file_list;

	if (scmd_list == NULL)
		return (-1);
	cur_dir_file_list = get_cur_dir_file_list();
	if (cur_dir_file_list == NULL)
		return (-1);
	if (do_wildcard(scmd_list->redirs, cur_dir_file_list) < 0)
		return (wrapper_free_list(&cur_dir_file_list));
	if (do_wildcard(scmd_list->args, cur_dir_file_list) < 0)
		return (wrapper_free_list(&cur_dir_file_list));
	free_list(&cur_dir_file_list);
	return (0);
}
