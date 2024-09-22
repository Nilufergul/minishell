/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:07:41 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/21 14:41:12 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int signum)
{
	if (signum == CTRL_C)
	{
		g_catch_ctrlc = 1;
		printf("\n");
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_child(int signum)
{
	if (signum == CTRL_C)
		printf("\n");
}

int	init_signals(int mode)
{
	if (mode == 0)
		signal(CTRL_C, ctrl_c);
	else if (mode == 1)
		signal(CTRL_C, handle_child);
	signal(CTRL_SLASH, SIG_IGN);
	return (1);
}

void	ctrl_d(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		free(line);
		exit(0);
	}
}
