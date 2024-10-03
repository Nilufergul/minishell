/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removing_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:07 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 19:29:07 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	expander(t_split *split, t_mini *mini, t_exit_status *exit_t)
{
	while (split)
	{
		if (split->meta == DOLLAR)
			split->node = remove_quotes_two(&split, &mini, exit_t);
		else if (split->meta == HEREDOC)
			split = split->next;
		split = split->next;
	}
}

void	remove_quotes(t_split *split)
{
	while (split)
	{
		if (split->meta != DOLLAR)
			quotes(split);
		else
			split->meta = EXCEPT;
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

void	procedure2(t_split *split, t_mini *mini, t_exit_status *exit_t)
{
	expander(split, mini, exit_t);
	remove_quotes(split);
	free_the_minis(mini);
}
