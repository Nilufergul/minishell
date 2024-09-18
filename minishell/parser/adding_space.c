/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:31 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 18:17:25 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_check_meta(char *str, int *i)
{
	char	quote;

	if (str[*i] && (str[*i] == '\"' || str[*i] == '\''))
	{
		quote = str[*i];
		(*i)++;
		while (str[*i] && str[*i] != quote)
		{
			(*i)++;
		}
	}
}

void	shift_and_insert(char *str, int *len, int pos)
{
	int	j;

	j = *len;
	while (j > pos)
	{
		str[j + 1] = str[j];
		j--;
	}
	str[pos + 1] = ' ';
	(*len)++;
	str[*len] = '\0';
}

int	count_meta_character(char *str, char s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] == s && str[i + 1] != ' ')
			|| (str[i] == s && str[i - 1] != ' '))
			count++;
		i++;
	}
	i += count;
	return (i);
}

void	shift_and_insert_spaces(char *line, int *len, int *i, char s)
{
	if ((line[*i] == s && (line[*i - 1] != ' ' && line[*i - 1] != s)))
		shift_and_insert(line, len, *i - 1);
	if (line[*i] == s && (line[*i + 1] != ' ' && line[*i + 1] != s))
		shift_and_insert(line, len, *i);
}

char	*create_new_line_with_space(t_mini *mini, int len, int count)
{
	char	*new_line;

	new_line = malloc(sizeof(char) * (len + count + 1));
	if (!new_line)
		return (NULL);
	ft_strlcpy(new_line, mini->line, len + count + 1);
	return (new_line);
}

void	adding_space(t_mini *mini, char s)
{
	int		i;
	int		len;
	int		count;
	char	*new_line;

	i = 0;
	len = ft_strlen(mini->line);
	count = count_meta_character(mini->line, s);
	new_line = create_new_line_with_space(mini, len, count);
	if (!new_line)
		return ;
	while (new_line[i] != '\0')
	{
		quote_check_meta(new_line, &i);
		shift_and_insert_spaces(new_line, &len, &i, s);
		i++;
	}
	free(mini->line);
	mini->line = new_line;
}


