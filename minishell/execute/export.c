#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "deneme.h"

void print_env(char **env)
{
	for (int i = 0; env[i] != NULL; i++)
	{
		printf("%s\n", env[i]);
	}
}

void print_export(t_mini *mini)
{
	for (int i = 0; mini->env[i] != NULL; i++)
	{
		char *equal_sign = strchr(mini->env[i], '=');
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

void add_or_update_variable(t_mini *mini, const char *name, const char *value)
{
	int i = 0;
	while (mini->env[i] != NULL)
	{
		if (strncmp(mini->env[i], name, strlen(name)) == 0 && mini->env[i][strlen(name)] == '=')
		{
			free(mini->env[i]);
			mini->env[i] = malloc(strlen(name) + strlen(value) + 2);
			sprintf(mini->env[i], "%s=%s", name, value);
			return;
		}
		i++;
	}

	mini->env = realloc(mini->env, sizeof(char *) * (i + 2));
	mini->env[i] = malloc(strlen(name) + strlen(value) + 2);
	sprintf(mini->env[i], "%s=%s", name, value);
	mini->env[i + 1] = NULL;
}

void builtin_export(t_mini *mini, char *args[])
{
	if (args[1] == NULL)
	{

		print_export(mini);
	}
	else
	{
		for (int i = 1; args[i] != NULL; i++)
		{
			char *equal_sign = strchr(args[i], '=');
			if (equal_sign != NULL)
			{
				*equal_sign = '\0';
				add_or_update_variable(mini, args[i], equal_sign + 1);
			}
		}
	}
}
