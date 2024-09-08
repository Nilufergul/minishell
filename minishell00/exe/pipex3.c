
#include "../minishell.h"

int	open_rights(t_fd *head)
{
	int	fd;
	int	last_fd;

	last_fd = -1;
	while (head != NULL)
	{
		if (head->type == GREAT)
		{
			unlink(head->name);
			fd = open(head->name, O_CREAT | O_RDWR, 0777);
		}
		else if (head->type == GREATER)
			fd = open(head->name, O_WRONLY | O_APPEND | O_CREAT, 0644);
		else
			fd = open(head->name, O_RDWR, 0777);
		if (fd == -1)
			return (-1);
		if (last_fd != -1)
			close(last_fd);
		last_fd = fd;
		head = head->next;
	}
	return (last_fd);
}

int	open_lefts(t_fd *head)
{
	int		fd;
	int		last_fd;
	char	*error;

	error = NULL;
	while (head != NULL)
	{
		if (head->type == LESS)
		{
			fd = open(head->name, O_RDONLY, 0777);
			if (fd == -1 && !error)
				error = head->name;
		}
		else if (head ->type == HEREDOC)
			fd = heredoc(head->name);
		close(last_fd);
		last_fd = fd;
		head = head->next;
	}
	if (error)
	{
		printf("%s: There is no such file!\n", error);
		exit(EXIT_FAILURE);
	}
	return (last_fd);
}

int	built_in(t_line *command)
{
	if (ft_strcmp(command->cmd, "echo") == 0)
		echo_main(merge_echo(command->arg));
	else if (ft_strcmp(command->cmd, "pwd") == 0)
		pwd();
	else if (ft_strcmp(command->cmd, "cd") == 0)
		ft_cd(command,command->arg[0]);
	else if (ft_strcmp(command->cmd, "export") == 0)
		ft_export(command);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		ft_unset(command);
	else if (ft_strcmp(command->cmd, "env") == 0)
		ft_environment(*(command->env));
	else if (ft_strcmp(command->cmd, "exit") == 0)
		ft_exit(command->arg);
	else
		return (0);
	return (1);
}

int	run_command_run(t_line *command)
{
	char	*exe;

	if (command->cmd != NULL && !built_in(command))
	{
		exe = get_copy(ft_strdup(command->cmd), command->arg);
		run_exec(exe, *(command->env));
	}
	return (0);
}

int	**fill_pipes(int count)
{
	int	**array;
	int	i;

	array = (int **)malloc((count - 1) * sizeof(int *));
	if (array == NULL)
		return (0);
	i = 0;
	while (i < count - 1)
	{
		array[i] = (int *)malloc(2 * sizeof(int));
		if (array[i] == NULL)
			exit(1);
		if (pipe(array[i]) == -1)
			exit(1);
		i++;
	}
	return (array);
}
