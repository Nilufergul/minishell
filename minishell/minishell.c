
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

void lexer(t_mini *mini)
{
	int i;
	i = 0;

	mini->line = ft_strtrim(mini->line, " "); // başta sonda bosluk silindi ;)
	if(ft_strnstr(mini->line,"env", 3))
	{
		while(i < (env_size(mini->env)))
		{
			printf("%s\n", mini->env[i]);
			i++;
		}
	}
}

void routine(t_mini *mini)
{
	lexer(mini);
}

/*void routine(t_mini *mini)
{
	//lexer  
	 pipe
	redirect mixed
	open quote
	
	
	//parser
	gereksiz boslukları silme(başta ve sonda)
	$(real) aç (metalara  tırnak at)" "
	meta char ayır(bosluk at)
	gerçek bosluğa ayır (nodea falan)(split)
	meta char leri ayır
	gereksiz tırnak sil (backslash ??)


	//exe
*/


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