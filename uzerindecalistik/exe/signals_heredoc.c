/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:07:36 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/21 14:41:26 by ngulcift         ###   ########.fr       */
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
	signal(CTRL_C, heredoc_ctrlc);
	signal(CTRL_SLASH, SIG_IGN);
	return (1);
}
