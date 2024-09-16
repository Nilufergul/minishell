#include "../minishell.h"

void	expander(t_split *split, t_mini *mini)
{
	while (split)
	{
		if (split->meta == DOLLAR)
		{
			split->node = remove_quotes_two(&split, &mini);
			split->meta = EXCEPT;
		}
		else
			quotes(split);
		split = split->next;
	}
}

void	remove_quotes(t_split *split)
{
	while (split)
	{
		quotes(split);
		split = split->next;
	}
}

void	quotes(t_split *split)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (split->node[i])
	{
		if (split->node[i] == '\"' || split->node[i] == '\'')
		{
			quote = split->node[i];
			j = i;
			i++;
			while (split->node[i] && split->node[i] != quote)
				i++;
			if (split->node[i] == quote)
			{
				char_remove(split, j);
				char_remove(split, i - 1);
				i--;
			}
		}
		else
			i++;
	}
}

void	char_remove(t_split *split, int i)
{
	int	len;

	len = ft_strlen(split->node);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(split->node + i, split->node + i + 1, len - i);
	split->node[len - 1] = '\0';
}

/*   ---------------------------------------------------  */

int	count_substr(const char *str, const char *sub)
{
	int			count;
	const char	*tmp;
	int			sub_len;

	count = 0;
	tmp = str;
	sub_len = ft_strlen(sub);
	tmp = ft_strnstr(tmp, sub, ft_strlen(tmp));
	while (tmp != NULL)
	{
		count++;
		tmp += sub_len;
		tmp = ft_strnstr(tmp, sub, ft_strlen(tmp));
	}
	free((void *)tmp);
	return (count);
}

char	*allocate_new_node(const char *node, const char *var, const char *value)
{
	int		old_len;
	int		new_len;
	int		extra_len;
	char	*new_node;

	old_len = strlen(var);
	new_len = strlen(value);
	extra_len = 0;
	if (new_len > old_len)
	{
		extra_len = (new_len - old_len) * count_substr(node, var);
	}
	new_node = malloc(strlen(node) + extra_len + 1);
	return (new_node);
}

void	replace_substr_in_node(char *new_node,
						const char *node, const char *var, const char *value)
{
	const char	*str;
	char		*pos;
	int			old_len;
	int			new_len;

	str = node;
	pos = new_node;
	old_len = strlen(var);
	new_len = strlen(value);
	while (*str)
	{
		if (ft_strnstr(str, var, ft_strlen(str)) == str)
		{
			ft_strlcpy(pos, value, new_len + 1);
			pos += new_len;
			str += old_len;
		}
		else
		{
			*pos++ = *str++;
		}
	}
	*pos = '\0';
}

void	replace_node_substr(t_split *node, const char *var, const char *value)
{
	char	*new_node;

	if (!node || !node->node || !var || !value)
		return ;
	new_node = allocate_new_node(node->node, var, value);
	if (!new_node)
		return ;
	replace_substr_in_node(new_node, node->node, var, value);
	free(node->node);
	node->node = new_node;
}

void dollar_quest(t_split *split, t_exit_status *exit)
{
    char *exit_str;
    t_split *current_split = split;

    while (current_split)
    {
		exit_str = ft_itoa(exit->exit_code);
        int i = 0; // Reset index for each node
        char *node = current_split->node; // Assuming node is a mutable string

        while (node[i] != '\0')
        {
            // Check for "$?" followed by a non-alphanumeric character
            if ((node[i] == '$') && (node[i + 1] == '?'))
            {
                replace_node_substr(current_split, "$?", exit_str);
               // printf("Updated node: %s\n", current_split->node); // Print updated nodexx
                exit->exit_code = 127;
            }
            i++;
        }
		free(exit_str);  // burasının yeri değişti
        current_split = current_split->next; // Move to the next node
    }
}
