/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:06:59 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 16:35:05 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_pipe_things(t_pipe_info *pipe_info, t_exit_status *exit_code_line)
{
	clean_pipes(pipe_info, exit_code_line);
	free(pipe_info->pid);
	free_all_pipes(pipe_info->pipes, pipe_info->len - 1);
	free(pipe_info->pipes);
	free(pipe_info);
}

void	make_pipe(t_line *command, t_exit_status *exit_code_line)
{
	t_pipe_info	*pipe_info;

	if (command->cmd != NULL && ((struct_len(command) == 1 \
			&& built_in2(command, exit_code_line))))
		return ;
	pipe_info = malloc(sizeof(t_pipe_info));
	if (pipe_info == NULL)
		exit(1);
	pipe_info->len = struct_len(command);
	pipe_info->pid = malloc(sizeof(pid_t) * pipe_info->len);
	if (pipe_info->pid == NULL)
		exit(1);
	pipe_info->pipes = fill_pipes(pipe_info->len);
	create_processes(command, pipe_info, exit_code_line);
	free_pipe_things(pipe_info, exit_code_line);
}

int	built_in2(t_line *command, t_exit_status *exit_code_line)
{
	if (ft_strcmp(command->cmd, "cd") == 0)
		exit_code_line->exit_code = ft_cd(command);
	else if (ft_strcmp(command->cmd, "export") == 0)
		exit_code_line->exit_code = ft_export(command);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		ft_unset(command);
	else if (ft_strcmp(command->cmd, "env") == 0)
		exit_code_line->exit_code = ft_environment(*(command->env));
	else if (ft_strcmp(command->cmd, "exit") == 0)
		ft_exit(command, exit_code_line);
	else
		return (0);
	return (1);
}

void	clean_pipes(t_pipe_info *pipe_info, t_exit_status *exit_code_line)
{
	int	i;

	i = 0;
	while (i < pipe_info->len - 1)
	{
		close(pipe_info->pipes[i][0]);
		close(pipe_info->pipes[i][1]);
		i++;
	}
	i = 0;
	while (i < pipe_info->len)
	{
		waitpid(pipe_info->pid[i], &(exit_code_line->exit_code), 0);
		if (i == pipe_info->len - 1 && WIFEXITED(exit_code_line->exit_code))
			exit_code_line->exit_code /= 256;
		i++;
	}
}

void	procedure3(t_line *command, t_split *split, t_exit_status *exit_t)
{
	make_pipe(command, exit_t);
	free_the_split(split);
	free_command(command);
}
