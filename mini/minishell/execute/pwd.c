
#include "../minishell.h"

void	pwd(void)
{
	char	*s;

	s = getcwd(NULL, 0);
	printf("%s\n", s);
}