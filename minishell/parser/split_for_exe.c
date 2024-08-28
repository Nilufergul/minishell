#include "../minishell.h"

void take_arguments(t_split *split, t_line *line, int *ct)
{
	int i;
	t_fd *current_fd;

	i = 0;
	while(split->meta != PIPE && split->next != NULL)
	{
		line->arg[i] = split->node;
		current_fd = line->fd;
		current_fd->type = split->meta;
		split = split->next;
		//current_fd = current_fd->next;
		*ct++;
		i++;
	}

}

void up_to_line(t_line *line, int ct)
{
	int i;

	i = 0;
	while(i < ct)
	{
		line = line->next;
		i++;
	}
}

void take_types(t_line *line, t_split *split, int ct) // type ın durumuna göre yazılcak. 
{
	int i;
	t_fd *current_fd;

	i = 0;
	while(i < ct)
	{
		current_fd = line->fd;
		current_fd->type = split->meta;
		line = line->next;
		split = split->next;
		//current_fd = current_fd->next;burası olmslı mı
		i++;
	}
}

t_line *split_for_exe(t_split *split) // denenmedi.
{
	t_split *tmp;
	int ct;
	ct = 0;
	t_line *tmp2;
	tmp = split;
	int flag;

	flag = 1;

	t_line *line;
	line = malloc((sizeof(t_line)));
	line->fd = malloc((sizeof(t_fd)));
	tmp2 = line;

	while(tmp->next)
	{
		if(flag == 1)
		{
			line->cmd = split->node;
			flag = 0;
		}
		else if(flag == 0)
		{
			take_arguments(tmp, tmp2, &ct);
			take_types(tmp, tmp2, ct);
			up_to_split(tmp2, ct);
			ct = 0;
		}
		if(split->meta == PIPE)
		{
			flag = 1;
		}
		tmp = tmp->next;
	}
	return(line);
}
