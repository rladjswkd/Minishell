/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:44:26 by jim               #+#    #+#             */
/*   Updated: 2022/07/31 19:14:21 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "linked_list.h"
#include "env_list.h"
#include "lexer.h"
#include "exit.h"
#include "utils.h"
#include "expansion.h"
/*
	variable의 마지막 위치를 반환한다.
*/

static void	change_dollar_expansion_flag(int *dollar_expansion_flag)
{
	if (*dollar_expansion_flag == NORMAL)
		*dollar_expansion_flag = VARIABLE;
	else
		*dollar_expansion_flag = NORMAL;
}

/*
	variable naming 조건에 맞춘다면
	variable시작인지도 확인해야겠지만
	$ 에서 없는 환경변수라면
*/
static int	check_dollar_expansion_flag(int flag, char ch, int len)
{
	if (flag == NORMAL)
	{
		if (ch == '$')
			return (CHANGED);
	}
	else if (flag == VARIABLE)
	{
		if (len == 0 && ch == '$')
			return (NOT_CHANGED);
		else if (len == 1)
		{
			if (check_start_of_variable(ch) == 0)
				return (CHANGED);
		}
		else if (check_mid_of_variable(ch) == 0)
			return (CHANGED);
	}
	return (NOT_CHANGED);
}
/*
	- only do double qoute
	cur_node가 가리키는 곳의 변수값을 바꿔야한다.
	pointer에 따른 차이 재확인 필요
	호출한 함수에서 동적할당하는 경우 
	호출된 함수에서는 로컬이라서 동적할당한게 로컬로 처리될 수 있는가?
	즉 가리키는 포인터가 로컬 variable인가?

	jake@DESKTOP-39VE82R:/mnt/d/42/Minishell$ echo $test 34 454
	34 454
	jake@DESKTOP-39VE82R:/mnt/d/42/Minishell$ echo "$test 34 454"
	34 454
	변환할때 없다면 해당 노드자체를 없앤다.
	변환된 문자열할당할때 일관성을 위해 malloc은 동일하게 하는가?

	- " $ $  $ $ $" 처럼 $기호로 된게 많다면 어떻게 할것인가?
	 그떄마다 realloc할것인가?
	- linked list가 나을것인가?
	 대신 $, $사이에 있는 문자열도 linked list로 만들어야한다.
	 모든 문자열이 변환되면
	 각 해당 노드들에 담긴 문자열의 길이를 세서 
	 해당 길이만큼 문자열 할당한 뒤 노드 하나씩 이어붙여 준다. 
	 이어붙여진 문자열을 담은 노드는 삭제한다.
	 (이 노드는 "$ $ $ $ $"을 $를 포함하거나 하지 않은 것들로 이루어진 node이다.)
	 e.g) "42 $test %% $abc $?" -> "42 ", $test, " %% ", $abc, " ", $?
	  		echo 1$ab\34$ab_42%42
				 1, $ab, \34, $ab_42, %42
*/

static void	reset_expansion_str_split_var(t_list *cur_node, \
									int *dollar_expansion_flag, \
									t_sub_str_info	*sub_str_info, \
									int idx, const char *as_is_str)
{
	get_token(cur_node)->types = *dollar_expansion_flag;
	if (as_is_str[idx] == '$' && dollar_expansion_flag == VARIABLE)
		;
	else
		change_dollar_expansion_flag(dollar_expansion_flag);
	sub_str_info->start_idx = (size_t)idx; // 제대로 될것인가?
	sub_str_info->len = 0;
}

/*
as_is_str
sub_str_info->start_of_word = as_is_str; 제대로 되는지 확ㅇ니
*/
static void	init_expansion_str_split_var(const char *as_is_str, int *idx, \
								t_sub_str_info *sub_str_info, \
								int *dollar_expansion_flag)
{
	*dollar_expansion_flag = NORMAL;
	if (as_is_str[0] == '$')
		*dollar_expansion_flag = VARIABLE;
	*idx = 0;
	sub_str_info->len = 0;
	sub_str_info->start_idx = 0;
}

/*
static int	alloc_node(t_list *tmp_expansion_list, t_sub_str_info sub_str_info, \
						char *as_is_str, int dollar_expansion_flag)
{
	if (dollar_expansion_flag == VARIABLE
		&& as_is_str[idx] == '?')
	{
		sub_str_info.len++;
		idx++;
	}
	tmp_expansion_list->next = (t_list *)malloc(sizeof(t_token));
	if (tmp_expansion_list->next == NULL)
		return (-1); // free tmp_expansion_list
	get_token(tmp_expansion_list->next)->data = \
	ft_substr(as_is_str, sub_str_info.start_idx, sub_str_info.len);
	if (get_token(tmp_expansion_list->next)->data == NULL)
		return (-1); // free tmp_expansion_list, also data.
	reset_expansion_str_split_var(tmp_expansion_list, \
							&dollar_expansion_flag, \
							&sub_str_info, idx);
	tmp_expansion_list = tmp_expansion_list->next;
}
*/

// expansion_str_split
int	expansion_str_split(t_token *token, t_list *tmp_expansion_list)
{
	const char		*as_is_str;
	int				idx;
	t_sub_str_info	sub_str_info;
	t_list			*cur_node;
	int				dollar_expansion_flag;

	cur_node = tmp_expansion_list;
	as_is_str = (const char	*)token->data;
	init_expansion_str_split_var(as_is_str, &idx, &sub_str_info, &dollar_expansion_flag);
	while (as_is_str[idx])
	{
		// alloc_node(tmp_expansion_list, )// 지역변수로 처리될것인가?
		// 현재문자 이전까지만 할당되어야한다. 정상적으로 될것인가?
		if (check_dollar_expansion_flag(dollar_expansion_flag, as_is_str[idx], \
										sub_str_info.len))
		{
			if (dollar_expansion_flag == VARIABLE
				&& as_is_str[idx] == '?')
			{
				sub_str_info.len++;
				idx++;
			}
			cur_node->next = (t_list *)malloc(sizeof(t_token));
			if (cur_node->next == NULL)
				return (-1); // free tmp_expansion_list
			get_token(cur_node->next)->data = \
			ft_substr(as_is_str, sub_str_info.start_idx, sub_str_info.len);
			if (get_token(cur_node->next)->data == NULL)
				return (-1); // free tmp_expansion_list, also data.
			reset_expansion_str_split_var(cur_node->next, \
									&dollar_expansion_flag, \
									&sub_str_info, idx, as_is_str);
			cur_node = cur_node->next;
			cur_node->next = NULL;
		}
		sub_str_info.len++;
		idx++;
	}
	cur_node->next = (t_list *)malloc(sizeof(t_token));
	if (cur_node->next == NULL)
		return (-1); // free tmp_expansion_list
	get_token(cur_node->next)->data = \
	ft_substr(as_is_str, sub_str_info.start_idx, sub_str_info.len);
	if (get_token(cur_node->next)->data == NULL)
		return (-1); // free tmp_expansion_list, also data.
	return (0);
}

/*
	- find key
	
*/
static char	*convesion_using_env(t_env_list *env_list, char *str)
{ 
	t_env_node	*env_node;

	env_node = env_list->header_node;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, str, \
						max_nonnegative(env_node->key, str)) == 0)
			return (ft_strdup(env_node->value));
		env_node = env_node->next_node;
	}
	return (ft_strdup(""));
}

static int	get_alloc_size(t_list *tmp_expansion_list)
{
	t_list	*cur_node;
	int		alloc_size;

	cur_node = tmp_expansion_list;
	alloc_size = 0;
	while (cur_node)
	{
		alloc_size += ft_strlen(get_token(cur_node)->data);
		cur_node = cur_node->next;
	}
	return (alloc_size);
}

static void	concat_list_data(t_list *list, char *dst, \
							int dstsize)
{
	t_list	*cur_node;

	cur_node = list;
	while (cur_node)
	{
		ft_strlcat(dst, get_token(cur_node)->data, dstsize);
		dstsize -= ft_strlen(get_token(cur_node)->data);
		cur_node = cur_node->next;
	}
}

// tmp_expansion_list 각 token data에 있는 문자열을 세서 ft_strcat으로 이어붙인다.
static int	concat_tmp_expansion_list(t_token *token, \
										t_list *tmp_expansion_list)
{
	int		alloc_size;

	alloc_size = get_alloc_size(tmp_expansion_list->next) + 1;
	token->data = (char *)malloc(sizeof(char) * alloc_size);
	if (token->data == NULL)
	{
		// free tmp_expansion_list, tmp_expansion_list data 
		// 호출한 함수에서 잘 지워지는지도 확인해야한다.
		return (-1);
	}
	concat_list_data(tmp_expansion_list->next, token->data, alloc_size);
	return (0);
}

// token->data 시작이 $부터인지 재검증 필요
static int  conversion(t_env_list *env_list, t_token *token)
{
	char	*as_is_str;
	char	*to_be_str;

	as_is_str = token->data;
	if (as_is_str[1] == '?')
		to_be_str = ft_itoa(*get_exit_status());
	else // env list에 있는것을 이용해서 변환한다.
		to_be_str = convesion_using_env(env_list, &(as_is_str[1]));
	if (to_be_str == NULL)
		return (-1);
	free(token->data);
	token->data = to_be_str;
	return (0);
}

/*
	- 문자열을 node로 만든다. $로 이루어져있거나 그렇지 않은 것으로 나뉘어있다.
		-  $로 이루어진것은 변환한다.
	- 변환이후에는 해당 node들에 담긴 문자열 길이를 잰다.
	- 모든 길이를 합해서 문자열로 동적할당한다.
	- 문자열에 모든 노드를 시작노드부터 끝까지 이어붙인다.
	- 다 이어붙인 뒤 해당 변수가 선언한 함수에서 tmp_expasion_list를 동적할당된 data및 node를 제거한다.
		
	// ? 혹은 env에 없다면 공백으로 변환된다.없으며 해당 data가 있는 node도 날려야한다.
	- dollar sign이 있는 것과 아닌 것으로 나눈다.
		- 만약 dollar sign이 없다면?
		- 아무것나누지 않는다?
			- 그럴려면 있는지 없는지 확인하는 과정이 들어간다.
				- 확인과정을 넣는게 나을 것인가 아니면 확인 과정 없이 우선 $가 있는것과 아닌것으로 나누는 것이 나을 것인가?
				- 확인과정이 없다면 $가 없는 문자열만을 가진 node 1개가 나올 것이다. 우선 그 생각이 맞을 것인가?
					- 1개가 나온다면 해당 node를 할당하고, 변환하며(변환되지 않겠지만)
						이후에 다시 통합할것이다.
					- $가 있는지(변환과정을 거치게될지) 처음에 순환을 통해서 파악하는게 더 효율적이라 생각든다.
						- 1개 노드에 담긴 문자열의 길이가 평균, 중위적으로 그렇게 길지 않을것이라 판단
						- 최악의 경우, 평균의 경우를 생각했을때에 일단 나누고서 할당하는 것보다 효율적일것 같다.
						- 그렇다면 $가 있는지 확인하는 과정을 거친 뒤에
							- $가 있다면 해당 노드의 문자열을 $가 있는 것과 없는 노드로 나누고 
							   그 이후에 변환한다.
						- $가 아예 없다면 변환 과정도 당연히 거치지 않으며 통합과정 역시 없다.
						   이미 그 자체로 완전하므로.
*/
int	dollar_sign_conversion(t_env_list *env_list, t_token *token)
{
	t_list	tmp_expansion_list;
	t_list	*cur_node;	

	tmp_expansion_list.next = NULL;
	if (env_list == NULL || token == NULL)
		return (-1);
	// expansion_str_split
	if (expansion_str_split(token, &tmp_expansion_list) < 0)
		return (-1);
	cur_node = tmp_expansion_list.next;
	while (cur_node)
	{
		if (get_token(cur_node)->types == VARIABLE)
		{
			if (conversion(env_list, get_token(cur_node)) < 0)
			{
				// free tmp_expansion_list, tmp_expansion_list data
				return (-1);
			}
		}
		cur_node = cur_node->next;
	}
	safe_free(&(token->data));
	// tmp_expansion_list 각 token data에 있는 문자열을 세서 ft_strcat으로 이어붙인다.
	if (concat_tmp_expansion_list(token, &tmp_expansion_list) < 0)
		return (-1);
	// free tmp_expansion_list, tmp_expansion_list data
	return (0);
}
