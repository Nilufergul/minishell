#include "../minishell.h"
#include "../minishell.h"

void quotes(t_split *split)
{
	int i;
	int j;
	char quote;

	i = 0;
	while (split->node[i])
	{	
		if (split->node[i] == '\"' || split->node[i] == '\'')
		{
			quote = split->node[i];
			j = i;
			i++;
			while (split->node[i] && split->node[i] != quote)
			{
				i++;
			}
			if (split->node[i] == quote)
			{
				char_remove(split, j);
				char_remove(split, i - 1);
				i--;
			}
		}
		else
		{
			i++;
		}
	}
}

void char_remove(t_split *split, int i)
{
	int len;

	len = ft_strlen(split->node);
	if (i < 0 || i >= len)
		return;

	ft_memmove(split->node + i, split->node + i + 1, len - i);
	split->node[len - 1] = '\0';
}

void remove_quotes(t_split *split)
{
	while (split)
	{
		quotes(split);
		split = split->next;
	}
}

void expander(t_split *split, t_mini *mini)  // $'PAT'   kontroo edilcek
{
	while(split)
	{
		if(split->meta == DOLLAR)
		{
			if(quoted_dollar(split))
			{
				if(!(split->node[0] == '\"' || split->node[0] == '\''))
				{
					replace_node_substr(split,"$", "");
				}
			}
			handle_dollar(split, mini);
		}
		split = split->next;
	}
}


