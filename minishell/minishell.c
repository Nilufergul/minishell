
#include "minishell.h"

t_mini *init_mini(t_mini *mini, char** environ, char** argv)
{
	mini = malloc(sizeof(t_mini));
	if(!mini)
		return (NULL);
	get_env(mini, environ);
	if(!mini->env)
		return(NULL);
	mini->arg = argv;
	mini->line = NULL;
	return (mini);
}

void get_env(t_mini *mini ,char** environ)
{
	int i;
	
	mini->env = malloc(sizeof(char **) * (env_size(environ) + 1));
	if (!mini->env)
		return;
	i = 0;

	while(environ[i])
	{
		mini->env[i] = ft_strdup(environ[i]);
		i++;
	}
}

void running_shell(t_mini *mini)
{
	while(true)
	{
		mini->line = readline("minishell$> ");
		if(!mini->line)
		{
			break ;
		}
		//add_history(mini->line);

	}
}

int main(int argc, char** argv,char** environ)
{
	// signal handlelancak
	t_mini *mini;


	mini = NULL;
	mini = init_mini(mini, environ, argv);
	if(!mini)
		return (argc);//????
	running_shell(mini);
}