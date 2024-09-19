/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 20:16:54 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:16:56 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	w_exit_status(int status)
{
	return ((status >> 8) & 0x000000ff);
}

void	run_exec(char *command, char **env, t_exit_status *exit_code_line)
{
	char	*path;
	char	**commands;

	commands = ft_split(command, ' ');
	path = get_command_path(env, commands[0]);
	if (!path)
		path = commands[0];
	if (access(path, X_OK) == -1)
	{
		ft_putstr_fd(commands[0], 2);
		ft_putendl_fd(": There is no such command", 2);
		exit(127);
	}
	execve(path, commands, env);
	exit_code_line->exit_code = 1;
	exit(exit_code_line->exit_code);
}

char	*get_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH", 5))
		{
			path = ft_strdup(env[i]);
			break ;
		}
		i++;
	}
	return (path);
}

char	*get_command_path(char **env, char *command)
{
	int		i;
	char	*path;
	char	**paths;
	char	*address;

	i = 0;
	path = get_path(env);
	paths = ft_split(path, ':');
	free(path);
	path = 0;
	command = ft_strjoin("/", command);
	while (paths[i])
	{
		if (access(command, F_OK | X_OK) == 0)
			path = ft_strdup(command);
		address = ft_strjoin(paths[i], command);
		if (access(address, F_OK | X_OK) == 0)
			path = address;
		i++;
	}
	free(command);
	free(address);
	return (path);
}
