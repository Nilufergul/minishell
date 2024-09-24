/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:05:58 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/24 17:33:33 by ngulcift         ###   ########.fr       */
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

t_mini			*mini_initializer(t_mini *mini, char **environ);
void			ft_env(t_mini *mini, char **environ);
void			start_shell(t_mini *mini, t_exit_status *exit);
void			procedure(t_mini *mini, t_exit_status *exit_t);
void			update_dirs(char ***env, char *current_dir);
int				handle_path(char **path, char ***env);
char			*get_home_path(char ***env);
void			control_space(char *command);
int				change_directory(char *path);
int				ft_cd(t_line *line);
int				is_valid(const char *str);
int				print_error(const char *arg);
int				print_export(char **env);
int				handle_export_argument(t_line *line, const char *arg);
int				ft_export(t_line *line);
void			*ft_realloc(void *ptr, size_t current_size, size_t new_size);
void			add_env_variable(char ***env, int i, const char *name, \
					const char *value);
void			update_env_variable(char **env, int i, \
						const char *name, const char *value);
void			create_update(char ***env, const char *name, const char *value);
long long int	ft_longlong(const char *str);
int				echo_main(char *s);
void			echo_case1(char c, int *expect, int *ret);
int				echo_case2(char c, int *expect, int *ret);
int				echo_case3(char c, int *expect, int *ret);
int				echo_index(char *s);
int				ft_environment(char **env);
void			print_error_exit(const char *arg, const char *msg, int code);
int				check_argument(const char *arg);
int				valid_value(char *arg);
void			exit_handling(char **args, int i, \
				t_exit_status *exit_code_line);
void			ft_exit(t_line *line, t_exit_status *exit_code_line);
char			**get_copy(char *result, char **arr);
char			*merge_echo(char **arr);
int				handle_input(int pipefd[2], char *target);
int				heredoc(char *target);
void			free_pipe_things(t_pipe_info *pipe_info, \
				t_exit_status *exit_code_line);
void			make_pipe(t_line *command, \
				t_exit_status *exit_code_line);
int				built_in2(t_line *command, \
				t_exit_status *exit_code_line);
void			clean_pipes(t_pipe_info *pipe_info, \
				t_exit_status *exit_code_line);
void			procedure3(t_line *command, t_split *split, \
				t_exit_status *exit_t);
void			run_exec(t_line *command, char **env, \
				t_exit_status *exit_code_line);
int				is_directory(const char *path);
int				is_file(const char *path);
char			*get_path(char **env);
char			*get_command_path(char **env, char *command);
void			close_all_pipes(int **pipes, int len);
void			free_all_pipes(int **pipes, int len);
int				handle_right_fd(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit);
int				handle_left_fd(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit);
int				get_fds(t_line *command, t_pipe_info *pipe_info, \
				t_exit_status *exit);
int				open_rights(t_fd *head);
int				open_lefts(t_fd *head);
int				built_in(t_line *command, t_exit_status *exit_code_line);
int				**fill_pipes(int count);
void			create_processes(t_line *command, \
				t_pipe_info *pipe_info, t_exit_status *exit_code_line);
void			handle_fork(t_line *command, t_pipe_info *pipe_info, \
				int i, t_exit_status *exit_code_line);
void			run_child_process(t_line *command, t_pipe_info *pipe_info, \
				int i, t_exit_status *exit_code_line);
int				pwd(void);
int				heredoc_ctrld(char *line);
void			heredoc_ctrlc(int signum);
int				init_signals_heredoc(void);
void			ctrl_c(int signum);
void			handle_child(int signum);
int				init_signals(int mode);
void			ctrl_d(char *line);
int				is_valid_unset(const char *arg);
char			**remove_env_var(char **env, int index);
int				remove_var(char ***env, const char *arg);
int				ft_unset(t_line *line);
void			quote_check_meta(char *str, int *i);
void			shift_and_insert(char *str, int *len, int pos);
int				count_meta_character(char *str, char s);
void			insert_space(t_mini *mini, char s);
int				count_substr(const char *str, const char *sub);
char			*allocate_new_node(const char *node, \
				const char *var, const char *value);
void			switch_substr_in_node(char *new_node, \
				const char *node, const char *var, const char *value);
void			switch_node_substr(t_split *node, \
				const char *var, const char *value);
void			dollar_and_quest(t_split *split, t_exit_status *exit);
char			*get_res(char *var, t_mini **mini);
int				get_dollar(char *str, int i, \
				t_mini **mini, char **new_str);
int				get_var_end(char *str, int i);
char			*extract_var(char *str, int i, int j);
int				get_single_quote(char *str, int i, char **new_str);
int				get_double_quote(char *str, int i, \
				char **new_str, t_mini **mini);
char			*remove_quotes_two(t_split **split, t_mini **mini, \
				t_exit_status *exit);
int				update_index(char *str, char **new_str, int i, t_mini **mini);
void			expander(t_split *split, t_mini *mini, t_exit_status *exit_t);
void			remove_quotes(t_split *split);
void			quotes(t_split *split);
void			char_remove(t_split *split, int i);
void			procedure2(t_split *split, t_mini *mini, \
				t_exit_status *exit_t);
void			shift_and_insert_spaces(char *line, \
				int *len, int *i, char s);
char			*create_new_line_with_space(t_mini *mini, \
				int len, int count);
int				skip_single_quotes(char *node, int *i);
void			cases(t_split **tmp_spl, t_line **tmp2, \
				int *flag_pipe);
t_line			*ready_for_exe(t_split *split, t_mini *mini);
int				skip_quotes(const char *line, int i);
void			skip_spaces(const char *line, int *i);
void			get_token(const char *line, int *i);
int				closed_quotes_index(const char *input);
void			cmd_to_lower(char *str);
int				is_redir(t_split *split);
void			line_list_file_right(t_split *tmp, \
				t_line *line, int type);
void			line_list_file_left(t_split *tmp, \
				t_line *line, int type);
void			line_list_arg(t_split *tmp, t_line *line);
void			lexer(t_mini *mini);
int				give_type_2(int i, char *str);
int				give_type(char *str);
t_split			*get_node(const char *str, unsigned int start, \
				size_t len);
void			append_to_list(t_split **head, const char *line, \
				int start, int end);
t_split			*split_to_nodes(t_mini *mini);
int				check_redirect(char *input);
int				check_quotes_closed(const char *input);
int				check_backslash(char *input);
int				check_semicolon(char *input);
int				checking_syntax(t_mini *mini);
int				check_pipe_first(char *input);
int				check_pipe_last(char *input);
int				double_pipe(char *input);
int				redirect_and_pipe_two(char *input);
int				redirect_and_pipe(char *input);
int				merged_redir(char *input);
int				merged_redir_three(char *input);
int				merged_redir_four(char *input);
int				merged_redir_two(char *input);
int				check_last_arg_redirect(char *input);
int				syntax_error_quote(void);
int				syntax_error_pipe(void);
int				not_allowed_char_error(void);
int				syntax_error_redir(void);
void			free_the_split(t_split *split);
void			free_the_minis(t_mini *mini);
void			free_command(t_line *head);
void			free_fd_list(t_fd *head);
void			free_ty_list(t_ty *head);
void			free_arg_list(char **arg);
t_line			*create_new_line(char ***env);
t_fd			*create_new_fd(char *name, int type);
t_ty			*create_new_ty(int type);
void			append_line(t_line **head, t_line *new_line);
void			append_fd(t_fd **head, t_fd *new_fd);
void			append_ty(t_ty **head, t_ty *new_ty);
int				add_arg(char ***arg, char *new_arg);
int				struct_len(t_line *head);
int				fd_len(t_fd **head);
int				jump_quotes(char c, int quote);
int				jump_spaces(char *input, int i);
void			runcommanderror(char *command, int i);
int				check_file(t_line *command, int flag);
#endif
