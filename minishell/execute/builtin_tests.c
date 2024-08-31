#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

#define BUFFER_SIZE 1024

void process_command(char *cmd, t_mini *mini)
{
	char *args[100];
	int i = 0;

	char *token = strtok(cmd, " \t\n");
	while (token != NULL)
	{
		args[i++] = token;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
	{
		return;
	}

	if (strcmp(args[0], "cd") == 0)
	{
		ft_cd(args[1]);
	}
	else if (strcmp(args[0], "pwd") == 0)
	{
		ft_pwd();
	}
	else if (strcmp(args[0], "echo") == 0)
	{
		int index = echo_index(cmd);
		if (index >= 0)
		{
			printf("%s\n", cmd + index);
		}
	}
	else if (strcmp(args[0], "export") == 0)
	{
		ft_export(mini, args);
	}
	else if (strcmp(args[0], "unset") == 0)
	{
		ft_unset(mini, args);
	}
	else if (strcmp(args[0], "env") == 0)
	{
		ft_environment(mini);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		ft_exit(args);
	}
	else
	{
		printf("minishell: command not found: %s\n", args[0]);
	}
}

int main(int argc, char *argv[], char *envp[])
{

	(void)argc;
	(void)argv;
	
	char buffer[BUFFER_SIZE];
	t_mini mini;
	int env_count = 0;

	while (envp[env_count] != NULL)
		env_count++;

	mini.env = malloc(sizeof(char *) * (env_count + 1));

	for (int i = 0; i < env_count; i++)
		mini.env[i] = strdup(envp[i]);
	mini.env[env_count] = NULL;

	while (1)
	{
		printf("minishell> ");
		if (fgets(buffer, BUFFER_SIZE, stdin) == NULL)
		{
			perror("fgets");
			continue;
		}

		if (strcmp(buffer, "exit\n") == 0)
		{
			break;
		}

		process_command(buffer, &mini);
	}

	for (int i = 0; mini.env[i] != NULL; i++)
	{
		free(mini.env[i]);
	}
	free(mini.env);

	return 0;
}
