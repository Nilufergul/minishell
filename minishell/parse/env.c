
#include "lib/minishell.h"
int env_size(char **environ)
{
    int i;

    i = 0;
    if(!environ)
        return (0);
    while(environ[i])
        i++;
    return (i);
}

void get_env(t_mini *built)
{
	extern char **environ;
	int i;

	built->env = malloc(sizeof(char *) * (env_size(environ) + 1));
	i = 0;

	while(environ[i])
	{
		built->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

void ft_env(t_mini *built)
{
	int i;
	i = 0;
	while(built->env[i])
	{
		printf("%s\n", built->env[i]);
		i++;
	}
}