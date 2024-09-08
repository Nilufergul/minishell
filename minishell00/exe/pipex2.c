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
	if (command->cmd != NULL && !built_in(command))
	{
		exe = get_copy(ft_strdup(command->cmd), command->arg);
		run_exec(exe, *(command->env));
	}
	else
		waitpid(pipe_info->pid[i], NULL, 0);
	exit(0);
}

void	get_fds(t_line *command, t_pipe_info *pipe_info)
{
	if (fd_len(&(command->left)) != 0)
	{
		dup2(open_lefts(command->left), 0);
		pipe_info->input = 0;
	}
	if (fd_len(&(command->right)) != 0)
	{
		dup2(open_rights(command->right), 1);
		pipe_info->output = 0;
	}
}

void	create_processes(t_line *command, t_pipe_info *pipe_info)
{
	int	i;
	int	output;
	int	input;

	i = 0;
	while (i < pipe_info->len)
	{
		pipe_info->input = 1;
		pipe_info->output = 1;
		input = dup(0);
		output = dup(1);
		get_fds(command, pipe_info);
		pipe_info->pid[i] = fork();
		if (pipe_info->pid[i] < 0)
			exit(1);
		if (pipe_info->pid[i] == 0)
			run_child_process(command, pipe_info, i);
		dup2(input, 0);
		close(input);
		dup2(output, 1);
		close(output);
		command = command->next;
		i++;
	}
}
