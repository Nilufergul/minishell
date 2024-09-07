#include "../minishell.h"

void free_the_split(t_split *split)
{
	t_split *tmp;
	while(split)
	{
		tmp = split;
		split = split->next;
		free(tmp->node);
		free(tmp);
	}
	free(split);
}

void free_the_minis(t_mini *mini)
{
	free(mini->line);
}