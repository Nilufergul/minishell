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
		(*i)++;
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

int	dollar_outside_quotes(const char *input)
{
	int	quote;
	int	i;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
		{
			i++;
			quote = input[i];
			while (input[i] && input[i] != quote)
			{
				i++;
			}
			quote = 0;
		}
		if(input[i] == '$')
			return (1);
		i++;
	}
	return (0);
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
