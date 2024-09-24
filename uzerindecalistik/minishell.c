/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:05:53 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 18:56:41 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini	*mini_initializer(t_mini *mini, char **environ)
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

void	procedure(t_mini *mini, t_exit_status *exit_t)
{
	t_line	*command;
	t_split	*split;
	char	*tmp;

	tmp = mini->line;
	mini->line = ft_strtrim(mini->line, " ");
	mini->line = ft_strtrim(mini->line, "\t");
	free(tmp);
	if (ft_strcmp(mini->line, "") == 0)
	{
		free(mini->line);
		return ;
	}
	if (!checking_syntax(mini))
	{
		exit_t->exit_code = 258;
		free(mini->line);
		return ;
	}
	lexer(mini);
	split = split_to_nodes(mini);
	if (!split)
		return ;
	procedure2(split, mini, exit_t);
	command = ready_for_exe(split, mini);
	procedure3(command, split, exit_t);
}

void	start_shell(t_mini *mini, t_exit_status *exit)
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
		procedure(mini, exit);
	}
}

int	main(int argc, char **argv, char **environ)
{
	t_mini			*mini;
	t_exit_status	*exit_status;

	exit_status = malloc(sizeof(t_exit_status));
	exit_status->exit_code = 0;
	(void) argc;
	(void) argv;
	mini = NULL;
	init_signals(0);
	mini = mini_initializer(mini, environ);
	if (!mini)
		return (0);
	start_shell(mini, exit_status);
}
