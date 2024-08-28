#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "deneme.h"

int main(int argc, char *argv[], char *envp[])
{
	t_mini mini;
	mini.line = NULL;
	mini.env = NULL;
	size_t len = 0;
	char *input = NULL;
	char *token = NULL;
	char *args[10];

	for (int i = 0; envp[i] != NULL; i++)
	{
		mini.env = realloc(mini.env, sizeof(char *) * (i + 2));
		mini.env[i] = strdup(envp[i]);
		mini.env[i + 1] = NULL;
	}

	while (1)
	{
		printf("minishell> ");
		getline(&input, &len, stdin);

		input[strcspn(input, "\n")] = 0;

		int i = 0;
		token = strtok(input, " ");
		while (token != NULL && i < 10)
		{
			args[i++] = token;
			token = strtok(NULL, " ");
		}
		args[i] = NULL;

		if (strcmp(args[0], "export") == 0)
		{
			builtin_export(&mini, args);
		}
		else if (strcmp(args[0], "unset") == 0)
		{
			builtin_unset(&mini, args);
		}
		else if (strcmp(args[0], "env") == 0)
		{
			print_env(mini.env);
		}
		else if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		else
		{
			printf("Komut tanınmadı: %s\n", args[0]);
		}
	}

	free(input);

	for (int i = 0; mini.env[i] != NULL; i++)
	{
		free(mini.env[i]);
	}
	free(mini.env);

	return 0;
}
