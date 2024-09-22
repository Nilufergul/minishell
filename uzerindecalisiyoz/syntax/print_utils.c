/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:04:57 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 12:37:21 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	syntax_error_quote(void)
{
	printf("Syntax error. Unclosed quote.\n");
	return (0);
}

int	syntax_error_pipe(void)
{
	printf("Syntax error. Invalid pipe using.\n");
	return (0);
}

int	not_allowed_char_error(void)
{
	printf("Unexpected character using.\n");
	return (0);
}

int	syntax_error_redir(void)
{
	printf("Mixed redirect using.\n");
	return (0);
}
