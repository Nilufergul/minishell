/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:37 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 12:03:39 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_res(char *var, t_mini **mini)
{
	char	**env;
	char	**line;
	int		i;
	char	*res;

	env = (*mini)->env;
	res = 0;
	i = 0;
	while (env[i])
	{
		line = ft_split(env[i], '=');
		if (ft_strcmp(var, line[0]) == 0)
		{
			res = ft_strdup(line[1]);
			free(line[0]);
			free(line[1]);
			free(line);
			return (res);
		}
		free(line[0]);
		free(line[1]);
		free(line);
		i++;
	}
	return (res);
}

int	get_dollar(char *str, int i, t_mini **mini, char **new_str)
{
	int		j;
	char	*var;
	char	*res;
	char	*temp;

	j = get_var_end(str, i);
	if (i == j)
		return (i);
	var = extract_var(str, i, j);
	if (!var)
		return (i);
	res = get_res(var, mini);
	free(var);
	if (!res)
		return (j - 1);
	temp = ft_strjoin(*new_str, res);
	free(*new_str);
	*new_str = temp;
	free(res);
	return (j - 1);
}

int	get_var_end(char *str, int i)
{
	int	j;

	j = i;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	return (j);
}

char	*extract_var(char *str, int i, int j)
{
	char	*var;
	int		k;

	k = 0;
	var = (char *)malloc((j - i + 2) * sizeof(char));
	if (!var)
		return (NULL);
	while (k < j - i)
	{
		var[k] = str[i + k];
		k += 1;
	}
	var[k] = 0;
	return (var);
}

int	get_single_quote(char *str, int i, char **new_str)
{
	int		j;
	int		k;
	char	*res;
	char	*temp;

	j = i;
	while (str[j] && str[j] != '\'')
		j++;
	if (i == j)
		return (i);
	res = malloc(j - i + 2);
	if (!res)
		return (i);
	k = 0;
	while (k < j - i)
	{
		res[k] = str[i + k];
		k += 1;
	}
	res[k] = 0;
	temp = ft_strjoin(*new_str, res);
	free(*new_str);
	*new_str = temp;
	free(res);
	return (j);
}
