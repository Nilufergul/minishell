
// exit [n] seklinde calısacakmıs

//shell ismi sonradan degisirse bu fonksiyon güncellenecek

#include "../minishell.h"
#include <unistd.h>
#include <stdlib.h>

void ft_exit(char **args)
{
	int exitCode = 0;
	int i = 0;

	while (args[i] != NULL)
	{
		i++;
	}

	if (i == 1)
	{
		write(2, "exit\n", 5);
		exit(0);
	}

	for (int j = 0; args[1][j]; j++)
	{
		if (args[1][j] != '-' && (args[1][j] < '0' || args[1][j] > '9'))
		{
			write(1, "exit\n", 5);
			write(2, "exit: numeric argument required\n", 33);
			exit(255);
		}
	}

	exitCode = atoi(args[1]);

	if (i == 2)
	{
		write(1, "exit\n", 5);
		exit(exitCode);
	}
	else
	{

		write(1, "exit\n", 5);
		write(2, "exit: too many arguments\n", 25);
	}
}

/*
int main(int argc, char **argv)
{
	if (argc)
	{

		ft_exit(argv);
	}
	return 0;
}

	test icin ./a.out'tan sonra asağıdakileri elle dene yada yapıstır
	"-10"
	"randomword"
	"random" "word"
	"-10192" "random"
	"-43" "-124"
*/
