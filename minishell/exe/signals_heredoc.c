/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darikan <darikan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:19 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 19:25:35 by darikan          ###   ########.fr       */
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
