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
	clean_pipes(command, pipe_info);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (command->cmd != NULL && !built_in(command))
	{
		exe = get_copy(ft_strdup(command->cmd), command->arg);
		run_exec(command, exe, *(command->env));
	}
	exit(command->exit_code_line);
}

int	get_fds(t_line *command, t_pipe_info *pipe_info)
{
	int	fd;
	int	ret;

	ret = 0;
	if (fd_len(&(command->left)) != 0)
	{
		fd = open_lefts(command->left);
		if (fd == -1)
		{
			fd = open("/dev/null", O_RDONLY);
			free(command->env[0][0]);
			command->env[0][0] = ft_strdup("?=1");
			ret = -1;
		}
		dup2(fd, 0);
		pipe_info->input = 0;
	}
	if (ret != -1 && fd_len(&(command->right)) != 0)
	{
		fd = open_rights(command->right);
		if (fd != -1)
		{
			dup2(fd, 1);
			pipe_info->output = 0;
		}
	}
	return (ret);
}

void	create_processes(t_line *command, t_pipe_info *pipe_info)
{
	int	i;
	int	output;
	int	input;

	i = 0;
	while (i < pipe_info->len)
	{
		free(command->env[0][0]);
		command->env[0][0] = ft_strdup("?=0");
		pipe_info->input = 1;
		pipe_info->output = 1;
		input = dup(0);
		output = dup(1);
		if (get_fds(command, pipe_info) != -1)
		{
			pipe_info->pid[i] = fork();
			if (pipe_info->pid[i] < 0)
				exit(1);
			if (pipe_info->pid[i] == 0)
				run_child_process(command, pipe_info, i);
		}
		dup2(input, 0);
		close(input);
		dup2(output, 1);
		close(output);
		if (g_catch_ctrlc == 1)
		{
			free(command->env[0][0]);
			command->env[0][0] = ft_strdup("?=1");
			break;
		}	
		command = command->next;
		i++;
	}
}
