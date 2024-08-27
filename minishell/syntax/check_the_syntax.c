#include "../minishell.h"

int	redirect_check(char *input)
{
	if (mixed_redir(input) != 0 || mixed_redir_two(input) != 0 || mixed_redir_three(input) != 0 || mixed_redir_four(input) != 0)
		return (1);
	if (redir_plus_pipe(input) != 0 || redir_plus_pipe_two(input) || last_arg_is_redir(input))
		return (1);
	return (0);
}

int	all_closed_quotes(const char *input)
{
	int	i;
	int quote;

	quote = 0;
	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && quote == 0)
			quote = input[i];
		else if ((quote == input[i]) && (quote != 0))
			quote = 0;
	}
	return (quote);
}

int	backslash_check(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if(input[i] == '\\' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	semicolon_check(char *input)
{
	int	i;
	int	quote;
	
	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = pass_the_quotes(input[i], quote);
		if (input[i] == ';' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_the_syntax(t_mini *mini)
{
	if (all_closed_quotes(mini->line) != 0)
		return (print_syntax_error_quote());
	if (is_pipe_first(mini->line) != 0 || is_pipe_last(mini->line) != 0 || double_pipe(mini->line) != 0)
		return (print_syntax_error_pipe());
	if (backslash_check(mini->line) == 1 || semicolon_check(mini->line) == 1)
		return (print_unexpected_char_error());
	if (redirect_check(mini->line) != 0)
		return (print_syntax_error_redir());
	printf("%s\n", mini->line); // silincek deneme printfi
	return (1);
}


