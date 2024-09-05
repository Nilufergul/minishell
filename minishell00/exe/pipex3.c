
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
	if (ft_strncmp(command->cmd, "echo" , ft_strlen(command->cmd)) == 0)
		echo_main(command->arg[0]);
	else if (ft_strncmp(command->cmd, "pwd" ,ft_strlen(command->cmd)) == 0)
		pwd();
	else if (ft_strncmp(command->cmd, "cd", ft_strlen(command->cmd)) == 0)
		ft_cd(command->arg[0]);
	else if (ft_strncmp(command->cmd, "export" ,ft_strlen(command->cmd)) == 0)
		ft_export(command->arg, (command->env));
	else if (ft_strncmp(command->cmd, "unset",ft_strlen(command->cmd)) == 0)
		ft_unset(command->arg, (command->env));
	else if (ft_strncmp(command->cmd, "env",ft_strlen(command->cmd)) == 0)
		ft_environment((command->env));
	else if (ft_strncmp(command->cmd, "exit", ft_strlen(command->cmd)) == 0)
		ft_exit(command->arg);
	else
		return (0);
	return (1);
}

void	run_command_run(t_line *command)
{
	char	*exe;
	int		output;
	int		input;

	input = dup(0);
	output = dup(1);
	if (fd_len(&(command->left)) != 0)
		dup2(open_lefts(command->left), 0);
	if (fd_len(&(command->right)) != 0)
		dup2(open_rights(command->right), 1);
	if (!built_in(command))
	{
		exe = get_copy(ft_strdup(command->cmd), command->arg);
		run_exec(exe, (command->env));
	}
	dup2(input, 0);
	close(input);
	dup2(output, 1);
	close(output);
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
