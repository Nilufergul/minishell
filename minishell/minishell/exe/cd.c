/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:36:37 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:48:28 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_dirs(char ***env, char *current_dir)
{
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	create_update(env, "OLDPWD", current_dir);
	create_update(env, "PWD", new_pwd);
	free(new_pwd);
}

int	handle_path(char **path, char *prev_dir)
{
	if (ft_strcmp(*path, "-") == 0)
	{
		if (prev_dir[0] == '\0')
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		*path = prev_dir;
		printf("%s\n", *path);
	}
	return (0);
}

char	*get_home_path(void)
{
	char	*home;

	home = getenv("HOME");
	if (!home)
		printf("cd: HOME environment variable not set\n");
	return (home);
}

int	change_directory(char *path)
{
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	return (0);
}

int	ft_cd(t_line *line)
{
	char		prev_dir[1024];
	char		current_dir[1024];
	char		*path;

	if (line->arg && line->arg[0])
	{
		path = line->arg[0];
	}
	else
	{
		path = NULL;
	}
	if (!getcwd(current_dir, sizeof(current_dir)))
	{
		perror("getcwd");
		return (1);
	}
	if (!path || ft_strcmp(path, "~") == 0)
		path = get_home_path();
	if (!path || handle_path(&path, prev_dir) || change_directory(path))
		return (1);
	update_dirs(line->env, current_dir);
	ft_strcpy(prev_dir, current_dir);
	return (0);
}
