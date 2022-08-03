/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 12:25:48 by jim               #+#    #+#             */
/*   Updated: 2022/08/04 00:07:28 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <dirent.h>
#include "linked_list.h"
#include "lexer.h"
#include "utils.h"


/*
  매칭되는 것이 없다면 literal로 취급
  *만 들어오는 경우 현재 디렉토리에 있는 file or directory들을 넘겨준다.
  .*이 있는 경우에만 .을 가져온다
  *.* (총  2자 이상이야어햔다.   .으로 시작하는 것은 포함되지 않으며, .으로 끊나는건 가능하다.)
  pattern은 별도 함수에서 매칭시킨다.
  매칭된 것은 연결리스트로 준다?
  $> cat < a*
	minishell: ambiguous redirection
	$> cat < ab*
	abab
*/
static int	do_wildcard(t_list *list)
{
	DIR				*dir_ptr;
	struct dirent	*file;
	char			buf[PATH_MAX];
	
	if (list == NULL)
		return (0);
	if (getcwd(buf, sizeof(buf)) == NULL)
		return (1);
	dir_ptr = opendir(buf);
	if (dir_ptr == NULL)
		return (-1);
	file = readdir(dir_ptr);
	while (file != NULL)
	{
		file->d_name;
		file = readdir(dir_ptr);
	}
	closedir(dir_ptr);
	return (0);
}

/*< a << b >> c >> e << df
	- 어떤 redir type인지 읽어서 처리한다.
	- expansion 처리되었다는 가정하에 실행한다.
	- ex
*/
int	wildcard_for_curdir(t_simple *scmd_list)
{
	if (scmd_list == NULL)
		return (-1);
	if (do_wildcard(scmd_list->redirs) < 0)
		return (-1);
	if (do_wildcard(scmd_list->args) < 0)
		return (-1);
	return (0);
}
