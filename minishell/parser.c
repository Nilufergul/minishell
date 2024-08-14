/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:31:55 by rcan              #+#    #+#             */
/*   Updated: 2024/08/13 20:29:24 by rcan             ###   ########.fr       */
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
int main()
{

	t_mini *minik;

	minik = (t_mini *)malloc(sizeof(t_mini));
	minik->line = malloc(sizeof(char*));
	minik->line[0] = (char *)malloc(sizeof(char)*8); 
	if(minik == NULL)
		return 0;
	minik->line[0] = "\"'abc'\"";
	printf("%s\n",minik->line[0]);
	int i = quote_checker_1(minik);
	printf("A\n");
	printf("%d",i);
}