#include "../minishell.h"

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

void	dollar_quest(t_split *split, t_exit_status *exit)
{
	char	*exit_str;
	t_split	*current_split;
	int		i;
	char	*node;

	i = 0;
	current_split = split;
	while (current_split)
	{
		exit_str = ft_itoa(exit->exit_code);
		i = 0;
		node = current_split->node;
		while (node[i] != '\0')
		{
			if ((node[i] == '$') && (node[i + 1] == '?'))
			{
				replace_node_substr(current_split, "$?", exit_str);
				exit->exit_code = 127;
			}
			i++;
		}
		free(exit_str);
		current_split = current_split->next;
	}
}
