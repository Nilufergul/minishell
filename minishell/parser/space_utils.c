/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:13 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 19:29:18 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
