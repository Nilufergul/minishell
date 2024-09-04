/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 00:03:10 by selmandemir       #+#    #+#             */
/*   Updated: 2024/09/04 02:00:03 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_pipe_things(t_pipe_info *pipe_info)
{
	clean_pipes(pipe_info);
	free(pipe_info->pid);
	free_all_pipes(pipe_info->pipes, pipe_info->len - 1);
	free(pipe_info->pipes);
	free(pipe_info);
}

char	**copy_env(char **env)
{
	int		rows;
	char	**new;

	rows = 0;
	while (env[rows])
		rows++;
	new = (char **)malloc((rows + 1) * sizeof(char *));
	if (new == NULL)
		exit(1);
	new[rows] = NULL;
	rows--;
	while (rows >= 0)
	{
		new[rows] = ft_strdup(env[rows]);
		if (new[rows] == NULL)
			exit(1);
		rows--;
	}
	return (new);
}

void	make_pipe(t_line *command)
{
	t_pipe_info	*pipe_info;

	if (struct_len(command) == 1 && built_in2(command) == 1)
		return ;
	pipe_info = malloc(sizeof(t_pipe_info));
	if (pipe_info == NULL)
		exit(1);
	pipe_info->len = struct_len(command);
	pipe_info->pid = malloc(sizeof(pid_t) * pipe_info->len);
	if (pipe_info->pid == NULL)
		exit(1);
	pipe_info->pipes = fill_pipes(pipe_info->len);
	create_processes(command, pipe_info);
	free_pipe_things(pipe_info);
}



int main(int argc, char **argv, char **envp)
{
	if (argc == 3 && argv[0][0] == 5)
		printf(" asf");
	char **env = copy_env(envp);
	t_line *komut1;
	//t_line *komut2;
	//t_line *komut3;
	//t_line *komut4;
	//t_line *komut5;

	komut1 = create_new_line("echo", env);
	//komut2 = create_new_line("echo", env);
	//komut3 = create_new_line("env", env);
	//komut4 = create_new_line("unset", env);
	//komut5 = create_new_line("env", env);



	//append_line(&komut1, komut2);
	//append_line(&komut1, komut3);
	//append_line(&komut1, komut4);
	//append_line(&komut1, komut5);

	//add_arg(&(komut1->arg), "selman=5");
	add_arg(&(komut1->arg), "a");
	add_arg(&(komut1->arg), "b");
	add_arg(&(komut1->arg), "c");



	//add_arg(&(komut2->arg), "yazi");
	//add_arg(&(komut3->arg), "ppppp");
	//add_arg(&(komut4->arg), "selman");
	//add_arg(&(komut5->arg), "");


	append_fd(&(komut1->right), create_new_fd("d", 4));
	append_fd(&(komut1->right), create_new_fd("f", 4));
	//append_fd(&(komut1->right), create_new_fd("d3", 4));

	//append_fd(&(komut1->left), create_new_fd("f", 5));
	//append_fd(&(komut1->left), create_new_fd("b", 5));
	//append_fd(&(komut1->left), create_new_fd("dur1", 1));
	//append_fd(&(komut1->left), create_new_fd("dur2", 1));







	printf("");
	make_pipe(komut1);
	//make_pipe(komut2);
	//make_pipe(komut3);
	//make_pipe(komut4);
	//make_pipe(komut5);



	return 0;
}


