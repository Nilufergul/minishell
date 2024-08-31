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

void ft_unset(t_mini *mini, char *args[])
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
		while (mini->env[j] != NULL)
		{

			if (ft_strncmp(mini->env[j], args[i], ft_strlen(args[i])) == 0 && mini->env[j][ft_strlen(args[i])] == '=')
			{
				free(mini->env[j]);

				for (int k = j; mini->env[k] != NULL; k++)
				{
					mini->env[k] = mini->env[k + 1];
				}

				mini->env[j] = NULL;
				break;
			}
			j++;
		}
	}
}
