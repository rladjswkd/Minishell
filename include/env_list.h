/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 19:36:08 by jim               #+#    #+#             */
/*   Updated: 2022/06/28 21:18:21 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LIST_H
# define ENV_LIST_H
# include <stddef.h>

typedef struct s_env_node
{
	struct s_env_node	*next_node;
	char				*key;
	char				*value;
}				t_env_node;

typedef struct s_env_list
{
	t_env_node	*header_node;
	int			list_length;
}				t_env_list;

t_env_list	*create_env_list(void);
t_env_node	*create_env_node(char *key, char *value);
int			add_back_env_node(t_env_list *env_list, t_env_node *new_node);
int			remove_env_node(t_env_list *env_list, t_env_node *cur_node, \
							char *data);

#endif
