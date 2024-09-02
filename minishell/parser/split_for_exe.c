#include "../minishell.h"

void fd_zero(t_fd *fd)
{
	fd->file = -1;
	fd->name = NULL;
	fd->next = NULL;
	fd->type = -1;
}

char *cmd_to_lower(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += 32;
		}
		i++;
	}
	return (str);
}

void line_zero(t_line *line)
{
	line->arg = NULL;
	line->cmd = NULL;
	line->fd = NULL;
	line->next = NULL;
}

void start_new_list_fd(t_line *line)
{
	t_fd *a;
    a = (t_fd *)malloc(sizeof(t_fd)); // Hatalı olan kısım düzeltilmiş
    if (a == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }
    line->fd = a;
    fd_zero(line->fd);
}

void start_next_list_line(t_line **line) // neden cift pointer alıyor bilmiyorum??!!
{
    *line = (t_line *)malloc(sizeof(t_line)); // Hatalı olan kısım düzeltilmiş
	if(!line)
	{
		// hata kontrolu
	}
    line_zero(*line);
}

void add_next_list_fd(t_fd *fd)
{
	t_fd *tmp;
	tmp = malloc(sizeof(t_fd));
	if(!tmp)
	{
		// hata kontrolu
	}
	fd_zero(tmp);
	fd->next = tmp;
}
// liste oluşturmalar güncellenicek.
void add_new_list_line(t_line *line)
{
	t_line *tmp;
	tmp = malloc(sizeof(t_line));
	if(!tmp)
	{
		// hata kontrolu
	}
	line_zero(tmp);
	line->next = tmp;
}

void line_list_file(t_split *tmp, t_line *line)
{
		line->fd->name = tmp->node;
		line->fd->type = tmp->meta;
		add_next_list_fd(line->fd); 
		line->fd = line->fd->next;
		tmp = tmp->next;
}

int ft_args_len(t_split *split)
{
	t_split *tmp;
	tmp = split;
	int i;
	i = 0;
	while(tmp && tmp->meta != PIPE && is_redir(tmp))
	{
		while(tmp->node[i])
			i++;
		if(tmp->next != NULL)
			tmp = tmp->next;
		else
			break;
	}
	return (i);
}

void line_list_arg(t_split *tmp, t_line *line) // ABORT
{
	int i;

	i = 0;
	line->arg = malloc(ft_args_len(tmp) * sizeof(char **)); // burda arg sayısı kadar yer acmak gerkli burası cokomelli !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?????????????????????????????????????????
	while(tmp && tmp->meta != PIPE && is_redir(tmp)) // echo adsadsa >> b.txt de adsadsa diye dosya açmıyo o yüzden echo özel durum redir ya da pipe görene kadar argüman olarak alsın SOLVED ACCES LE DOSYAYI DENİCEZ
	{
		line->arg[i] = malloc(ft_strlen(tmp->node) * sizeof(char));
		line->arg[i] = tmp->node; // strcpy??*
		i++;
		tmp = tmp->next;
		// line arg icin double pointer yer acmak icin kac arguman oldugunu bilip ona yer acıp sonrasında uzunlugu kadar da acmak lazım
	}
	line->arg[i] = NULL;
}

int is_redir(t_split *split)
{
	t_split *tmp;
	tmp = split;
	if(tmp->meta == 1 || tmp->meta == 3 || tmp->meta == 4 || tmp->meta == 5)
		return (1);
	return 0;
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
	start_next_list_line(&line);
	start_new_list_fd(line);
	tmp2 = line;
	while(tmp_spl)
	{
		if(flag_pipe == 1)  // açılabiliyo mu sonraki node u redir mi check i atılcak dosyalraa
		{
			if(tmp_spl == NULL)
				break;
			line->cmd = cmd_to_lower(tmp_spl->node);
			flag_pipe = 0;
			tmp_spl = tmp_spl->next;
			if(tmp_spl == NULL)
				break;
		}
		if(tmp_spl->meta == EXCEPT && flag_pipe == 0)// && tmp->meta != PIPE) //-> bu kontrol gerekli mi
		{
			line_list_arg(tmp_spl, tmp2);
		}
		else if(tmp_spl->meta == GREAT || tmp_spl->meta == GREATER)
		{
			tmp_spl = tmp_spl->next;
			line_list_file(tmp_spl, tmp2);
		}
		if(tmp_spl->meta == PIPE)
		{
			flag_pipe = 1;
			tmp_spl = tmp_spl->next;
			add_new_list_line(tmp2); // yeni liste oluşturma func_2
			tmp2->env_line = mini->env;
			tmp2 = tmp2->next;
			start_new_list_fd(tmp2); // yeni listenin fd si başlatılcak.
		}
		else
			tmp_spl = tmp_spl->next;
	} // 									 en son herşey bitince adresleri geri iade mi ediyoduk ?????????????
	return(line);
}
