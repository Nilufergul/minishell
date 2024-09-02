#include "../minishell.h"

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