/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:03:58 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 19:28:52 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	get_qm(char **new_str, t_exit_status *exit_t)
{
	char	*res;
	char	*temp;

	res = ft_itoa(exit_t->exit_code);
	temp = ft_strjoin(*new_str, res);
	free(*new_str);
	*new_str = temp;
	free(res);
}

char	*remove_quotes_two(t_split **split, t_mini **mini, \
	t_exit_status *exit_t)
{
	int		nums[2];
	char	*new_str;
	char	*str;

	nums[0] = 0;
	nums[1] = 1;
	new_str = ft_calloc(1, 1);
	str = (*split)->node;
	while (str[nums[0]])
	{
		if (str[nums[0]] == '$' && str[nums[0] + 1] && str[nums[0] + 1] == '?')
		{
			get_qm(&new_str, exit_t);
			nums[0]++;
		}
		else
			nums[0] = update_index(str, &new_str, nums, mini);
		nums[0]++;
	}
	free(str);
	return (new_str);
}

int	update_index(char *str, char **new_str, int nums[2], t_mini **mini)
{
	char	*temp;

	if (str[nums[0]] == '$' && str[nums[0] + 1] && \
		(ft_isalnum(str[nums[0] + 1]) || str[nums[0] + 1] == '_'))
		nums[0] = get_dollar(str, nums[0] + 1, mini, new_str);
	else if (str[nums[0]] == '\'' && nums[1] == 1)
		nums[0] = get_single_quote(str, nums[0] + 1, new_str);
	else if (str[nums[0]] == '\"')
		nums[1] ^= 1;
	else
	{
		temp = ft_calloc(ft_strlen(*new_str) + 2, 1);
		ft_strcpy(temp, *new_str);
		temp[ft_strlen(*new_str)] = str[nums[0]];
		temp[ft_strlen(*new_str) + 1] = 0;
		free(*new_str);
		*new_str = ft_strdup(temp);
		free(temp);
	}
	return (nums[0]);
}
