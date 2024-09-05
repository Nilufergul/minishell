
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

void	run_child_process(t_line *command, t_pipe_info *pipe_info, int i)
{
	if (i != 0)
	{
		dup2(pipe_info->pipes[i - 1][0], STDIN_FILENO);
		close(pipe_info->pipes[i - 1][0]);
	}
	if (i != pipe_info->len - 1)
	{
		dup2(pipe_info->pipes[i][1], STDOUT_FILENO);
		close(pipe_info->pipes[i][1]);
	}
	close_all_pipes(pipe_info->pipes, pipe_info->len - 1);
	run_command_run(command);
	exit(0);
}

void	create_processes(t_line *command, t_pipe_info *pipe_info)
{
	int	i;

	i = 0;
	while (i < pipe_info->len)
	{
		pipe_info->pid[i] = fork();
		if (pipe_info->pid[i] < 0)
			exit(1);
		if (pipe_info->pid[i] == 0)
			run_child_process(command, pipe_info, i);
		command = command->next;
		i++;
	}
}

void	clean_pipes(t_pipe_info *pipe_info)
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
		waitpid(pipe_info->pid[i], NULL, 0);
		i++;
	}
}
