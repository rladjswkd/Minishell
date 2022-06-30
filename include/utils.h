/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 14:45:28 by jim               #+#    #+#             */
/*   Updated: 2022/06/30 17:13:49 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H
# include <stddef.h>
# include <stdbool.h>
# define SHELL_NAME "minishell"

bool	is_whitespace(char const ch);

size_t	ft_strlen(const char *s);

void	ft_putstr_fd(const char *s, int fd);
void	print_newline_fd(int fd);

int		free_list(char ***word_list);
char	**ft_split(char const *s, char c);

char	*ft_strdup(const char *s1);
char	*ft_strndup(const char *s1, int len);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strchr(char *s, int c);

void	error_handler(char *cmd, char *argv, char *msg, char exit_status);
void	print_error(char *shell_name, char *cmd, char *argv, char *msg);
size_t	max_nonnegative(char const *s1, char const *s2);

#endif
