#include "pipex.h"


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

void print_export(char **env)
{
	for (int i = 0; env[i] != NULL; i++)
	{
		char *equal_sign = ft_strchr(env[i], '=');
		if (equal_sign != NULL)
		{
			*equal_sign = '\0';
			printf("declare -x %s=\"%s\"\n", env[i], equal_sign + 1);
			*equal_sign = '=';
		}
		else
		{
			printf("declare -x %s\n", env[i]);
		}
	}
}

void create_update(char **env, const char *name, const char *value)
{
	int i = 0;
	size_t name_len = ft_strlen(name);
	size_t value_len = ft_strlen(value);
	size_t total_len = name_len + value_len + 2;

	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=')
		{
			free(env[i]);

			env[i] = malloc(total_len);
			if (env[i] == NULL)
				return;

			ft_strlcpy(env[i], name, total_len);
			env[i][name_len] = '=';
			ft_strlcpy(env[i] + name_len + 1, value, total_len - name_len - 1);

			return;
		}
		i++;
	}

	env = ft_realloc(env, sizeof(char *) * (i + 1), sizeof(char *) * (i + 2));
	if (env == NULL)
		return;

	env[i] = malloc(total_len);
	if (env[i] == NULL)
		return;

	ft_strlcpy(env[i], name, total_len);
	env[i][name_len] = '=';
	ft_strlcpy(env[i] + name_len + 1, value, total_len - name_len - 1);

	env[i + 1] = NULL;
}

void ft_export(char **args, char **env)
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
					create_update(env, args[i], equal_sign + 1);
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
					create_update(env, args[i], "");
				}
				else
				{
					printf("export: `%s': not a valid identifier\n", args[i]);
				}
			}
		}
	}