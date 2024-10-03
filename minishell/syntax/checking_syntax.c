/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checking_syntax.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:46 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 12:04:49 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_redirect(char *input)
{
	if (merged_redir(input) != 0 || merged_redir_two(input) != 0
		|| merged_redir_three(input) != 0 || merged_redir_four(input) != 0)
		return (1);
	if (redirect_and_pipe(input) != 0 || redirect_and_pipe_two(input)
		|| check_last_arg_redirect(input))
		return (1);
	return (0);
}

int	check_quotes_closed(const char *input)
{
	int	i;
	int	quote;

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

int	check_backslash(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '\\' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_semicolon(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == ';' && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	checking_syntax(t_mini *mini)
{
	if (check_quotes_closed(mini->line) != 0)
		return (syntax_error_quote());
	if (check_pipe_first(mini->line) != 0 || check_pipe_last(mini->line) != 0
		|| double_pipe(mini->line) != 0)
		return (syntax_error_pipe());
	if (check_backslash(mini->line) == 1 || check_semicolon(mini->line) == 1)
		return (not_allowed_char_error());
	if (check_redirect(mini->line) != 0)
		return (syntax_error_redir());
	return (1);
}
