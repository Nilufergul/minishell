/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:06:48 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/23 21:20:27 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_copy(char *result, char **arr)
{
	char	*cur;
	char	*temp;
	int		i;

	cur = result;
	i = 0;
	while (arr != NULL && arr[i] != NULL)
	{
		temp = ft_strjoin(cur, " ");
		free(cur);
		cur = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
	return (cur);
}

char	*merge_echo(char **arr)
{
	char	*cur;
	char	*temp;
	int		i;

	if (!arr || !arr[0])
		return (0);
	cur = ft_strdup(arr[0]);
	i = 1;
	while (arr != NULL && arr[i] != NULL)
	{
		temp = ft_strjoin(cur, " ");
		free(cur);
		cur = ft_strjoin(temp, arr[i]);
		free(temp);
		i++;
	}
	return (cur);
}

void	runcommanderror(char *command, int i)
{
	if (i == 1)
	{
		write(1,"minishell: ",11);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	else if (i == 0)
	{
		write(1,"minishell: ",11);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": is a directory: ", 2);
		exit(126);
	}
	else if (i == 2)
	{
		write(1,"minishell: ",11);
		ft_putstr_fd(command, 2);
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
}

