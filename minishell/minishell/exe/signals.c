/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:37:21 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 22:19:29 by rcan             ###   ########.fr       */
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
	signal(CTRL_SLASH, ctrl_c);
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
