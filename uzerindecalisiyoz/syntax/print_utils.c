/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:57 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 17:21:15 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error_quote(void)
{
	write(1, "minishell: ", 11);
	printf("Syntax error. Unclosed quote.\n");
	return (0);
}

int	syntax_error_pipe(void)
{
	write(1, "minishell: ", 11);
	printf("Syntax error. Invalid pipe using.\n");
	return (0);
}

int	not_allowed_char_error(void)
{
	write(1, "minishell: ", 11);
	printf("Unexpected character using.\n");
	return (0);
}

int	syntax_error_redir(void)
{
	write(1, "minishell: ", 11);
	printf("Mixed redirect using.\n");
	return (0);
}
