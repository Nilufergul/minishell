/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darikan <darikan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:35:24 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 20:11:52 by darikan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <dirent.h>
# include <string.h>
# include <errno.h>
# include <termios.h>
# include <sys/ioctl.h>
# include <term.h>
# include <curses.h>
# include <fcntl.h>
# include "libft/libft.h"

# define CTRL_C SIGINT
# define CTRL_SLASH SIGQUIT

volatile int	g_catch_ctrlc;

typedef enum s_type
{
	EXCEPT = 0,
	HEREDOC = 1,
	PIPE = 2,
	GREAT = 3,
	GREATER = 4,
	LESS = 5,
	DOLLAR = 6
}			t_type;

typedef enum s_file_des
{
	STDINN = 0,
	STDOUT = 1,
	STDERR = 2
}			t_file_des;

typedef struct s_ty
{
	int			type;
	struct s_ty	*next;
}				t_ty;

typedef struct s_arg
{
	int				*arg;
	struct s_arg	*next;
}				t_arg;

typedef struct s_split
{
	int				meta;
	char			*node;
	struct s_split	*next;
}				t_split;

typedef struct s_fd
{
	int			fd;
	int			type;
	char		*name;
	struct s_fd	*next;
}				t_fd;
typedef struct s_exit_status
{
	int	exit_code;
}				t_exit_status;

typedef struct s_line
{
	char			*cmd;
	char			**arg;
	char			***env;
	struct s_fd		*right;
	struct s_fd		*left;
	struct s_line	*next;
}				t_line;

typedef struct s_mini
{
	char	**env;
	char	*line;
}				t_mini;

typedef struct s_pipe_info
{
	int		**pipes;
	pid_t	*pid;
	int		len;
	int		input;
	int		output;
}				t_pipe_info;

//minishell.c
t_mini			*init_mini(t_mini *mini, char **environ);
void			ft_env(t_mini *mini, char **environ);
void			running_shell(t_mini *mini, t_exit_status *exit);
void			routine(t_mini *mini, t_exit_status *exit_t);

//cd
static void		update_dirs(char ***env, char *current_dir);
static int		handle_path(char **path, char *prev_dir);
static char		*get_home_path(void);
static int		change_directory(char *path);
int				ft_cd(t_line *line);

//export
int				is_valid(const char *str);
int				print_error(const char *arg);
int				print_export(char **env);
int				handle_export_argument(t_line *line, const char *arg);
int				ft_export(t_line *line);

//export_helper
void			*ft_realloc(void *ptr, size_t current_size, size_t new_size);
void			add_env_variable(char ***env, int i, const char *name, \
					const char *value);
void			update_env_variable(char **env, int i, \
						const char *name, const char *value);
void			create_update(char ***env, const char *name, const char *value);
long long int	ft_longlong(const char *str);

//echo_main
int				echo_main(char *s);

//echo_helper
void			echo_case1(char c, int *expect, int *ret);
int				echo_case2(char c, int *expect, int *ret);
int				echo_case3(char c, int *expect, int *ret);
int				echo_index(char *s);

//env
int				ft_environment(char **env);

//exit
void			print_error_exit(const char *arg, const char *msg, int code);
static int		check_argument(const char *arg);
static int		valid_value(char *arg);
static void		exit_handling(char **args, int i, \
				t_exit_status *exit_code_line);
void			ft_exit(t_line *line, t_exit_status *exit_code_line);

//go_exe
char			*get_copy(char *result, char **arr);
char			*merge_echo(char **arr);

//heredoc
int				handle_input(int pipefd[2], char *target);
int				heredoc(char *target);

//make_pipe
void			free_pipe_things(t_pipe_info *pipe_info, \
				t_exit_status *exit_code_line);
void			make_pipe(t_line *command, \
				t_exit_status *exit_code_line);
int				built_in2(t_line *command, \
				t_exit_status *exit_code_line);
void			clean_pipes(t_pipe_info *pipe_info, \
				t_exit_status *exit_code_line);
void			routine3(t_line *command, t_split *split, \
				t_exit_status *exit_t);

//pipex
int				w_exit_status(int status);
void			run_exec(char *command, char **env, \
				t_exit_status *exit_code_line);
char			*get_path(char **env);
char			*get_command_path(char **env, char *command);

//pipex2
void			close_all_pipes(int **pipes, int len);
void			free_all_pipes(int **pipes, int len);
int				handle_right_fd(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit);
int				handle_left_fd(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit);
int				get_fds(t_line *command, t_pipe_info *pipe_info, \
				t_exit_status *exit);

//pipex3
int				open_rights(t_fd *head);
int				open_lefts(t_fd *head);
int				built_in(t_line *command, t_exit_status *exit_code_line);
int				**fill_pipes(int count);

//pipex4
void			create_processes(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit_code_line);
void			handle_fork(t_line *command, t_pipe_info *pipe_info, \
				int i, t_exit_status *exit_code_line);
void			run_child_process(t_line *command, t_pipe_info *pipe_info, \
				int i, t_exit_status *exit_code_line);

//pwd
int				pwd(void);

//signals_heredoc
int				heredoc_ctrld(char *line);
void			heredoc_ctrlc(int signum);
int				init_signals_heredoc(void);

//signals
static void		ctrl_c(int signum);
static void		handle_child(int signum);
int				init_signals(int mode);
void			ctrl_d(char *line);

//unset
int				is_valid_unset(const char *arg);
char			**remove_env_var(char **env, int index);
int				remove_var(char ***env, const char *arg);
int				ft_unset(t_line *line);

//adding_space
void			quote_check_meta(char *str, int *i);
void			shift_and_insert(char *str, int *len, int pos);
int				count_meta_character(char *str, char s);
void			adding_space(t_mini *mini, char s);

//dollar_utils
int				count_substr(const char *str, const char *sub);
char			*allocate_new_node(const char *node, \
				const char *var, const char *value);		
void			replace_substr_in_node(char *new_node, \
				const char *node, const char *var, const char *value);
void			replace_node_substr(t_split *node, \
				const char *var, const char *value);
void			dollar_quest(t_split *split, t_exit_status *exit);

//dollar_utils2
char			*get_res(char *var, t_mini **mini);
int				get_dollar(char *str, int i, \
				t_mini **mini, char **new_str);
int				get_var_end(char *str, int i);
char			*extract_var(char *str, int i, int j);
int				get_single_quote(char *str, int i, char **new_str);

//dollar_utils3
int				get_double_quote(char *str, int i, \
				char **new_str, t_mini **mini);
char			*remove_quotes_two(t_split **split, t_mini **mini);
int				update_i(char *str, char **new_str, int i, t_mini **mini);

//removing_quotes
void			expander(t_split *split, t_mini *mini);
void			remove_quotes(t_split *split);
void			quotes(t_split *split);
void			char_remove(t_split *split, int i);
void			routine2(t_split *split, t_mini *mini, \
				t_exit_status *exit_t);

//space_utils
void			shift_and_insert_spaces(char *line, \
				int *len, int *i, char s);
char			*create_new_line_with_space(t_mini *mini, \
				int len, int count);
int				skip_single_quotes(char *node, int *i);

//split_for_exr
void			cases(t_split **tmp_spl, t_line **tmp2, \
				int *flag_pipe);
t_line			*split_for_exe(t_split *split, t_mini *mini);

//split_utils
int				skip_quotes(const char *line, int i);
void			skip_spaces(const char *line, int *i);
void			handle_token(const char *line, int *i);
int				closed_quotes_index(const char *input);
void			cmd_to_lower(char *str);

//split_utils2
int				is_redir(t_split *split);
void			line_list_file_right(t_split *tmp, \
				t_line *line, int type);
void			line_list_file_left(t_split *tmp, \
				t_line *line, int type);
void			line_list_arg(t_split *tmp, t_line *line);
void			lexer(t_mini *mini);

//split
int				meta_type_2(int i, char *str);
int				meta_type(char *str);
t_split			*sub_node(const char *str, unsigned int start, \
				size_t len);				
void			add_to_list(t_split **head, const char *line, \
				int start, int end);
t_split			*splitter(t_mini *mini);

//check_the_syntax
int				redirect_check(char *input);
int				all_closed_quotes(const char *input);				
int				backslash_check(char *input);
int				semicolon_check(char *input);
int				check_the_syntax(t_mini *mini);

//pipe_check
int				is_pipe_first(char *input);
int				is_pipe_last(char *input);
int				double_pipe(char *input);
int				redir_plus_pipe_two(char *input);		
int				redir_plus_pipe(char *input);

//redir_check
int				mixed_redir(char *input);
int				mixed_redir_three(char *input);
int				mixed_redir_four(char *input);
int				mixed_redir_two(char *input);				
int				last_arg_is_redir(char *input);

//print_utils
int				print_syntax_error_quote(void);
int				print_syntax_error_pipe(void);
int				print_unexpected_char_error(void);
int				print_syntax_error_redir(void);

//free_split
void			free_the_split(t_split *split);
void			free_the_minis(t_mini *mini);

//get_free
void			free_command(t_line *head);
void			free_fd_list(t_fd *head);
void			free_ty_list(t_ty *head);
void			free_arg_list(char **arg);

//struct_utils
t_line			*create_new_line(char ***env);
t_fd			*create_new_fd(char *name, int type);
t_ty			*create_new_ty(int type);
void			append_line(t_line **head, t_line *new_line);
void			append_fd(t_fd **head, t_fd *new_fd);

//struct_utils
void			append_ty(t_ty **head, t_ty *new_ty);
int				add_arg(char ***arg, char *new_arg);
int				struct_len(t_line *head);
int				fd_len(t_fd **head);

//syntax_utils
int				pass_the_quotes(char c, int quote);
int				pass_the_spaces(char *input, int i);
#endif
