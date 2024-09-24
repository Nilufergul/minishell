/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:06:11 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/22 16:28:43 by ngulcift         ###   ########.fr       */
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

int	handle_path(char **path, char ***env)
{
	char	*oldpwd;
	int		i;

	oldpwd = NULL;
	i = 0;
	if (ft_strcmp(*path, "-") == 0)
	{
		while ((*env)[i] != NULL)
		{
			if (ft_strncmp((*env)[i], "OLDPWD=", 7) == 0)
			{
				oldpwd = &(*env)[i][7];
				break ;
			}
			i++;
		}
		if (!oldpwd)
		{
			printf("cd: OLDPWD not set\n");
			return (1);
		}
		*path = oldpwd;
		printf("%s\n", *path);
	}
	return (0);
}

char	*get_home_path(char ***env)
{
	char	*home;
	int		i;

	home = NULL;
	i = 0;
	while ((*env)[i] != NULL)
	{
		if (ft_strncmp((*env)[i], "HOME=", 5) == 0)
		{
			home = &(*env)[i][5];
			break ;
		}
		i++;
	}
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
		path = get_home_path(line->env);
	if (!path || handle_path(&path, line->env) || change_directory(path))
		return (1);
	update_dirs(line->env, current_dir);
	return (0);
}
