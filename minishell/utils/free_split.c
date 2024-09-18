/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:35:45 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:35:46 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_the_split(t_split *split)
{
	t_split	*tmp;

	while (split)
	{
		tmp = split;
		split = split->next;
		free(tmp->node);
		free(tmp);
	}
	free(split);
}

void	free_the_minis(t_mini *mini)
{
	free(mini->line);
}
