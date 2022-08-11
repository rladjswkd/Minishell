/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 13:44:26 by jim               #+#    #+#             */
/*   Updated: 2022/08/11 11:26:29 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "destruct_wrapper.h"
#include "env_list.h"
#include "lexer.h"
#include "exit.h"
#include "utils.h"
#include "expansion.h"

/*
	variable naming 조건에 맞춘다면
	variable시작인지도 확인해야겠지만
	$ 에서 없는 환경변수라면
*/
int	check_dollar_flag(int flag, t_sub_str_info sub_str_info)
{
	char	ch;
	int		len;

	ch = (sub_str_info.as_is_str)[sub_str_info.idx];
	len = sub_str_info.len;
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

static char	*convesion_using_env(t_env_list *env_list, const char *str)
{
	t_env_node	*env_node;

	env_node = env_list->header_node;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, str, \
						max_nonnegative(env_node->key, str)) == 0)
		{
			if (env_node->value == NULL)
				return (ft_strdup(""));
			return (ft_strdup(env_node->value));
		}
		env_node = env_node->next_node;
	}
	return (ft_strdup(""));
}

static int	conversion(t_env_list *env_list, t_token *token)
{
	const char	*as_is_str;
	char		*to_be_str;

	as_is_str = (const char *)token->data;
	if (as_is_str[1] == '\0')
		to_be_str = ft_strdup("$");
	else if (as_is_str[1] == '?')
		to_be_str = ft_itoa(*get_exit_status());
	else
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
	if (expansion_str_split(token, &tmp_expansion_list) < 0)
		return (-1);
	cur_node = tmp_expansion_list.next;
	while (cur_node)
	{
		if (get_token(cur_node)->types == VARIABLE)
		{
			if (conversion(env_list, get_token(cur_node)) < 0)
				return (wrapper_free_token_list(&tmp_expansion_list, -1));
		}
		cur_node = cur_node->next;
	}
	safe_free(&(token->data));
	if (concat_tmp_expansion_list(token, &tmp_expansion_list) < 0)
		return (wrapper_free_token_list(&tmp_expansion_list, -1));
	return (0);
}
