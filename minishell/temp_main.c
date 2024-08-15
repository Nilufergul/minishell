#include "minishell.h"

int main()
{
    t_line *komut1;
    t_line *komut2;
    t_fd    *fd1;
    t_fd    *fd2;
    t_ty    *ty1;
    t_ty    *ty2;


    komut1 = malloc(sizeof(t_line));
    komut2 = malloc(sizeof(t_line));
    fd1 =    malloc(sizeof(t_fd));
    fd2 =    malloc(sizeof(t_fd));
    ty1 =    malloc(sizeof(t_ty));
    ty2 =    malloc(sizeof(t_ty));



    komut1->cmd = "ls";
    komut2->cmd = "grep";

    char *s = "selman";
    char **ss;
    ss = malloc(sizeof(char *));
    ss[0] = s;
    komut2->arg = ss;

    fd1->name = "dosya1";
    fd2->name = "dosya2";

    fd1->next = fd2;
    ty1->type = GREATER;
    ty2->type = GREATER;


    //////////////////////////////////////////////////////////////////////////

    printf("%d\n", ty1->type);




    printf("Calisiyor..\n");
    return 0;
}


