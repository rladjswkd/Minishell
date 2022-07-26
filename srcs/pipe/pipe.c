/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/07/26 18:45:50 by jim              ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "pipe.h"
#include "utils.h"
#include "env_list.h"
#include "linked_list.h"
#include "lexer.h"
#include "execute.h"
#include "process.h"
#include "ft_error.h"

static int	child_process(t_env_list *env_list, t_fd_info *fd_info, \
							t_pipelist_info *pipelist_info, t_list *heredoc_list);

// parameter수정필요
static int	parent_process(t_fd_info *fd_info, t_process_info *process_info, \
						t_list *start_node, t_list *cur_node);
// t_pipe_info;
// cat a > b > c
/*
	echo a > output > b > c > d < e | cat |
	stdout
	- test할 사항
	- pipe 1개, 2개, n개 일때의 fd 전달
	- redirec 있을때 케이스
*/


/*
	- make multipipe
	- 다음에 파이프가 있는지 확인하고서 있으면 연결한다.
	- fork와 파이프 연결은 개별로 바꾼다.
	- 현재 위치(명령어 블록)기준으로 이전에 파이프가 있었는지, 다음에 파이프가 있는지를 확인하여
	이전에 파이프가 있었다면
	dup2(fd[READ_END], STDIN)으로 변경한다.
	이후에 파이프가 있다면
	dup2(fd[WRITE_END], STDOUT)으로 변경한다.
	connect_to_prev
	connect_to_next
	이후에 파이프 기호가 있다면
	pipe()선언한다.
	fork()를 뜬다.
*/


/*
	- exit status
	- pipe가 있는 동안 계속 파이프 만들고 프로세스 생성한다.
		딘, 마지막 직전까지만 파이프는 만든다.
		마지막 scmd에 대해서는 fork()뜬다.
	- pipe에 대한 fd는 해당 명령어 블럭에 담아두어야한다.
		- fd를 안담아도 된다. 단 close를 위해 기억은 해야한다.
	- 과정은 어떻게 되는가?
		- 값이 들어온다.
		- 다음 것이 있으면 pipe()를 만든다.
		- 2n + 1, 2n번째 자식 프로세스 조건에 맞게 실행한다.(n은 0부터 시작)
			- 시작 프로세스면 다음 프로세스로 pipe연결을 한다.
			- 중간에 있는 것들이면 이전, 이후로 pipe연결을 한다.
			- 다음 파이프가 있다면
				자식에서 dup2 이후에 이미 사용한 fd[WRITE_END]를 close한다.
			- 이전 파이프가 있다면
				자식에서 dup2 이후 fd[READ_END]를 close한다.
		- 
*/
static void	switch_flag(int *flag)
{
	if (*flag)
		*flag = 0;
	else
		*flag = 1;
}

int		pipeline_processing(t_env_list *env_list, t_list *pipeline_list, t_list *heredoc_list)
{
	t_pipelist_info		pipelist_info;
	t_fd_info			fd_info;
	t_process_info		process_info;

	fd_info.spin_flag = 1;
	pipelist_info.start_node = pipeline_list;
	pipelist_info.cur_node = pipeline_list;
	while (pipelist_info.cur_node)
	{
		if (is_exist_next_pipe(pipelist_info.cur_node ))
		{
			if (pipe(fd_info.fd[(fd_info.spin_flag + 1) % 2]) < 0)
				return (1);
		}
		process_info.pid = fork();
		if (process_info.pid < 0)
			return (-1);
		else if (process_info.pid == 0)
			return (child_process(env_list, &fd_info, &pipelist_info, heredoc_list));
		else
			parent_process(&fd_info, &process_info, pipeline_list, pipelist_info.cur_node);
		switch_flag(&fd_info.spin_flag);
		pipelist_info.cur_node = pipelist_info.cur_node->next;
	}
	return (0);
}


/*
	builtin check
	env_list를 singleton으로?
	- preperation
	- redir처리
	- builtin()
	- extern_cmd()
	- exit status
*/
/*
	- pipe 연결
	- command type확인
		- compound
			- pipeline
			- subshell
		- simple
			- simple_cmd를 호출한다.
	- exit_status
*/
static int	child_process(t_env_list *env_list, t_fd_info *fd_info, \
							t_pipelist_info *pipelist_info, \
							t_list *heredoc_list)
{
	t_list	*compound_list;
	int		status;

	compound_list = get_compound(pipelist_info->cur_node)->list;
	if (is_exist_prev_pipe(pipelist_info->start_node, pipelist_info->cur_node))
		connect_to_prev(fd_info->fd[fd_info->spin_flag % 2]);
	if (is_exist_next_pipe(pipelist_info->cur_node))
		connect_to_next(fd_info->fd[(fd_info->spin_flag + 1) % 2]);
	if (get_command_type(pipelist_info->cur_node) & COMPOUND_PIPELINE 
		|| get_command_type(pipelist_info->cur_node) & COMPOUND_SUBSHELL)
	{
		status = execute_processing(env_list , pipelist_info->cur_node, \
									heredoc_list,TRUE);
		exit((char)status);
	}
	else if (get_command_type(pipelist_info->cur_node) & SIMPLE_NORMAL)
		status = simple_cmd(env_list, pipelist_info->cur_node, heredoc_list, TRUE);
	else
	{
		status = 2;
		print_error(SHELL_NAME, NULL, NULL, "unknown command_type");// error
	}
	return (status);
}

/*
	현재가 오른쪽으로 연결하는지 왼쪽으로 연결하는지에 따라서 달라진다.
	닫아야할 fd가 달라진다.
	어떻게 구분해서 넘겨줄것인가
	조건문을 덕지덕지 나눠서 넣지 않고 할수 있는 방법은 무엇인가?
	왼쪽에 파이프가 있었다면 
	close(fd[WRITE_END]);
	parent process가 child보다 늦게 실행되는가?
*/
//int fd[2][2], int spin_flag
static int	parent_process(t_fd_info *fd_info, t_process_info *process_info, \
						t_list *start_node, t_list *cur_node)
{
	if (is_exist_prev_pipe(start_node, cur_node))
		if (close(fd_info->fd[fd_info->spin_flag % 2][READ_END]) < 0)
			return (-1);
	if (is_exist_next_pipe(cur_node))
		if (close(fd_info->fd[(fd_info->spin_flag + 1) % 2][WRITE_END]) < 0)
			return (-1);
	waitpid(process_info->pid, &(process_info->status), 0);
	return (1);
}
