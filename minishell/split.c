#include "lib/minishell.h"

int	real_space_counter(char const *s)
{
	int	i;
	int	count;
	char quote;

	count = 0;
	i = 0;
	while (s[i])
	{
		if(s[i] == '\'' || s[i] == '\"')
		{
			quote = s[i];
			i++;
			while(s[i] != '\0' && s[i] != quote)
				i++;
			if(s[i] == '\0')
				return (count);
		}	
		if(s[i] == ' ')
		{
			count++;
		}
		i++;
	}
	return (count);
}

enum type meta_type(char *str)//"" icindekileri de atayacak
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '|')
			return (PIPE);
		if(str[i] == '<')
		{
			if(str[i+1] == '<')
				return (HEREDOC);
		}
		if(str[i] == '<')
			return (LESS);
		if(str[i] == '>')
		{
			if(str[i+1] == '>')
				return (GREATER);
		}
		if(str[i] == '>')
			return (GREAT);
		i++;
	}
	return (EXEC);
}

t_split *sub_node(const char *str, unsigned int start, size_t len)
{
	t_split *node;
	int		i;

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
	i = start;
	while(i < len)
	{
		node->node[i] = str[start+i];
		i++;
	}
	node->node[i] = '\0';
	node->meta = meta_type(node->node);
	node->next = NULL;
	return (node);
}

t_split	*splitter(t_mini *mini)
{
	int		i;
	int		start;
	int		head;
	char	quote;
	t_split	*splitted;
	t_split *splitted_head;

	i = 0;
	start = 0;
	head = 1;
	splitted = malloc(sizeof(t_split));
	if (!splitted)
		return (NULL);
	while (mini->line[i])
	{
		if(mini->line[i] == '\'' || mini->line[i] == '\"')
		{
			quote = mini->line[i];
			i++;
			while(mini->line[i] != '\0' && mini->line[i] != quote)
				i++;
			if(mini->line[i] == '\0')
				return (splitted);
			i++;
		}
		if(head == 1 && mini->line[i] == ' ')
		{
			splitted = sub_node(mini->line, 0, i);
			splitted_head = splitted;
			head = 0;
			start = i;
			i++;
		}
		else if(mini->line[i] == ' ')
		{
			splitted->next = sub_node(mini->line, start, i);
			start = i;
			splitted = splitted->next;
			i++;
		}
		i++;
	}
	return (splitted_head);
}

#include <stdio.h>
int main(){
	char a[] = "ech adfb afasf yfhgh";
	t_mini *minik;
	t_split *splitted;

	minik = (t_mini *)malloc(sizeof(t_mini));
	minik->line = malloc(sizeof(char)*20);

	splitted = (t_split *)malloc(sizeof(t_split));

	minik->line = a;
	splitted = splitter(minik);

	printf("%s\n",splitted->node);
	splitted = splitted->next;

	printf("%s\n",splitted->node);
	splitted = splitted->next;

	printf("%s\n",splitted->node);
}