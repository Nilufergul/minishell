#include "../minishell.h"

char	*get_env_value(char *var, char **env)
{
	char	**line;
	char	*res;
	int		i;

	i = 0;
	res = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (ft_strcmp(var, line[0]) == 0)
		{
			res = ft_strdup(line[1]);
			free(line[0]);
			free(line[1]);
			free(line);
			return (res);
		}
		free(line[0]);
		free(line[1]);
		free(line);
		i++;
	}
	return (res);
}
