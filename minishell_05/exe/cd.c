#include "../minishell.h"
int ft_cd(char *path)
{
    static char prev_dir[1024] = "";
    char current_dir[1024];

    if (getcwd(current_dir, sizeof(current_dir)) == NULL)
    {
        perror("getcwd");
        return 1;
    }

    if (path == NULL || ft_strncmp(path, "~" , ft_strlen(path)) == 0)
    {
        char *home_dir = getenv("HOME");
        if (home_dir == NULL)
        {
            printf("cd: HOME environment variable not set\n");
            return 1;
        }
        path = home_dir;
    }
    else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
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

    strcpy(prev_dir, current_dir); // lib function

    return 0;
}

void	pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
    free(s);
}
