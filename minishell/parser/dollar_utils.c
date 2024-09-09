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
	if (!new_node)  // Bellek tahsisi başarısız olduysa
		return (NULL);
	return (new_node);
}
char	*ft_strnstr1(const char *h, const char *ndl, size_t n)
{
	size_t	i;
	size_t	j;
	i = 0;
	j = 0;
	if (ndl[0] == '\0')
		return ((char *)h);
	while (h[i] != '\0' && i < n)
	{
		if(h[i] == '\'')
		{
			i++;
			while(h[i] != '\'')
			{
				i++;
			}
		}
		if (h[i] == ndl[j])
		{
			while (h[i + j] == ndl[j] && i + j < n)
			{
				if (ndl[j + 1] == '\0')
					return ((char *)h + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}


void	replace_substr_in_node(char *new_node,
						const char *node, const char *var, const char *value)
{
	const char	*str;
	char		*pos;
	int			old_len;
	int			new_len;
	int			in_single_quote;

	str = node;
	pos = new_node;
	old_len = strlen(var);
	new_len = strlen(value);
	in_single_quote = 0;

	while (*str)
	{
		// Tek tırnak içinde olup olmadığımızı kontrol ederiz
		if (*str == '\'')
			in_single_quote = !in_single_quote;  // Tek tırnak flag'ini değiştir

		// Eğer tek tırnak içinde değilsek, arama yap
		if (!in_single_quote && ft_strnstr1(str, var, ft_strlen(str)) == str)
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

int	quoted_dollar(t_split *split)
{
	int	i;

	i = 0;
	while (split->node[i] != '\0')
	{
		if ((split->node[i] == '$') && (split->node[i + 1] == '\"'
				|| split->node[i + 1] == '\''))
		{
			return (1);
		}
		i++;
	}
	return (0);
}

