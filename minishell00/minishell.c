
#include "minishell.h"

t_mini *init_mini(t_mini *mini, char** environ)
{
	mini = malloc(sizeof(t_mini));
	if(!mini)
		return (NULL);
	ft_env(mini, environ);
	if(!mini->env)
		return(NULL);
	mini->line = NULL;
	return (mini);
}

int env_size(char **environ)
{
    int i;

    i = 0;
    if (!environ)
        return (0);
    while (environ[i])
        i++;
    return (i);
}

void ft_env(t_mini *mini ,char** environ)
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
		add_history(mini->line);
		routine(mini);
	}
}

void routine(t_mini *mini)
{
	t_line *command;
	t_split *split;
	if(!check_the_syntax(mini))
	{
		return ;
	}
	lexer(mini);
	split = splitter(mini);
	expander(split, mini);
	remove_quotes(split);
	//split for exe to  t_line
	command = split_for_exe(split, mini);
	//to run the line
	//run_command_run(command);
	while(command)
	{
		printf("%s\n", command->cmd);
		printf("%s\n", command->left->name);
		printf("%s\n", command->right->name);
		
		command = command->next;
	}
}

int main(int argc, char** argv,char** environ)
{
	//signal handlelancak
	t_mini *mini;
	(void)argc;
	(void)argv;

	mini = NULL;
	mini = init_mini(mini, environ);
	if(!mini)
		return 0;
	running_shell(mini);
}




