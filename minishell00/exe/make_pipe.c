#include "../minishell.h"
void	free_pipe_things(t_pipe_info *pipe_info)
{
	clean_pipes(pipe_info);
	free(pipe_info->pid);
	free_all_pipes(pipe_info->pipes, pipe_info->len - 1);
	free(pipe_info->pipes);
	free(pipe_info);
}

char	**copy_env(char **env)
{
	int		rows;
	char	**new;

	rows = 0;
	while (env[rows])
		rows++;
	new = (char **)malloc((rows + 1) * sizeof(char *));
	if (new == NULL)
		exit(1);
	new[rows] = NULL;
	rows--;
	while (rows >= 0)
	{
		new[rows] = ft_strdup(env[rows]);
		if (new[rows] == NULL)
			exit(1);
		rows--;
	}
	return (new);
}

void	make_pipe(t_line *command)
{
	t_pipe_info	*pipe_info;

	if (struct_len(command) == 1 && !run_command_run(command))
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
	free_pipe_things(pipe_info);
}
