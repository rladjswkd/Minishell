/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 18:22:26 by jim               #+#    #+#             */
/*   Updated: 2022/06/26 19:32:04 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

/*
	- envp등의 값을 초기화하는 함수
	- 전역변수를 쓸지
	- 어떻게 구성할지에 따라 달라진다.
	- 환경변수 등 초기에 세팅이 필요한 값들을 가지고 있는 구조체에 대한 논의 필요
	- 함수별로 어떻게 가지고 다닐 것인가?
	- 전역변수를 쓰지 않는다고해도 계속 가지고 다니면 전역변수와의 차이점은 무엇인가?
	- 전역변수를 씀으로써 생길수 있는 문제와 어디서는 가지고 다니는 변수를 씀으로써
	  발생할 수 있는 문제의 차이점은 무엇인가?
	- 결과를 자료구조에 담아야한다.
*/

#include "linked_list.h"

typedef struct s_env
{
	linked_list	*key_list;
	linked_list	*value_list;
}				t_env;

/*
	linked로 하면 몇개가 들어올지 신경안써도 되지만
	찾을때 key, value list를 똑같은 횟수만큼 이동해줘야한다.
	그 부분에서 둘다 이동해야하므로 지장이 있을수 있다.
	우선은 linked를 활용해본다.
	불편하면 array list로 변경가능.
*/

int	init(char **envp)
{
	t_env	env;
	size_t	idx;

	// error handling 필요
	key_list = create_linked_list();
	if (env->key_list == NULL)
		return (-1);
	value_list = create_linked_list();
	if (env->value_list == NULL)
		return (-1);
	idx = 0;
	while (envp[idx])
	{
		create_linked_node()
		idx++;
	}
	ft_strnstr();

}
