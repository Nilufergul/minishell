#include "../minishell.h"

enum type	meta_type_2(int i, char *str)
{
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			return (HEREDOC);
		return (LESS);
	}
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			return (GREATER);
		return (GREAT);
	}
	if (str[i] == '$')
		return (DOLLAR);
	return(EXCEPT);
}

enum type meta_type(char *str) {
    int i;
    char quote;
    int in_quote = 0;

    i = 0;
    while (str[i]) {
        if (str[i] == '\"' || str[i] == '\'') {
            quote = str[i];
            i++;
            while (str[i] && str[i] != quote) {
                if (str[i] == '$')  // Check for the dollar sign within quotes
                    return (DOLLAR);
                i++;
            }
            if (str[i]) // Skip the closing quote
                i++;
        } else {
            if (str[i] == '|')
                return (PIPE);
            if (meta_type_2(i, str) != EXCEPT)
                return (meta_type_2(i, str));
            i++;
        }
    }
    return (EXCEPT);
}

t_split	*sub_node(const char *str, unsigned int start, size_t len)
{
	t_split	*node;
	size_t	j;

	if (!str)
		return (NULL);
	node = malloc(sizeof(t_split));
	if (!node)
		return (NULL);
	node->node = malloc(sizeof(char) * (len + 1));
	if (!node->node)
	{
		free(node);
		return (NULL);
	}
	j = 0;
	while (j < len)
	{
		node->node[j] = str[start + j];
		j++;
	}
	node->node[j] = '\0';
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
	t_split	*splitted_head;

	i = 0;
	start = 0;
	head = 1;
	splitted = NULL;
	splitted_head = NULL;
	while (mini->line[i])
	{
		if (mini->line[i] == '\'' || mini->line[i] == '\"')
		{
			quote = mini->line[i];
			i++;
			while (mini->line[i] != '\0' && mini->line[i] != quote)
				i++;
			if (mini->line[i] == '\0')
				return (splitted_head);
			i++;
		}
		while (mini->line[i] == ' ')
			i++;
		if (mini->line[i] == '\0')
			break;
		start = i;
		while (mini->line[i] != '\0' && mini->line[i] != ' ' &&
			mini->line[i] != '\'' && mini->line[i] != '\"')
			i++;
		splitted = sub_node(mini->line, start, i - start);
		if (head == 1)
		{
			splitted_head = splitted;
			head = 0;
		}
		else
		{
			t_split *current = splitted_head;
			while (current->next != NULL)
				current = current->next;
			current->next = splitted;
		}
		while (mini->line[i] == ' ')
			i++;
	}
	return (splitted_head);
}


int	main()
{
	t_mini *mini;

	mini = malloc(sizeof(t_mini *));
	mini->line = malloc(sizeof(char)*1200);
	strcpy(mini->line,"< > \'$\' >> $ |"); //birden fazla bosluk
	t_split *head;

	head = splitter(mini);
	while (head != NULL)
	{
		printf("%d-", head->meta);
		head = head->next;
	}
}