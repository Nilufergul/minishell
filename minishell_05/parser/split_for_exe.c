#include "../minishell.h"

void cmd_to_lower(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
}

int is_redir(t_split *split)
{
	if(split->meta == HEREDOC || split->meta == GREAT || split->meta == GREATER || split->meta == LESS)
		return (1);
	return 0;
}

void line_list_file_right(t_split *tmp, t_line *line)
{
	append_fd(&(line->right), create_new_fd(tmp->node, tmp->meta));
}

void line_list_file_left(t_split *tmp, t_line *line)
{
	append_fd(&(line->left), create_new_fd(tmp->node, tmp->meta));
}

void line_list_arg(t_split *tmp, t_line *line)
{
	while(tmp && tmp->meta != PIPE && is_redir(tmp))
	{
		add_arg(&(line->arg), tmp->node);
		tmp = tmp->next;
	}
}

t_line *split_for_exe(t_split *split, t_mini *mini) // denenmedi. // HEREDOC KOŞULLARI BİLİNMEDİĞİ İÇİN EKLENMEDİ ONLARI ÖĞRENİP GÜNCELLİCEZ.
{
	t_split *tmp_spl;
	int flag_pipe;
	t_line *line;
	t_line *tmp2;

	tmp_spl = split;
	flag_pipe = 1;
	line = NULL; 

	tmp2 = line;
	while(tmp_spl)
	{
		if(flag_pipe == 1 && !is_redir(tmp_spl))
		{
			if(tmp_spl == NULL)
			{
				tmp_spl = tmp_spl->next;
				break;
			}
			cmd_to_lower(tmp_spl->node);
			tmp2 = create_new_line(tmp_spl->node, (mini->env));
			append_line(&line, tmp2); // yeni liste oluşturma func_2
			flag_pipe = 0;
			tmp_spl = tmp_spl->next;
			if(tmp_spl == NULL)
				break;
		}
		if(tmp_spl->meta == EXCEPT && flag_pipe == 0)
		{
			line_list_arg(tmp_spl, tmp2); // ok
			tmp_spl = tmp_spl->next;
		}
		else if(tmp_spl->meta == GREAT || tmp_spl->meta == GREATER)
		{
			tmp_spl = tmp_spl->next;
			line_list_file_right(tmp_spl, tmp2);
		}
		else if(tmp_spl->meta == LESS || tmp_spl->meta == HEREDOC)
		{
			tmp_spl = tmp_spl->next;
			line_list_file_left(tmp_spl, tmp2);
		}
		if(tmp_spl && tmp_spl->meta == PIPE)
		{
			flag_pipe = 1;
			tmp_spl = tmp_spl->next;
		}
		else
		{
			if(tmp_spl->next == NULL)
				break;
			tmp_spl = tmp_spl->next;
		}
	}
	return(line);
}

