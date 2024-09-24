/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:05:07 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 15:27:13 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	merged_redir(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '<' && quote == 0)
		{
			if (input[i + 1])
				i++;
			i = jump_spaces(input, i);
			if (input[i] == '>')
				return (1);
		}
		i++;
	}
	return (0);
}

int	merged_redir_three(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '<' && input[i + 1] == '<' && quote == 0)
		{
			if (input[i + 2])
				i += 2;
			else
				return (0);
			i = jump_spaces(input, i);
			if (input[i] == '>' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	merged_redir_four(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '>' && input[i + 1] && input[i + 1] == '>' \
			&& quote == 0)
		{
			if (input[i + 2])
				i += 2;
			else
				return (0);
			i = jump_spaces(input, i);
			if (input[i] == '>' || input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	merged_redir_two(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '>' && quote == 0)
		{
			if (input[i + 1])
				i++;
			i = jump_spaces(input, i);
			if (input[i] == '<')
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_last_arg_redirect(char *input)
{
	int		i;
	int		c;
	char	red;

	i = 0;
	while (input[i])
	{
		quote_check_meta(input, &i);
		if (input[i] == '<' || input[i] == '>')
		{
			red = input[i];
			c = jump_spaces(input, i) - i;
			if ((c != 0 && ((input[i + c] && input[i + c] == red) \
				|| input[i + c] == '\0')))
				return (1);
			if (input[i] == '\0')
				return (1);
			if (input[i + c] && input[i + c] == red && input[i + 1] == '\0')
				return (1);
		}
		i++;
	}
	return (0);
}
