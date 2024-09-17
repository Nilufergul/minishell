#include "../minishell.h"

void	quote_check_meta(char *str, int *i)
{
	char	quote;

	if (str[*i] && (str[*i] == '\"' || str[*i] == '\''))
	{
		quote = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != quote)
		{
			(*i)++;
		}
	}
}

void	shift_and_insert(char *str, int *len, int pos)
{
	int	j;

	j = *len;
	while (j > pos)
	{
		str[j + 1] = str[j];
		j--;
	}
	str[pos + 1] = ' ';
	(*len)++;
	str[*len] = '\0';
}

int	count_meta_character(char *str, char s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == s && str[i + 1] != ' ')
			|| (str[i] == s && str[i - 1] != ' '))
			count++;
		i++;
	}
	i += count;
	return (i);
}

void	adding_space(t_mini *mini, char s)
{
	int		i;
	int		len;
	int		count;
	char	*new_line;
	char	*tmp;

	i = 0;
	len = ft_strlen(mini->line);
	count = count_meta_character(mini->line, s);
	new_line = malloc(sizeof(char) * (len + count + 1));
	if (!new_line)
		return ;
	ft_strlcpy(new_line, mini->line, (len + count + 1));
	while (new_line[i] != '\0')
	{
		quote_check_meta(new_line, &i);
		if ((new_line[i] == s && (i != 0 && new_line[i - 1] != ' '
					&& new_line[i - 1] != s)))
			shift_and_insert(new_line, &len, (i - 1));
		if ((new_line[i] == s
				&& (new_line[i + 1] != ' ' && new_line[i + 1] != s)))
			shift_and_insert(new_line, &len, i);
		i++;
	}
	tmp = mini->line;
	mini->line = new_line;
	free(tmp);
}

void	lexer(t_mini *mini)
{
	adding_space(mini, '>');
	adding_space(mini, '<');
	adding_space(mini, '|');
}
