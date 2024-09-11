#include "../minishell.h"

int	skip_quotes(const char *line, int i)
{
	char	quote;

	quote = line[i];
	i++;
	while (line[i] && line[i] != quote)
		i++;
	if (line[i])
		i++;
	return (i);
}

void	skip_spaces(const char *line, int *i)
{
	while (line[*i] == ' ')
		(*i)++;
}

void	handle_token(const char *line, int *i)
{
	while (line[*i] && line[*i] != ' ')
	{
		if (line[*i] == '\0')
			return ;
		if (line[*i] == '\"' || line[*i] == '\'')
			*i = skip_quotes(line, *i);
		if (line[*i] == ' ')
			return ;
		if (line[*i] == '\0')
			return ;
		(*i)++;
	}
}

int	closed_quotes_index(const char *input)
{
	int	quote;
	int	i;
	int	j;

	i = 0;
	j = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
		{
			j = i + 1;
			quote = input[i];
			while (input[j] && input[j] != quote)
			{
				if (input[j] == '$')
					return (quote);
				j++;
			}
			quote = 0;
		}
		i++;
	}
	return (quote);
}

void	cmd_to_lower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}
