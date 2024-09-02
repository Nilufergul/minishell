// Selman
#include "../minishell.h"


t_line *create_new_line(char *cmd_str, char **env)
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
    new_line->env = env;
    new_line->arg = NULL;
    new_line->type = NULL;
    new_line->fd = NULL;
    new_line->minis = NULL;
    new_line->next = NULL;
    return new_line;
}

t_fd *create_new_fd(char *name, int type)
{
    t_fd *new_fd;

    new_fd = (t_fd *)malloc(sizeof(t_fd));
    if (new_fd == NULL)
        return NULL;
    new_fd->fd = -1;
    new_fd->name = ft_strdup(name);
    new_fd->type = type;
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

int fd_len(t_fd **head)
{
    int res;
    t_fd *current;

    res = 0;
    current = *head;
    if (current != NULL)
    {
        res += 1;
        current = current->next;
    }
    return (res);
}

char *go_exe(char *str, char **arr)
{
    size_t total_length = 0;
    size_t str_len = 0;
    int num_strings = 0;
    char *result = NULL;
    char *current_pos = NULL;
    size_t i = 0;

    if (str != NULL)
    {
        str_len = strlen(str);
        total_length += str_len;
        num_strings++;
    }
    while (arr != NULL && arr[num_strings - 1] != NULL)
    {
        total_length += strlen(arr[num_strings - 1]);
        num_strings++;
    }
    if (num_strings > 1)
        total_length += num_strings - 1;
    result = (char *)malloc(total_length + 1);
    if (result == NULL)
        return NULL;

    current_pos = result;
    if (str != NULL)
    {
        strcpy(current_pos, str);
        current_pos += str_len;
        if (arr != NULL && arr[0] != NULL)
        {
            *current_pos = ' ';
            current_pos++;
        }
    }
    i = 0;
    while (arr != NULL && arr[i] != NULL)
    {
        strcpy(current_pos, arr[i]);
        current_pos += strlen(arr[i]);
        if (arr[i + 1] != NULL)
        {
            *current_pos = ' ';
            current_pos++;
        }
        i++;
    }
    *current_pos = '\0';
    return result;
}
/*


    t_line *komut1;
    t_line *komut2;
    t_line *komut3;


    komut1 = create_new_line("pwd", env);
    komut2 = create_new_line("cd", env);
    komut3 = create_new_line("pwd", env);

    add_arg(&(komut2->arg), "..");

    append_fd(&(komut1->fd), create_new_fd("a", 4));
    append_fd(&(komut1->fd), create_new_fd("b", 4));

    make_pipi means run
    make_pipe(komut1, env);
    make_pipe(komut2, env);





*/
