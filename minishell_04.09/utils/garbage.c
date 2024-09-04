#include "../minishell.h"

t_gc_col	*garbage_collector(t_gc_col *garb, void *gp)
{
	t_gc_col	*new_node;
	t_gc_col	*tmp;

	new_node = malloc(sizeof(t_gc_col));
	if (!new_node)
		return (NULL);
	new_node->ptr = gp;
	new_node->next = NULL;
	if (!garb)
		return (new_node);
	tmp = garb;
	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}
	tmp->next = new_node;
	return (garb);
}

void	free_garb(t_gc_col *garb)
{
	t_gc_col	*tmp;

	while (garb != NULL)
	{
		tmp = garb;
		garb = garb->next;
		free(tmp->ptr);
		free(tmp);
	}
}
/*
#include "../minishell.h"
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	while (true)
	{
		t_gc_col *gc;
		char *str1;
		char *str2;
		char *str3;
		t_gc_col *tmp;

		gc = NULL;
		str1 = malloc(20);
		str2 = malloc(30);
		str3 = malloc(40);
		if (!str1 || !str2 || !str3)
		{
			perror("malloc");
			return (1);
		}
		// Bellek atamalarını kontrol etmek için içerik ekleme
		snprintf(str1, 20, "Hello, World!");
		snprintf(str2, 30, "Garbage Collector Test!");
		snprintf(str3, 40, "Another string to test.");
		// Pointerları garbage collector'a ekleme
		gc = garbage_collector(gc, str1);
		gc = garbage_collector(gc, str2);
		gc = garbage_collector(gc, str3);
		// Garbage collector içeriğini yazdırma
		tmp = gc;
		while (tmp != NULL)
		{
			printf("%s\n", (char *)tmp->ptr);
			tmp = tmp->next;
		}
		// Garbage collector'ı serbest bırakma
		free_garb(gc);
		sleep(10);
	}
		return (0);
}*/