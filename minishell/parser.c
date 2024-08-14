/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 19:31:55 by rcan              #+#    #+#             */
/*   Updated: 2024/08/14 20:18:40 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

int quote_checker_1(t_mini *mini)
{
	int i;
	char quote;
	
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
/*
void meta_sep(t_mini *mini) // |cat<a   -> | cat < a  çalışmıyo0000
{
	char *str;
	int i;
	int count;

	str = mini->line[0];
	
	i = 0;
	count = 0;
	while(str[i])
	{
		if(mini->line[0][i] == '|' || mini->line[0][i] == '>' || mini->line[0][i] == '<' ||
		mini->line[0][i] == '>>' || mini->line[0][i] == '<<')
		{
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
		}
		else if(mini->line[0][i] == ' ')
		{
			space_delete(mini->line[0],i);		
		}
		i++;
	}
}*/

void pipex_check(t_mini *mini)
{
	char *str;
	int i;

	i = 0;
	str = mini->line[0];
	while(str[i])
	{
		if(str[i] == '|')
		{
			if(str[i+1] != '\0' && str[i+1] == '|')
				printf("error\n");
				//error
		}
		i++;
	}
}


void space(t_mini *mini)
{
	char *str;
	char quote;
	int quote_on;
	int i;

	str = mini->line[0];
	quote_on = 0;
	i = 0;
	while(str[i])
	{
		if(mini->line[0][i] == '\"' || mini->line[0][i] == '\'')
		{
			quote = mini->line[0][i];
			i++;
			while(mini->line[0][i] && mini->line[0][i] != quote)
			{
				i++;
			}
		}
		else if(mini->line[0][i] == ' ')
		{
			printf("%c\n",mini->line[0][i]);
			space_delete(mini->line[0],i);		
		}
		i++;
	}
}

void space_delete(char *line, int i)
{
	int j;
	int k;
	int count;
	
	count = 0;
	j = i;
	k = 0;
	if(line[i+1] != ' ')
		return;
	while(line[j] && line[j] == ' ')
	{
		count++;
		j++;
	}
	count--;
	while(count-- != 0)
	{
		k = j--;
		while(line[k] != '\0')
		{
			line[k-1] = line[k];
			k++;
		}
		line[k-1] = '\0';
	}
}

int main()
{
	char a[] = "|ab|c   ashjk    ";
	t_mini *minik;

	minik = (t_mini *)malloc(sizeof(t_mini));
	minik->line = malloc(sizeof(char*));
	minik->line[0] = malloc(sizeof(char)*20); 
	if(minik == NULL)
		return 0;
	minik->line[0] = a;
	pipex_check(minik);
}