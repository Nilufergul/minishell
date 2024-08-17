/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: selmandemir <selmandemir@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 00:05:36 by selmandemir       #+#    #+#             */
/*   Updated: 2024/08/18 01:55:19 by selmandemir      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	echo_case1(char c, int *expect, int *ret)
{
	if (c == '-')
		*expect = 2;
	else
		*ret = 0;
}

int	echo_case2(char c, int *expect, int *ret)
{
	if (c == 'n')
		*expect = 3;
	else if (c == ' ')
	{
		*ret = 1;
		return (1);
	}
	else
		*ret = 0;
	return (0);
}

int	echo_case3(char c, int *expect, int *ret, int *n_count)
{
	if (c == ' ')
	{
		*expect = 1;
		return (1);
	}
	else if (c == '-' && *n_count == 1)
		*expect = 2;
	else if (c != 'n')
		*ret = 0;
	return (0);
}

void	echo_incn(char c, int *n)
{
	if (c == 'n')
		(*n)++;
	else
		*n = 0;
}

int	echo_index(char *s)
{
	int	ans;
	int	expect;
	int	n_count;
	int	i;
	int	ret;

	i = 0;
	ret = -1;
	ans = 0;
	while (i < ft_strlen(s))
	{
		if (expect == 1)
			echo_case1(s[i], &expect, &ret);
		else if (expect == 2 && echo_case2(s[i], &expect, &ret) == 1)
			return (i + 1);
		else if (echo_case3(s[i], &expect, &ret, &n_count) == 1)
			ans = i + 1;
		if (ret != -1)
			return (ans + ret);
		echo_incn(s[i], &n_count);
		i++;
	}
	return (ans);
}
