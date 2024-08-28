#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "deneme.h"

void builtin_unset(t_mini *mini, char *args[])
{
	if (args[1] == NULL)
	{
		return;
	}

	for (int i = 1; args[i] != NULL; i++)
	{
		int j = 0;
		while (mini->env[j] != NULL)
		{
			if (strncmp(mini->env[j], args[i], strlen(args[i])) == 0 && mini->env[j][strlen(args[i])] == '=')
			{
				free(mini->env[j]);
				for (int k = j; mini->env[k] != NULL; k++)
				{
					mini->env[k] = mini->env[k + 1];
				}
				break;
			}
			j++;
		}
	}
}
