#include "../minishell.h"

int quote_checker_1(t_mini *mini)
{
	int i;
	char quote;
	
	i = 0;
	while(mini->line[i])
	{
		if(mini->line[i] == '\"' || mini->line[i] == '\'')
		{
			quote = mini->line[i];
			i++;
			while(mini->line[i] && mini->line[i] != quote)
			{
				i++;
			}
			if(mini->line[i] == '\0')
				return(0);
		}
		i++;
	}
	return(1);
}

void quotes(t_split *split)
{
	int len;	

	len = ft_strlen(split->node);
	
	if((split->node[0] == '\"' && split->node[len - 1] == '\"') || (split->node[0] == '\'' && split->node[len - 1] == '\''))
	{
		char *new_str = malloc(len);
		if (!new_str)
			return;

		ft_strlcpy(new_str, ++split->node, len-1);
		split->node = new_str;
	}
}

void remove_quotes(t_split *split)
{
	while(split)
	{
		quotes(split);
		split = split->next;
	}
}