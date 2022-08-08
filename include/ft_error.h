/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:25:01 by jim               #+#    #+#             */
/*   Updated: 2022/08/09 02:20:29 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# define NONVALID "not a valid identifier"
# define ALLOC_FAIL "allocation fail"
# define AMBIGUOUS_REDIRECT "ambiguous redirect"

int		error_handler(char *cmd, char *argv, char *msg, char exit_status);
void	print_error(char *shell_name, char *cmd, char *argv, char *msg);

#endif