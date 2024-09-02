#include "../minishell.h"

int	mixed_redir(char *input)
{
	int	i;
	int	quote;
	
	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == '<' && quote == 0)
		{
			i++;
			i = pass_the_spaces(input, i);
			if (input[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	mixed_redir_three(char *input)
{
	int	i;
	int	quote;
	
	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
		{
			i += 2;
			i = pass_the_spaces(input, i);
			if (input[i] == '>' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	mixed_redir_four(char *input)
{
	int	i;
	int	quote;
	
	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == '>' && input[i + 1] == '>' && quote == 0)
		{
			i += 2;
			i = pass_the_spaces(input, i);
			if (input[i] == '>' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	mixed_redir_two(char *input)
{
	int	i;
	int	quote;
	
	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == '>' && quote == 0)
		{
			i++;
			i = pass_the_spaces(input, i);
			if (input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	last_arg_is_redir(char *input)
{
	int	i;
	char red;
	

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			red = input[i];
			i += 1;
			i = pass_the_spaces(input, i);
			if (input[i] == red || input[i] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
