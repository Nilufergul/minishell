// Selman
#include "../minishell.h"

t_line *create_new_line(char *cmd_str)
{
    t_line *new_line;
    new_line = (t_line *)malloc(sizeof(t_line));

    if (new_line == NULL)
        return NULL;
    new_line->cmd = ft_strdup(cmd_str);
    if (new_line->cmd == NULL)
    {
        free(new_line);
        return NULL; 
    }
    new_line->arg = NULL;
    new_line->type = NULL;
    new_line->fd = NULL;
    new_line->minis = NULL;
    new_line->next = NULL;
    return new_line;
}

t_fd *create_new_fd(int fd, char *name)
{
    t_fd *new_fd;

    new_fd = (t_fd *)malloc(sizeof(t_fd));
    if (new_fd == NULL)
        return NULL; 
    new_fd->fd = fd;
    new_fd->name = ft_strdup(name);
    if (new_fd->name == NULL)
    {
        free(new_fd);
        return NULL; 
    }
    new_fd->next = NULL;
    return new_fd;
}

t_ty *create_new_ty(int type)
{
    t_ty *new_ty;

    new_ty = (t_ty *)malloc(sizeof(t_ty));
    if (new_ty == NULL)
        return NULL; 
    new_ty->type = type;
    new_ty->next = NULL;
    return new_ty;
}

void append_line(t_line **head, t_line *new_line)
{
    t_line *current;

    if (*head == NULL)
        *head = new_line;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_line;
    }
}

void append_fd(t_fd **head, t_fd *new_fd)
{
    t_fd *current;

    if (*head == NULL)
        *head = new_fd;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_fd;
    }
}

void append_ty(t_ty **head, t_ty *new_ty)
{
    t_ty *current;

    if (*head == NULL)
        *head = new_ty;
    else
    {
        current = *head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_ty;
    }
}

int add_arg(char ***arg, char *new_arg)
{
    int i;
    char **new_arg_list;
    int j;

    i = 0;
    while ((*arg) && (*arg)[i])
        i++;
    new_arg_list = (char **)malloc(sizeof(char *) * (i + 2));
    if (new_arg_list == NULL)
        return -1; 
    j = -1;
    while (++j < i)
    {
        new_arg_list[j] = (*arg)[j];
    }
    free(*arg);
    new_arg_list[i] = strdup(new_arg);
    if (new_arg_list[i] == NULL)
    {
        free(new_arg_list);
        return -1; 
    }
    new_arg_list[i + 1] = NULL;
    *arg = new_arg_list;
    return 0; 
}

int struct_len(t_line *head)
{
    int    len;
    t_line *current;

    len = 0;
    current = head;
    while (current != NULL)
    {
        len += 1;
        current = current->next;
    }
    return len;
}

char *join_args_with_spaces(char **arg)
{
    int total_length = 0;
    int num_args = 0;

    if (arg == NULL || *arg == NULL)
        return NULL; 

    while (arg[num_args])
    {
        total_length += strlen(arg[num_args]);
        num_args++;
    }

    total_length += num_args - 1;

    char *result = (char *)malloc(total_length + 2);
    if (result == NULL)
        return NULL; 
    char *current_pos = result;
    *current_pos = ' ';
    current_pos++;
    for (int i = 0; i < num_args; i++)
    {
        size_t len = ft_strlen(arg[i]);
        ft_memcpy(current_pos, arg[i], len);
        current_pos += len;
        if (i < num_args - 1)
        {
            *current_pos = ' ';
            current_pos++;
        }
    }
    *current_pos = '\0';
    return result;
}
