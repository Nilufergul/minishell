
#include "../minishell.h"

char	*get_copy(char *result, char **arr)
{
	char	*cur;
	char	*temp;
	int		i;

	cur = result;
	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		temp = ft_strjoin(cur, " ");
		free(cur);
		cur = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
	return (cur);
}

int	built_in2(t_line *command)
{
	 if (ft_strcmp(command->cmd, "cd") == 0)
		run_command_run(command);
	else if (ft_strcmp(command->cmd, "export") == 0)
		run_command_run(command);
	else if (ft_strcmp(command->cmd, "unset") == 0)
		run_command_run(command);
	else if (ft_strcmp(command->cmd, "env") == 0)
		run_command_run(command);
	else if (ft_strcmp(command->cmd, "exit") == 0)
		run_command_run(command);
	else
		return (0);
	return (1);
}
