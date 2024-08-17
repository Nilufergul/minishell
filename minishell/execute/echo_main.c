/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 01:19:08 by selmandemir       #+#    #+#             */
/*   Updated: 2024/08/18 01:55:25 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	echo_main(char *s)
{
	int	ind;

	ind = echo_index(s);
	printf("%s", &s[ind]);
	if (ind < 3)
		printf("\n");
	return (1);
}


int main()
{
	printf("");
	echo_main("--nnnnnn selman selman");
	echo_main("-nnnnnn selman selman");
}
