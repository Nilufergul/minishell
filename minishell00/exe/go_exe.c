
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
	 if (ft_strncmp(command->cmd, "cd",ft_strlen(command->cmd)) == 0)
		run_command_run(command);
	else if (ft_strncmp(command->cmd, "export",ft_strlen(command->cmd)) == 0)
		run_command_run(command);
	else if (ft_strncmp(command->cmd, "unset",ft_strlen(command->cmd)) == 0)
		run_command_run(command);
	else if (ft_strncmp(command->cmd, "env",ft_strlen(command->cmd)) == 0)
		run_command_run(command);
	else if (ft_strncmp(command->cmd, "exit",ft_strlen(command->cmd)) == 0)
		run_command_run(command);
	else
		return (0);
	return (1);
}
