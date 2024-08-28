#ifndef MINI_SHELL_H
#define MINI_SHELL_H

typedef struct s_mini
{
	char **env;
	char *line;
} t_mini;

void builtin_unset(t_mini *mini, char *args[]);
void builtin_export(t_mini *mini, char *args[]);
void print_env(char **env);

#endif
