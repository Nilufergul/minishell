/* **** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:08:31 by muhademi          #+#    #+#             */
/*   Updated: 2024/09/02 18:20:21 by muhademi         ###   ########.fr       */
/*                                                                            */
/* **** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
#include <readline/readline.h>
#include <errno.h>

typedef enum type {
	EXEC = 0,
	HEREDOC = 1,
	PIPE = 2,
	GREAT = 3,
	GREATER = 4,
	LESS = 5,
} type;

typedef enum file_des {
	STDINN = 0,
	STDOUT = 1,
	STDERR = 2
} file_des;

typedef struct s_ty
{
	int type;
	struct s_ty *next;
}				t_ty;

typedef struct s_arg
{
	int *arg;
	struct s_arg *next;
}				t_arg;

typedef struct s_split
{
	int meta;
	char *node;
	struct s_split *next;
}				t_split;

typedef struct s_mini
{
	char **env;
	char *line;
} t_mini;

typedef struct s_fd
{
	int fd;
	int	type;
	char *name;
	struct s_fd *next;
}				t_fd;

typedef struct  s_line
{
	char	*cmd;
	char	**arg;
	char 	**env;
	struct  s_fd    *right;
	struct  s_fd    *left;
	struct  s_line  *next;
}				t_line;

typedef struct s_pipe_info
{
    int **pipes;
    pid_t *pid;
    int len;
} t_pipe_info;


void	run_exec(char *command, char **env);
char	*get_path(char **env);
char	*get_command_path(char **env, char *command);

int struct_len(t_line *head);
t_line *create_new_line(char *cmd_str, char **env);
t_fd *create_new_fd(char *name, int type);
t_ty *create_new_ty(int type);
void append_line(t_line **head, t_line *new_line);
void append_fd(t_fd **head, t_fd *new_fd);
void append_ty(t_ty **head, t_ty *new_ty);
int struct_len(t_line *head);
int add_arg(char ***arg, char *new_arg);

char	*get_copy(char *result, char **arr);
int fd_len(t_fd **head);
void clean_pipes(t_pipe_info *pipe_info);
void create_processes(t_line *command, t_pipe_info *pipe_info);
void run_child_process(t_line *command, t_pipe_info *pipe_info, int i);
void	pwd(void);
int ft_cd(char *path);
int	echo_main(char *s);
int	echo_index(char *s);
void	echo_incn(char c, int *n);
void	echo_case1(char c, int *expect, int *ret);
int	echo_case2(char c, int *expect, int *ret);
int	echo_case3(char c, int *expect, int *ret, int *n_count);

int heredoc(char *target);
int	open_lefts(t_fd *head);
int	built_in(t_line *command);
int	built_in2(t_line *command);
void	run_command_run(t_line *command);
int	**fill_pipes(int count);
void	close_all_pipes(int **pipes, int len);
void	free_all_pipes(int **pipes, int len);

void ft_export(char **args, char **env);
void ft_unset(char **args, char **env);
int	ft_environment(char **env);
void	ft_exit(char **args);
#endif
