/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/02 11:23:02 by jim               #+#    #+#             */
/*   Updated: 2022/08/13 20:59:59 by jim              ###   ########seoul.kr  */
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
#include "command_compound.h"
#include "command_simple.h"
#include "command.h"
#include "execute.h"
#include "process.h"
#include "exit.h"
#include "ft_error.h"

static void	child_process(t_env_list *env_list, t_fd_info *fd_info, \
							t_pipelist_info *pipelist_info);

static int	parent_process(t_fd_info *fd_info, t_list *start_node, \
							t_list *cur_node);

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

static int	init_pipeline_process(t_list *pipeline_list, \
										t_pipelist_info *pipelist_info, \
										t_process_info **process_info)
{
	t_list	*cur_node;
	int		count;

	count = 0;
	cur_node = pipeline_list;
	while (cur_node)
	{
		cur_node = cur_node->next;
		count++;
	}
	pipelist_info->start_node = pipeline_list;
	pipelist_info->cur_node = pipeline_list;
	(*process_info) = (t_process_info *)malloc(sizeof(t_process_info) \
											* count);
	if ((*process_info) == NULL)
		return (1);
	(*process_info)->process_count = count;
	return (0);
}

static int	pipeline_waitpid_processing(t_process_info *process_info)
{
	int	status;
	int	idx;

	idx = 0;
	while (idx < process_info->process_count)
	{
		waitpid(process_info[idx].pid, &(process_info[idx].status), 0);
		idx++;
	}
	status = handle_status(process_info[idx - 1].status);
	free(process_info);
	return (status);
}

int	pipeline_processing(t_env_list *env_list, t_list *pipeline_list)
{
	t_pipelist_info		pipelist_info;
	t_fd_info			fd_info;
	t_process_info		*process_info;
	int					idx;

	fd_info.spin_flag = 1;
	init_pipeline_process(pipeline_list, &pipelist_info, &process_info);
	idx = 0;
	while (pipelist_info.cur_node)
	{
		if (is_exist_next_pipe(pipelist_info.cur_node))
			if (pipe(fd_info.fd[(fd_info.spin_flag + 1) % 2]) < 0)
				return (1);
		process_info[idx].pid = fork();
		if (process_info[idx].pid < 0)
			return (1);
		else if (process_info[idx].pid == 0)
			child_process(env_list, &fd_info, &pipelist_info);
		parent_process(&fd_info, pipeline_list, pipelist_info.cur_node);
		pipelist_info.cur_node = pipelist_info.cur_node->next;
		switch_flag(&fd_info.spin_flag);
		idx++;
	}
	return (pipeline_waitpid_processing(process_info));
}

static void	child_process(t_env_list *env_list, t_fd_info *fd_info, \
							t_pipelist_info *pipelist_info)
{
	if (is_exist_prev_pipe(pipelist_info->start_node, pipelist_info->cur_node))
		connect_to_prev(fd_info->fd[fd_info->spin_flag % 2]);
	if (is_exist_next_pipe(pipelist_info->cur_node))
		connect_to_next(fd_info->fd[(fd_info->spin_flag + 1) % 2]);
	if (get_command_type(pipelist_info->cur_node) & COMPOUND_PIPELINE
		|| get_command_type(pipelist_info->cur_node) & COMPOUND_SUBSHELL)
		execute_processing(env_list, pipelist_info->cur_node, TRUE);
	else if (get_command_type(pipelist_info->cur_node) & SIMPLE_NORMAL)
		simple_cmd(env_list, \
							get_simple(pipelist_info->cur_node), TRUE);
	else
		print_error(SHELL_NAME, NULL, NULL, "unknown command_type");
}

static int	parent_process(t_fd_info *fd_info, t_list *start_node, \
							t_list *cur_node)
{
	if (is_exist_prev_pipe(start_node, cur_node))
		if (close(fd_info->fd[fd_info->spin_flag % 2][READ_END]) < 0)
			return (-1);
	if (is_exist_next_pipe(cur_node))
		if (close(fd_info->fd[(fd_info->spin_flag + 1) % 2][WRITE_END]) < 0)
			return (-1);
	return (1);
}
