
#include "../minishell.h"

enum type meta_type(char *str)
{
    int i;
	char quote;
    
	i = 0;
	while(str[i])
	{
		if(str[i] == '\"' || str[i] == '\'')
		{
			quote = str[i];
			i++;
			while(str[i] && str[i] != quote)
				i++;
		}
		if(str[i] == '|')
            return (PIPE);
        if(str[i] == '<')
        {
            if(str[i+1] == '<')
                return (HEREDOC);
            return (LESS);
        }
        if(str[i] == '>')
        {
            if(str[i+1] == '>')
                return (GREATER);
            return (GREAT);
        }
		i++;
	}
    return (EXCEPT);
}

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



t_split *sub_node(const char *str, unsigned int start, size_t len)
{
    t_split *node;
    size_t j;

    if (!str) 
        return NULL;
    node = malloc(sizeof(t_split));
    if (!node) 
        return NULL;
    node->node = malloc(sizeof(char) * (len + 1));
    if (!node->node) {
        free(node);
        return NULL;
    }
    j = 0;
    while(j < len)
    {
        node->node[j] = str[start + j];
        j++;
    }
    node->node[j] = '\0';
    node->meta = meta_type(node->node);
    node->next = NULL;
    return (node);
}

t_split *splitter(t_mini *mini)
{
    int i;
    int start;
    int head;
    char quote;
    t_split *splitted;
    t_split *splitted_head;

    i = 0;
    start = 0;
    head = 1;
    splitted = NULL;
    while (mini->line[i])
    {
        if(mini->line[i] == '\'' || mini->line[i] == '\"')
        {
            quote = mini->line[i];
            i++;
            while(mini->line[i] != '\0' && mini->line[i] != quote)
                i++;
            if(mini->line[i] == '\0')
                return (splitted_head);
            i++;
        }
        if(head == 1 && mini->line[i] == ' ')
        {
            splitted = sub_node(mini->line, 0, i);
            splitted_head = splitted;
            head = 0;
            start = i + 1;
        }
        else if(mini->line[i] == ' ')
        {
            splitted->next = sub_node(mini->line, start, i - start);
            splitted = splitted->next;
            start = i + 1;
        }
        i++;
    }
    if (start < i)
        splitted->next = sub_node(mini->line, start, i - start);
    return (splitted_head);
}
