/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:35:33 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:35:34 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pass_the_quotes(char c, int quote)
{
	if ((c == '\'' || c == '\"') && quote == 0)
		quote = c;
	else if ((quote == c) && quote != 0)
		quote = 0;
	return (quote);
}

int	pass_the_spaces(char *input, int i)
{
	while (input[i] == ' ')
		i++;
	return (i);
}
