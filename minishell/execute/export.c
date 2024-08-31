#include "builtins.h"

void *ft_realloc(void *ptr, size_t current_size, size_t new_size)
{
	if (ptr == NULL)
	{
		return malloc(new_size);
	}

	if (new_size == 0)
	{
		free(ptr);
		return NULL;
	}

	void *new_ptr = malloc(new_size);
	if (new_ptr == NULL)
	{
		return NULL;
	}

	ft_memcpy(new_ptr, ptr, current_size < new_size ? current_size : new_size);

	free(ptr);
	return new_ptr;
}

int is_valid(const char *str)
{
	if (!str || !*str || *str == '=' || !ft_isalpha(*str))
		return 0;

	for (int i = 0; str[i] != '\0' && str[i] != '='; i++)
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return 0;
	}

	return 1;
}

void print_export(t_mini *mini)
{
	for (int i = 0; mini->env[i] != NULL; i++)
	{
		char *equal_sign = ft_strchr(mini->env[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", mini->env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
		{
			printf("declare -x %s\n", mini->env[i]);
		}
	}
}

void create_update(t_mini *mini, const char *name, const char *value)
{
	int i = 0;
	size_t name_len = ft_strlen(name);
	size_t value_len = ft_strlen(value);
	size_t total_len = name_len + value_len + 2;

	while (mini->env[i] != NULL)
	{
		if (ft_strncmp(mini->env[i], name, name_len) == 0 && mini->env[i][name_len] == '=')
		{
			free(mini->env[i]);

			mini->env[i] = malloc(total_len);
			if (mini->env[i] == NULL)
				return;

			ft_strlcpy(mini->env[i], name, total_len);
			mini->env[i][name_len] = '=';
			ft_strlcpy(mini->env[i] + name_len + 1, value, total_len - name_len - 1);

			return;
		}
		i++;
	}

	mini->env = ft_realloc(mini->env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (mini->env == NULL)
		return;

	mini->env[i] = malloc(total_len);
	if (mini->env[i] == NULL)
		return;

	ft_strlcpy(mini->env[i], name, total_len);
	mini->env[i][name_len] = '=';
	ft_strlcpy(mini->env[i] + name_len + 1, value, total_len - name_len - 1);

	mini->env[i + 1] = NULL;
}

void ft_export(t_mini *mini, char *args[])
{
	if (args[1] == NULL)
	{
		print_export(mini);
	}
	else
	{
		for (int i = 1; args[i] != NULL; i++)
		{
			if (!is_valid(args[i]))
			{
				printf("export: `%s': not a valid identifier\n", args[i]);
				continue;
			}

			char *equal_sign = ft_strchr(args[i], '=');
			if (equal_sign != NULL)
			{
				*equal_sign = '\0';

				if (is_valid(args[i]))
				{
					create_update(mini, args[i], equal_sign + 1);
				}
				else
				{
					printf("export: `%s': not a valid identifier\n", args[i]);
				}
			}
			else
			{

				if (is_valid(args[i]))
				{
					create_update(mini, args[i], "");
				}
				else
				{
					printf("export: `%s': not a valid identifier\n", args[i]);
				}
			}
		}
	}
}
