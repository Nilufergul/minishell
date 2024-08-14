/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:31:55 by rcan              #+#    #+#             */
/*   Updated: 2024/08/14 16:03:04 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int quote_checker_1(t_mini *mini)
{
	int i;
	char quote;
	printf("%s\n",mini->line[0]);
	i = 0;
	while(mini->line[0][i])
	{
		if(mini->line[0][i] == '\"' || mini->line[0][i] == '\'')
		{
			quote = mini->line[0][i];
			i++;
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
			if(mini->line[0][i] == '\0')
				return(0);
		}
		i++;
	}
	return(1);
}
