/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure_token.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gyepark <gyepark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 12:53:42 by gyepark           #+#    #+#             */
/*   Updated: 2022/08/10 12:53:43 by gyepark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_TOKEN_H
# define STRUCTURE_TOKEN_H

typedef struct s_token
{
	int		types;
	char	*data;
	int		heredoc_fd;
}	t_token;
#endif
