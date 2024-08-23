#include <stdio.h>
#include <unistd.h>
#include <string.h> // libft fonksiyonları kullanılacak
#include <stdlib.h>

int ft_cd(char *path)
{
    static char prev_dir[1024] = "";
    char current_dir[1024];

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    if (path == NULL || strcmp(path, "~") == 0)
    {
        char *home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            printf("cd: HOME environment variable not set\n");
            return 1;
        }
        path = home_dir;
    }
    else if (strcmp(path, "-") == 0)
    {
        if (prev_dir[0] == '\0')
        {
            printf("cd: OLDPWD not set\n");
            return 1;
        }
        path = prev_dir;
        printf("%s\n", path);
    }

    if (chdir(path) != 0)
    {
        perror("cd");
        return 1;
    }

    strcpy(prev_dir, current_dir);

    return 0;
}

//TEST İÇİN MAİN

/*
int main()
{
    char command[256];
    char *args[10];
    int running = 1;

    while (running)
    {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s$ ", cwd);
        }
        else
        {
            perror("getcwd");
            exit(1);
        }

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            printf("\n");
            continue;
        }

        command[strcspn(command, "\n")] = '\0';

        int i = 0;
        char *token = strtok(command, " ");
        while (token != NULL && i < 10)
        {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] != NULL && strcmp(args[0], "cd") == 0)
        {
            if (args[1] == NULL)
            {
                ft_cd(NULL);
            }
            else
            {
                ft_cd(args[1]);
            }
        }
        // Eğer komut "exit" ise programdan çık
        else if (args[0] != NULL && strcmp(args[0], "exit") == 0)
        {
            running = 0;
        }
        // Diğer komutlar için mesaj yazdır
        else
        {
            printf("Komut: %s\n", command);
        }
    }

    return 0;
}
*/
