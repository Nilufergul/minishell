#include "../minishell.h"

int	is_redir(t_split *split)
{
	if (split->meta == HEREDOC || split->meta == GREAT
		|| split->meta == GREATER || split->meta == LESS)
		return (1);
	return (0);
}

void	line_list_file_right(t_split *tmp, t_line *line, int type)
{
	append_fd(&(line->right), create_new_fd(tmp->node, type));
}

void	line_list_file_left(t_split *tmp, t_line *line, int type)
{
	append_fd(&(line->left), create_new_fd(tmp->node, type));
}

void	line_list_arg(t_split *tmp, t_line *line)
{
	add_arg(&(line->arg), tmp->node);
}
