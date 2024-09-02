#include "builtins.h"

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

void ft_unset(char **env, char *args[])
{
	if (args[1] == NULL)
	{
		return;
	}

	for (int i = 1; args[i] != NULL; i++)
	{
		if (!is_valid_unset(args[i]))
		{
			printf("unset: `%s': not a valid identifier\n", args[i]);
			continue;
		}

		int j = 0;
		while (env[j] != NULL)
		{
			if (ft_strncmp(env[j], args[i], ft_strlen(args[i])) == 0 && env[j][ft_strlen(args[i])] == '=')
			{
				free(env[j]);

				for (int k = j; env[k] != NULL; k++)
				{
					env[k] = env[k + 1];
				}

				break;
			}
			j++;
		}
	}
}
