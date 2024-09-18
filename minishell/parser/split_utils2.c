/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darikan <darikan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:10 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 19:13:07 by darikan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_split *split)
{
	if (split->meta == HEREDOC || split->meta == GREAT
		|| split->meta == GREATER || split->meta == LESS)
		return (1);
	return (0);
}

void	line_list_file_right(t_split *tmp, t_line *line, int type)
{
	append_fd(&(line->right), create_new_fd(tmp->node, type));
}

void	line_list_file_left(t_split *tmp, t_line *line, int type)
{
	append_fd(&(line->left), create_new_fd(tmp->node, type));
}

void	line_list_arg(t_split *tmp, t_line *line)
{
	add_arg(&(line->arg), tmp->node);
}

void	lexer(t_mini *mini)
{
	adding_space(mini, '>');
	adding_space(mini, '<');
	adding_space(mini, '|');
}
