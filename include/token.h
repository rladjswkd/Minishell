/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:45 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:47 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H
# include "structure_token.h"
# include "structure_linked_list.h"
# include "type_token.h"
# include "construct.h"

t_token	*get_token(t_list *token_list);
int		get_token_type(t_list *token_list);
int		create_token(t_list **token_list, char *str, int len, int types);
#endif
