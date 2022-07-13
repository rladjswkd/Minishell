/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/07/13 16:00:12 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum e_pipe
{
	READ_END,
	WRITE_END,
}			t_pipe;

typedef int t_fd;

typedef struct s_pipe_info
{
	t_fd	in;
	t_fd	out;
}				t_pipe_info;

typedef enum e_bool
{
	FALSE,
	TRUE,
}			t_bool;

typedef enum e_sys_return
{
	SUCCESS,
	ERROR,
}			t_sys_return;
/*
	- 파이프를 열고 이전 명령어 블록에서 다음 명령어 블록으로 이어준다.
	- 즉, 첫번째 자식의 STDOUT을 pipe[WRITE_END]에 저장한다.
		두번쨰 자식의 STDINd을 pipe[READ_END]에 저장한다.
*/