/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_exe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:14 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 17:36:15 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cases(t_split **tmp_spl, t_line **tmp2, int *flag_pipe)
{
	if ((*tmp_spl)->meta && (*tmp_spl)->meta == PIPE)
		*flag_pipe = 1;
	else if (*flag_pipe == 2 && !is_redir((*tmp_spl)))
	{
		(*tmp2)->cmd = ft_strdup((*tmp_spl)->node);
		*flag_pipe = 0;
	}
	else if ((*tmp_spl)->meta && ((*tmp_spl)->meta == GREAT
			|| (*tmp_spl)->meta == GREATER))
	{
		line_list_file_right((*tmp_spl)->next, (*tmp2), (*tmp_spl)->meta);
		(*tmp_spl) = (*tmp_spl)->next;
	}
	else if ((*tmp_spl)->meta && ((*tmp_spl)->meta == LESS
			|| (*tmp_spl)->meta == HEREDOC))
	{
		line_list_file_left((*tmp_spl)->next, (*tmp2), (*tmp_spl)->meta);
		(*tmp_spl) = (*tmp_spl)->next;
	}
	else if ((*tmp_spl)->meta == EXCEPT && *flag_pipe == 0)
		line_list_arg((*tmp_spl), (*tmp2));
}

t_line	*split_for_exe(t_split *split, t_mini *mini)
{
	t_split	*tmp_spl;
	int		flag_pipe;
	t_line	*line;
	t_line	*tmp2;

	tmp_spl = split;
	flag_pipe = 1;
	line = NULL;
	tmp2 = line;
	while (tmp_spl)
	{
		if ((ft_strcmp(tmp_spl->node, "") == 0) && (tmp_spl->next != NULL))
			tmp_spl = tmp_spl->next;
		if (flag_pipe == 1)
		{
			tmp2 = create_new_line(&mini->env);
			append_line(&line, tmp2);
			flag_pipe = 2;
		}
		cases(&tmp_spl, &tmp2, &flag_pipe);
		tmp_spl = tmp_spl->next;
	}
	return (line);
}
