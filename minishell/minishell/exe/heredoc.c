/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:55 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:36:56 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	handle_input(int pipefd[2], char *target)
{
	char	*input;

	while (1)
	{
		input = readline("> ");
		if (!input)
			exit(EXIT_FAILURE);
		if (g_catch_ctrlc == 1)
		{
			g_catch_ctrlc = 0;
			free(input);
			break ;
		}
		if (heredoc_ctrld(input) || ft_strcmp(input, target) == 0)
		{
			free(input);
			break ;
		}
		if (write(pipefd[1], input, ft_strlen(input)) == -1
			|| write(pipefd[1], "\n", 1) == -1)
			exit(EXIT_FAILURE);
		free(input);
	}
	return (pipefd[0]);
}

int	heredoc(char *target)
{
	int		pipefd[2];

	init_signals_heredoc();
	if (pipe(pipefd) == -1)
		exit(EXIT_FAILURE);
	return (handle_input(pipefd, target));
}
