#include "../minishell.h"

int	is_pipe_first(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == ' ')
	{
		i++;
	}
	if (input[i] == '|')
	{
		return (1);
	}
	return (0);
}

int	is_pipe_last(char *input)
{
	int	i;

	i = 0;
	while (input[i])
		i++;
	i--;
	while (input[i] == ' ')
		i--;
	if (input[i] == '|')
		return (1);
	return (0);
}

int	double_pipe(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if ((input[i] == '|' && input[i + 1] == '|') && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	redir_plus_pipe_two(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (((input[i] == '>' && input[i + 1] && input[i + 1] == '>')
				|| (input[i] == '<' && input[i + 1] &&  input[i + 1] == '<'))
			&& quote == 0)
		{
			i += 2;
			i = pass_the_spaces(input, i);
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	redir_plus_pipe(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == '>' || input[i] == '<')
		{
			i++;
			i = pass_the_spaces(input, i);
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}
