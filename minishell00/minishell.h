# ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <stdio.h>
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

volatile int g_catch_ctrlc;

typedef enum type
{
	EXCEPT = 0,
	HEREDOC = 1,
	PIPE = 2,
	GREAT = 3,
	GREATER = 4,
	LESS = 5,
	DOLLAR = 6
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

typedef struct s_fd
{
	int fd;
	int	type;
	char *name;
	struct s_fd *next;
}				t_fd;
typedef struct s_exit_status
{
	int	*exit_code;
}				t_exit_status;

typedef struct  s_line
{
	char	*cmd;
	char	**arg;
	char 	***env;
	int		exit_code_line;
	struct  s_fd    *right;
	struct 	s_fd 	*left;
	struct  s_line  *next;
}				t_line;


typedef struct	s_mini
{
	char **env;
	char *line;
}				t_mini;

typedef struct s_pipe_info
{
    int **pipes;
    pid_t *pid;
    int len;
	int	input;
	int	output;
} t_pipe_info;

int	w_exit_status(int status);
void	quotes(t_split *split);
void	char_remove(t_split *split, int i);
void	dollar_quest(t_split *split,t_exit_status *exit );
void	quotes_cases(t_split **split, t_mini **mini, int *flag);
int	open_rights(t_fd *head);
int	open_lefts(t_fd *head);
void	run_exec(t_line *line, char *command, char **env);
char	*get_path(char **env);
char	*get_command_path(char **env, char *command);

int struct_len(t_line *head);
t_fd *create_new_fd(char *name, int type);
t_ty *create_new_ty(int type);
void append_line(t_line **head, t_line *new_line);
void append_fd(t_fd **head, t_fd *new_fd);
void append_ty(t_ty **head, t_ty *new_ty);
int struct_len(t_line *head);
int add_arg(char ***arg, char *new_arg);

char	*get_copy(char *result, char **arr);
int fd_len(t_fd **head);
void clean_pipes(t_line *command, t_pipe_info *pipe_info);
void create_processes(t_line *command, t_pipe_info *pipe_info);
void run_child_process(t_line *command, t_pipe_info *pipe_info, int i);
int	pwd(void);
int	echo_main(char *s);
int	echo_index(char *s);
void	echo_incn(char c, int *n);
void	echo_case1(char c, int *expect, int *ret);
int	echo_case2(char c, int *expect, int *ret);
int	echo_case3(char c, int *expect, int *ret, int *n_count);
char	*merge_echo(char **arr);

int heredoc(char *target);
int	open_lefts(t_fd *head);
int	built_in(t_line *command);
int	built_in2(t_line *command);
int	run_command_run(t_line *command);
int	**fill_pipes(int count);
void	close_all_pipes(int **pipes, int len);
void	free_all_pipes(int **pipes, int len);

int ft_export(t_line *command);
int ft_cd(t_line *line);
void create_update(char ***env, const char *name, const char *value);
int ft_unset(t_line *command);
int	ft_environment(char **env);
void	ft_exit(t_line *line);
long long int	ft_longlong(const char *str);
void	make_pipe(t_line *command);
int	built_in2(t_line *command);

//signals 
void    rl_replace_line(const char *text, int clear_undo);
int	init_signals(int mode);
void	ctrl_d(char *line);
void heredoc_ctrlc(int signum);
int	heredoc_ctrld(char *line);
int	init_signals_heredoc(void);



//parser...
//adding_space
void quote_check_meta(char *str, int *i);
void shift_and_insert(char *str, int *len, int pos);
int count_meta_character(char *str, char s);
void adding_space(t_mini *mini, char s);
void lexer(t_mini *mini);
//dollar_sign
char *dollar_exp(char *s);
int vary_check(t_mini *mini, char *var);
char *value_ret(t_mini *mini, int p);
char *dollar_checker(char *s, t_mini *mini);
int	handle_dollar(t_split *split, t_mini *mini);
//dollar_utils
int count_substr(const char *str, const char *sub);
char *allocate_new_node(const char *node, const char *var, const char *value);
void replace_substr_in_node(char *new_node, const char *node, const char *var, const char *value) ;
void replace_node_substr(t_split *node_struct, const char *var, const char *value);
int 	quoted_dollar(t_split *split);
//removing_quotes
void 	expander(t_split *split, t_mini *mini);
void quotes(t_split *split);
void	char_remove(t_split *split, int i);
void remove_quotes(t_split *split);
//split
enum type	meta_type_2(int i, char *str);
enum type meta_type(char *str);
t_split	*sub_node(const char *str, unsigned int start, size_t len);
void	add_to_list(t_split **head, const char *line, int start, int end);
t_split	*splitter(t_mini *mini);
//split_for_exe
void fd_zero(t_fd *fd);
void cmd_to_lower(char *str);
void line_zero(t_line *line);
void start_new_list_fd(t_line *line);
void start_next_list_line(t_line **line);
void add_next_list_fd(t_fd *fd);
void add_new_list_line(t_line *line);
void line_list_file(t_split *tmp, t_line *line);
void take_types(t_split *split, t_line *line);
void line_list_arg(t_split *tmp, t_line *line);
t_line *split_for_exe(t_split *split, t_mini *mini);
void	line_list_file_right(t_split *tmp, t_line *line, int type);
void	line_list_file_left(t_split *tmp, t_line *line, int type);
//split_utils
int		skip_quotes(const char *line, int i);
void	skip_spaces(const char *line, int *i);
void	handle_token(const char *line, int *i);
int		closed_quotes_index(const char *input);


// syntax...
//check the syntax
int	redirect_check(char *input);
int	all_closed_quotes(const char *input);
int	backslash_check(char *input);
int	semicolon_check(char *input);
int	check_the_syntax(t_mini *mini);
//pipe_check
int	is_pipe_first(char *input);
int	is_pipe_last(char *input);
int	double_pipe(char *input);
int	redir_plus_pipe_two(char *input);
int	redir_plus_pipe(char *input);
//print_utils
int	print_syntax_error_quote();
int	print_syntax_error_pipe();
int	print_unexpected_char_error();
int	print_syntax_error_redir();
//redir_check
int	is_redir(t_split *split);
int	mixed_redir(char *input);
int	mixed_redir_three(char *input);
int	mixed_redir_four(char *input);
int	mixed_redir_two(char *input);
int	last_arg_is_redir(char *input);


//utils...

// free
void free_the_minis(t_mini *mini);
void free_the_split(t_split *split);
//struct_utils
t_line *create_new_line(char ***env);
t_fd *create_new_fd(char *name, int type);
t_ty *create_new_ty(int type);
void append_line(t_line **head, t_line *new_line);
void append_fd(t_fd **head, t_fd *new_fd);


//syntax_utils
int	pass_the_spaces(char *input, int i);
int	pass_the_quotes(char c, int quote);


//minishell_main // ennvler bölüncek
t_mini *init_mini(t_mini *mini, char** environ);
int env_size(char **environ);;
void ft_env(t_mini *mini ,char** environ);
void running_shell(t_mini *mini,t_exit_status *exit);
void lexer(t_mini *mini);
void routine(t_mini *mini,t_exit_status *exit);

void	free_command(t_line *head);
void	free_fd_list(t_fd *head);
void	free_ty_list(t_ty *head);
void	free_arg_list(char **arg);


char *remove_quotes_selman(t_split **split, t_mini **mini);
int get_double_quote(char *str, int i, char **new_str, t_mini **mini);
int get_single_quote(char *str, int i, char **new_str);
int get_dollar(char *str, int i, t_mini **mini, char **new_str);
char *get_res(char *var, t_mini **mini);
#endif
