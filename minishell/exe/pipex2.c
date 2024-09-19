/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:17:05 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:17:07 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_all_pipes(int **pipes, int len)
{
	if (len <= 0)
		return ;
	close(pipes[len - 1][0]);
	close(pipes[len - 1][1]);
	if (len > 1)
		close_all_pipes(pipes, len - 1);
}

void	free_all_pipes(int **pipes, int len)
{
	if (len <= 0)
		return ;
	free(pipes[len - 1]);
	if (len > 1)
		free_all_pipes(pipes, len - 1);
}

int	handle_right_fd(t_line *command, \
	t_pipe_info *pipe_info, t_exit_status *exit)
{
	int	fd;

	fd = open_rights(command->right);
	if (fd != -1)
	{
		dup2(fd, 1);
		pipe_info->output = 0;
		return (0);
	}
	exit->exit_code = 1;
	return (-1);
}

int	handle_left_fd(t_line *command, t_pipe_info *pipe_info, t_exit_status *exit)
{
	int	fd;
	int	ret;

	fd = open_lefts(command->left);
	ret = 0;
	if (fd == -1)
	{
		exit->exit_code = 1;
		fd = open("/dev/null", O_RDONLY);
		ret = -1;
	}
	dup2(fd, 0);
	pipe_info->input = 0;
	return (ret);
}

int	get_fds(t_line *command, t_pipe_info *pipe_info, t_exit_status *exit)
{
	int	ret;

	ret = 0;
	if (fd_len(&(command->left)) != 0)
		ret = handle_left_fd(command, pipe_info, exit);
	if (ret != -1 && fd_len(&(command->right)) != 0)
		ret = handle_right_fd(command, pipe_info, exit);
	return (ret);
}
