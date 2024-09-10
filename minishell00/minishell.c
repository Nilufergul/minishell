
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

void	running_shell(t_mini *mini)
{
	while (true)
	{
		mini->line = readline("minishell$> ");
		if (!mini->line)
			break ;
		add_history(mini->line);
		routine(mini);
	}
}

void	routine(t_mini *mini)
{
	t_line	*command;
	t_split	*split;

	if (!check_the_syntax(mini))
		return ;
	lexer(mini);
	split = splitter(mini);
	expander(split, mini);
	free_the_minis(mini);
	command = split_for_exe(split, mini);
	free_the_split(split);
	make_pipe(command);
	free_command(command);
}

int	main(int argc, char **argv, char **environ)
{
	t_mini	*mini;

	(void) argc;
	(void) argv;
	mini = NULL;
	mini = init_mini(mini, environ);
	if (!mini)
		return (0);
	running_shell(mini);
}
