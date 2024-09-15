
#include "minishell.h"

t_mini	*init_mini(t_mini *mini, char **environ)
{
	mini = malloc(sizeof(t_mini));
	if (!mini)
		return (NULL);
	ft_env(mini, environ);
	if (!mini->env)
		return (NULL);
	mini->line = NULL;
	return (mini);
}

void	ft_env(t_mini *mini, char **environ)
{
	int	i;

	i = 0;
	if (!environ)
		return ;
	while (environ[i])
		i++;
	mini->env = malloc(sizeof(char **) * (i + 1));
	if (!mini->env)
		return ;
	i = 0;
	while (environ[i])
	{
		mini->env[i] = ft_strdup(environ[i]);
		i++;
	}
	mini->env[i] = NULL;
}

void	running_shell(t_mini *mini,t_exit_status *exit)
{
	while (true)
	{
		mini->line = readline("minishell$> ");
		ctrl_d(mini->line);
		if (g_catch_ctrlc == 1)
			g_catch_ctrlc = 0;
		if (mini->line[0] == 0)
		{
			free(mini->line);	
			continue ;
		}
		
			
		if (mini->line[0] == 0)
			continue ;
		add_history(mini->line);
		routine(mini,exit);
	}
}

void	routine(t_mini *mini, t_exit_status *exit)
{
	t_line	*command;
	t_split	*split;

	if (!check_the_syntax(mini))
		return ;
	lexer(mini);
	split = splitter(mini);
	dollar_quest(split, exit);
	//printf("glb burda \n");
	//getchar();
	expander(split, mini);
	remove_quotes(split);
	free_the_minis(mini);
	command = split_for_exe(split, mini);
	make_pipe(command, exit);
	free_the_split(split);
	free_command(command);
}

int	main(int argc, char **argv, char **environ)
{
	t_mini	*mini;
	t_exit_status *exit_status;

	exit_status=malloc(sizeof(t_exit_status));
	exit_status->exit_code = 0;
	(void) argc;
	(void) argv;
	mini = NULL;
    init_signals(0);
	mini = init_mini(mini, environ);
	if (!mini)
		return (0);
	running_shell(mini,exit_status);
}