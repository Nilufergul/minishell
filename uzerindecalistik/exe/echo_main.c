/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 12:06:21 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 12:06:23 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo_main(char *s)
{
	int	ind;

	if (!s)
	{
		printf("\n");
		return (0);
	}
	ind = echo_index(s);
	printf("%s", &s[ind]);
	if (ind < 3)
		printf("\n");
	return (0);
}
