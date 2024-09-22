/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:07:25 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/22 16:27:34 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_processes(t_line *command, \
	t_pipe_info *pipe_info, t_exit_status *exit_code_line)
{
	int	i;

	i = 0;
	while (i < pipe_info->len)
	{
		exit_code_line->exit_code = 0;
		pipe_info->input = 1;
		pipe_info->output = 1;
		handle_fork(command, pipe_info, i, exit_code_line);
		if (g_catch_ctrlc == 1)
		{
			exit_code_line->exit_code = 1;
			break ;
		}
		command = command->next;
		i++;
	}
}

void	handle_fork(t_line *command, t_pipe_info *pipe_info, \
	int i, t_exit_status *exit_code_line)
{
	int	input;
	int	output;

	input = dup(0);
	output = dup(1);
	if (get_fds(command, pipe_info, exit_code_line) != -1)
	{
		pipe_info->pid[i] = fork();
		if (pipe_info->pid[i] < 0)
			exit(1);
		if (pipe_info->pid[i] == 0)
			run_child_process(command, pipe_info, i, exit_code_line);
	}
	else
		exit_code_line->exit_code = 1;
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
}

void	run_child_process(t_line *command, t_pipe_info *pipe_info, \
							int i, t_exit_status *exit_code_line)
{
	char	*exe;

	if (i != 0 && pipe_info->input == 1)
	{
		dup2(pipe_info->pipes[i - 1][0], STDIN_FILENO);
		close(pipe_info->pipes[i - 1][0]);
	}
	if (i != pipe_info->len - 1 && pipe_info->output == 1)
	{
		dup2(pipe_info->pipes[i][1], STDOUT_FILENO);
		close(pipe_info->pipes[i][1]);
	}
	clean_pipes(pipe_info, exit_code_line);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (command->cmd != NULL && !built_in(command, exit_code_line))
	{
		exe = get_copy(ft_strdup(command->cmd), command->arg);
		run_exec(exe, *(command->env), exit_code_line);
	}
	exit(exit_code_line->exit_code);
}

void	control_space(char *command)
{
	unsigned long	i;

	i = 0;
	while (command[i])
	{
		if (command[i] != ' ' && command[i] != '\t' && command[i]
			!= '\n' && command[i] != '\v' && command[i] != '\r' )
			break ;
		else if (i == ft_strlen(command) - 1)
		{
			ft_putendl_fd(": There is no such command", 2);
			exit(127);
		}
		i++;
	}
}
