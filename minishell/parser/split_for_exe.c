#include "../minishell.h"

void fd_zero(t_fd *fd)
{
	fd->file = -1;
	fd->name = NULL;
	fd->next = NULL;
	fd->type = -1;
}

void cmd_to_lower(char *str)
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
	int i;

	i = 0;
	while(tmp && tmp->meta != PIPE) //					bu func larda tmp oluşturmana muhtemelen gerek yok çünkü ana func da adresleri saklıyoruz
	{
		line->fd->name = tmp->node;
		line->fd->type = tmp->meta;
		add_next_list_fd(line->fd); // 									fd nin başlangıcını tutmamız gerekiyor mu ???????????? 
		line->fd = line->fd->next;
		tmp = tmp->next;
	}
}

void take_types(t_split *split, t_line *line)
{
	t_fd *tmp;															// fd nin adresini tmp de mi nerede tutmak lazım bunu çöz
	tmp = line->fd;
	if(split->meta == GREAT || split->meta == GREATER)
	{
		line->fd->name = split->next->node;
		tmp->type = split->meta;
		tmp->file = -1; // check this;
		add_next_list_fd(line->fd);  // fd nin başlangıcını tutmamız gerekiyor mu ???????????? 
		line->fd = line->fd->next; // yeni liste oluşturma func
	}
	else if(split->meta == LESS)
	{
		line->fd->name = split->prev->node; // 																							prev node çekmicez bunu düzelt hepsini tek if de yapabilirsin artık
		line->fd->type = split->meta;
		line->fd->file = -1; // check this;
		add_next_list_fd(line->fd);  // fd nin başlangıcını tutmamız gerekiyor mu ???????????? 
		line->fd = line->fd->next; // yeni liste oluşturma func
	}
	else if(split->meta == HEREDOC)
	{
		line->fd->type = split->meta;
		line->fd->name = NULL;
		line->fd->file = -1;
		add_next_list_fd(line->fd);  // fd nin başlangıcını tutmamız gerekiyor mu ???????????? galiba line structının tmp sinde kullanılan fd boş bir fd oluyo zaten ama emin değilim.
		line->fd = line->fd->next; // yeni liste oluşturma func
	}
}

void line_list_arg(t_split *tmp, t_line *line)
{
	int i;

	i = 0;
	line->arg = malloc(sizeof(char *) * 10 + 1); // burda arg sayısı kadar yer acmak gerkli burası cokomelli !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!?????????????????????????????????????????
	while(tmp) // echo adsadsa >> b.txt de adsadsa diye dosya açmıyo o yüzden echo özel durum redir ya da pipe görene kadar argüman olarak alsın
	{
		if(tmp->meta != PIPE && tmp->meta != GREAT && tmp->meta != GREATER && tmp->meta != LESS && tmp->meta != HEREDOC)
		{
			line->arg[i] = malloc(sizeof(tmp->node)); // gerekli mi?
			line->arg[i] = tmp->node; // buna yer açılmıyor o yuzden seg yiyo olabilir
			i++;
		}
		// line arg icin double pointer yer acmak icin kac arguman oldugunu bilip ona yer acıp sonrasında uzunlugu kadar da acmak lazım
		
		tmp = tmp->next;
	}
	line->arg[i] = NULL;
}

t_line *split_for_exe(t_split *split) // denenmedi. // HEREDOC KOŞULLARI BİLİNMEDİĞİ İÇİN EKLENMEDİ ONLARI ÖĞRENİP GÜNCELLİCEZ.
{
	t_split *tmp;
	int flag_pipe;
	t_line *line;
	t_line *tmp2;
	int arg_check;

	tmp = split;
	arg_check = 0;
	flag_pipe = 1;
	line = NULL; 
	start_next_list_line(&line);
	start_new_list_fd(line);
	tmp2 = line;
	while(tmp)
	{
		if(flag_pipe == 1)
		{
			line->cmd = tmp->node;
			flag_pipe = 0;
			cmd_to_lower(line->cmd);
			tmp = tmp->next;
			if(ft_strncmp(line->cmd,"cat",ft_strlen(line->cmd))) // ya cat olucak ya da redirect ten sonrakiler file olcak o yüzden echo ya değil cat e özel durum yazman lazım // bir de echo ya özel yazılcak onları da txt olarak değil arg olarak alıcak heredoc görene kadar. 
			{
				line_list_file(tmp, tmp2); // file alıcaz
			}
		}
		if(tmp->meta == EXCEPT && flag_pipe == 0 && arg_check == 0)// && tmp->meta != PIPE) //-> bu kontrol gerekli mi
		{
			arg_check = 1;
			line_list_arg(tmp, tmp2);
		}
		if(tmp->meta != EXCEPT && tmp->meta != PIPE) // meta karakterden sonraki argumanu almıuyor
		{
			line_list_file(tmp, tmp2);
		}
		if(tmp->meta == PIPE)
		{
			arg_check = 0;
			flag_pipe = 1;
			tmp = tmp->next;
			add_new_list_line(tmp2); // yeni liste oluşturma func_2
			tmp2 = tmp2->next;
			start_new_list_fd(tmp2); // yeni listenin fd si başlatılcak. 
		}
		else
			tmp = tmp->next;
	} // 									 en son herşey bitince adresleri geri iade mi ediyoduk ?????????????
	return(line);
}
