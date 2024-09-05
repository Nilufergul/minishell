
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

void ft_unset(char **env, char **args)
{
	for (int i = 0; args[i] != NULL; i++)
	{
		if (!is_valid_unset(args[i]))
		{
			printf("unset: `%s': not a valid identifier\n", args[i]);
			continue;
		}

		for (int j = 0; env[j] != NULL; j++)
		{
			if (ft_strncmp(env[j], args[i], ft_strlen(args[i])) == 0 && env[j][ft_strlen(args[i])] == '=')
			{
				env = remove_env_var(env, j);
				break;
			}
		}
	}
}
