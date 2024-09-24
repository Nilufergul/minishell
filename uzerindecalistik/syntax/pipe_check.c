/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:53 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 12:52:28 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pipe_first(char *input)
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

int	check_pipe_last(char *input)
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
		quote = jump_quotes(input[i], quote);
		if ((input[i] == '|' && input[i + 1] == '|') && quote == 0)
			return (1);
		i++;
	}
	return (0);
}

int	redirect_and_pipe_two(char *input)
{
	int	i;
	int	quote;

	quote = 0;
	i = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (((input[i] == '>' && input[i + 1] && input[i + 1] == '>') || \
			(input[i] == '<' && input[i + 1] && input[i + 1] == '<')) \
			&& (quote == 0))
		{
			i += 2;
			i = jump_spaces(input, i);
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	redirect_and_pipe(char *input)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		quote = jump_quotes(input[i], quote);
		if (input[i] == '>' || input[i] == '<')
		{
			i++;
			i = jump_spaces(input, i);
			if (input[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}
