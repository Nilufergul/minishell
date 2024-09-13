
#include "../minishell.h"

void	free_pipe_things(t_line *command, t_pipe_info *pipe_info)
{
	clean_pipes(command, pipe_info);
	free(pipe_info->pid);
	free_all_pipes(pipe_info->pipes, pipe_info->len - 1);
	free(pipe_info->pipes);
	free(pipe_info);
}

void	make_pipe(t_line *command)
{
	t_pipe_info	*pipe_info;

	if(command->cmd == NULL)
	{}
	else if ((command->cmd[0] == 0) || (struct_len(command) == 1 && built_in2(command)))
		return ;
	pipe_info = malloc(sizeof(t_pipe_info));
	if (pipe_info == NULL)
		exit(1);
	pipe_info->len = struct_len(command);
	pipe_info->pid = malloc(sizeof(pid_t) * pipe_info->len);
	if (pipe_info->pid == NULL)
		exit(1);
	pipe_info->pipes = fill_pipes(pipe_info->len);
	create_processes(command, pipe_info);
	free_pipe_things(command, pipe_info);

}

int	built_in2(t_line *command)
{
	if (ft_strcmp(command->cmd, "cd") == 0)
		command->exit_code_line = ft_cd(command);
	else if (ft_strcmp(command->cmd, "export") == 0)
		command->exit_code_line = ft_export(command);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		ft_unset(command);
	else if (ft_strcmp(command->cmd, "env") == 0)
		command->exit_code_line = ft_environment(*(command->env));
	else if (ft_strcmp(command->cmd, "exit") == 0)
		ft_exit(command);
	else
		return (0);
	return (1);
}

void	clean_pipes(t_line *command, t_pipe_info *pipe_info)
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
		waitpid(pipe_info->pid[i], &command->exit_code_line, 0);
		if (ft_strcmp(command->env[0][0], "?=0") == 0)
		{
			command->exit_code_line = w_exit_status(command->exit_code_line);
			free(command->env[0][0]);
			command->env[0][0] = ft_strjoin(ft_strdup("?="), ft_strdup(ft_itoa(command->exit_code_line)));
		}
		i++;
	}
}
