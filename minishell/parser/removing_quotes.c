/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:17 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 18:14:47 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_split *split, t_mini *mini)
{
	while (split)
	{
		if (split->meta == DOLLAR)
		{
			split->node = remove_quotes_two(&split, &mini);
			split->meta = EXCEPT;
		}
		else
			quotes(split);
		split = split->next;
	}
}

void	remove_quotes(t_split *split)
{
	while (split)
	{
		quotes(split);
		split = split->next;
	}
}

void	quotes(t_split *split)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	while (split->node[i])
	{
		if (split->node[i] == '\"' || split->node[i] == '\'')
		{
			quote = split->node[i];
			j = i;
			i++;
			while (split->node[i] && split->node[i] != quote)
				i++;
			if (split->node[i] == quote)
			{
				char_remove(split, j);
				char_remove(split, i - 1);
				i--;
			}
		}
		else
			i++;
	}
}

void	char_remove(t_split *split, int i)
{
	int	len;

	len = ft_strlen(split->node);
	if (i < 0 || i >= len)
		return ;
	ft_memmove(split->node + i, split->node + i + 1, len - i);
	split->node[len - 1] = '\0';
}

void	routine2(t_split *split, t_mini *mini, t_exit_status *exit_t)
{
	dollar_quest(split, exit_t);
	expander(split, mini);
	remove_quotes(split);
	free_the_minis(mini);
}
