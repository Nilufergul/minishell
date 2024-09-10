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

void	quotes_cases(t_split **split, t_mini **mini, int *flag)
{
	int	stop;

	stop = 1;
	if (closed_quotes_index((*split)->node)) // dolar tırnak grubu içinde mi kalıyor
	{
		if ((quoted_dollar((*split)) && !closed_quotes_index((*split)->node)))
			replace_node_substr((*split), "$", "");
		if (closed_quotes_index((*split)->node) == '\'') // dolar hangi tırnak içinde kalıyor (tek tırnak içindeki dolar çalışmıyor
			*flag = 1;
	}
	else if (quoted_dollar((*split)))
		replace_node_substr((*split), "$", "");
	if (*flag == 0)
	{
		while (ft_strchr((*split)->node,'$') && stop)
		{
			dollar_quest((*split)); // $? çalıştırıyor
			stop=handle_dollar((*split), *mini); // expand edilicek dolarları çalıştırıyor.
		}
	}
	(*split)->meta = EXCEPT;
}
