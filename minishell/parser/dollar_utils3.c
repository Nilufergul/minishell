/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:18:26 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:18:28 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_double_quote(char *str, int i, char **new_str, t_mini **mini)
{
	char	*temp;

	while (str[i] && str[i] != '\"')
	{
		if (str[i] == '$' && str[i + 1]
			&& (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
			i = get_dollar(str, i + 1, mini, new_str);
		else
		{
			temp = ft_calloc(ft_strlen(*new_str) + 2, 1);
			ft_strcpy(temp, *new_str);
			temp[ft_strlen(*new_str)] = str[i];
			temp[ft_strlen(*new_str) + 1] = 0;
			free(*new_str);
			*new_str = temp;
		}
		i++;
	}
	return (i);
}

char	*remove_quotes_two(t_split **split, t_mini **mini)
{
	int		i;
	char	*new_str;
	char	*str;

	i = 0;
	new_str = malloc(1);
	new_str[0] = 0;
	str = (*split)->node;
	while (str[i])
	{
		i = update_i(str, &new_str, i, mini);
		i++;
	}
	free(str);
	return (new_str);
}

int	update_i(char *str, char **new_str, int i, t_mini **mini)
{
	char	*temp;

	if (str[i] == '$' && str[i + 1] && \
		(ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		i = get_dollar(str, i + 1, mini, new_str);
	else if (str[i] == '\'')
		i = get_single_quote(str, i + 1, new_str);
	else if (str[i] == '\"')
		i = get_double_quote(str, i + 1, new_str, mini);
	else
	{
		temp = ft_calloc(ft_strlen(*new_str) + 2, 1);
		ft_strcpy(temp, *new_str);
		temp[ft_strlen(*new_str)] = str[i];
		temp[ft_strlen(*new_str) + 1] = 0;
		free(*new_str);
		*new_str = ft_strdup(temp);
		free(temp);
	}
	return (i);
}
