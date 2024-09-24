/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_exe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:06:48 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 19:26:35 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_copy(char *result, char **arr)
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
	return (ft_split(cur, ' '));
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
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(command, 2);
	if (i == 1)
	{
		ft_putendl_fd(": No such file or directory", 2);
		exit(127);
	}
	else if (i == 0)
	{
		ft_putendl_fd(": is a directory: ", 2);
		exit(126);
	}
	else if (i == 2)
	{
		ft_putendl_fd(": Permission denied", 2);
		exit(126);
	}
	else if (i == 3)
	{
		ft_putendl_fd(": There is no such command", 2);
		exit(127);
	}
}

int	check_file(t_line *command, int flag)
{
	if (flag && !ft_strncmp(command->cmd, "./", 2) && \
		is_directory(command->cmd))
		runcommanderror(command->cmd, 0);
	if (flag && !ft_strncmp(command->cmd, "./", 2) && \
		!is_file(command->cmd))
		runcommanderror(command->cmd, 1);
	if (flag && !ft_strncmp(command->cmd, "./", 2) && \
		access(command->cmd, X_OK) == -1)
		runcommanderror(command->cmd, 2);
	if (!flag && is_directory(command->cmd))
		runcommanderror(command->cmd, 3);
	if (!flag && !is_file(command->cmd))
		runcommanderror(command->cmd, 3);
	if (!flag && ft_strncmp(command->cmd, "./", 2) && command->cmd[0] != '/')
		runcommanderror(command->cmd, 3);
	if (!flag && access(command->cmd, X_OK) == -1)
		runcommanderror(command->cmd, 3);
	return (1);
}
