/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:17:25 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:17:26 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	heredoc_ctrld(char *line)
{
	if (!line)
	{
		free(line);
		return (1);
	}
	return (0);
}

void	heredoc_ctrlc(int signum)
{
	if (signum == SIGINT)
	{
		g_catch_ctrlc = 1;
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	init_signals_heredoc(void)
{
	signal(SIGINT, heredoc_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	return (1);
}
