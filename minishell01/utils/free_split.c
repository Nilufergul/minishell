#include "../minishell.h"

void	free_the_split(t_split *split)
{
	t_split	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		free(tmp->node);
		free(tmp);
	}
	free(split);
}

void	free_the_minis(t_mini *mini)
{
	free(mini->line);
}

void	free_and_cpy_env(t_line *line)
{
	int		i;
	char	**tmp;

	i = 0;
	while (line->env[i])
		i++;
	tmp = (char **)malloc((i + 1) * sizeof(char *));
	if (!tmp)
	{
	}
	i = 0;
	while (line->env[i])
	{
		tmp[i] = *line->env[i];
		i++;
	}
	tmp[i] = NULL;
	i = 0;
	while (line->env[i])
	{
		free(line->env[i]);
		i++;
	}
}
