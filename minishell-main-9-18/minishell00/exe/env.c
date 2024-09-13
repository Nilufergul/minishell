#include "../minishell.h"

int	ft_environment(char **env)
{
	int	i;

	i = 1;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
	return (0);
}
