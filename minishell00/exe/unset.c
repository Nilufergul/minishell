#include "../minishell.h"

int is_valid_unset(const char *str)
{
	if (!str || !*str || !ft_isalpha(str[0]))
		return 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
	}

	return 1;
}

char **remove_env_var(char **env, int index)
{
	int env_size = 0;

	while (env[env_size] != NULL)
		env_size++;

	char **new_env = (char **)malloc(sizeof(char *) * env_size);
	if (!new_env)
		return env;

	for (int k = 0, m = 0; env[k] != NULL; k++)
	{
		if (k != index)
		{
			new_env[m] = env[k];
			m++;
		}
	}
	new_env[env_size - 1] = NULL;

	free(env[index]);
	free(env);

	return new_env;
}

void ft_unset(t_line *line)
{
	if (line == NULL || line->env == NULL || line->arg == NULL)
		return;

	for (int i = 0; line->arg[i] != NULL; i++)
	{
		if (!is_valid_unset(line->arg[i]))
		{
			printf("unset: `%s': not a valid identifier\n", line->arg[i]);
			continue;
		}

		for (int j = 0; (*line->env)[j] != NULL; j++)
		{
			if (ft_strncmp((*line->env)[j], line->arg[i], ft_strlen(line->arg[i])) == 0 && (*line->env)[j][ft_strlen(line->arg[i])] == '=')
			{
				*line->env = remove_env_var(*line->env, j);
				break;
			}
		}
	}
}
