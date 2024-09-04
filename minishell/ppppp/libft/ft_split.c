/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:56:13 by muhademi          #+#    #+#             */
/*   Updated: 2023/10/15 14:56:13 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	ans;

	i = 0;
	ans = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] == 0)
			break ;
		while (s[i] && s[i] != c)
			i++;
		ans += 1;
	}
	return (ans);
}

static void	fill_array_with_words(char **arr, char *str, char c)
{
	int	index;
	int	i;
	int	tmp_i;

	index = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			continue ;
		}
		tmp_i = i;
		while (str[i] && str[i] != c)
			i++;
		arr[index] = malloc(i - tmp_i + 1);
		if (!arr[index])
			arr[0] = 0 ;
		ft_strlcpy(arr[index], str + tmp_i, i - tmp_i + 1);
		index++;
	}
	arr[index] = 0;
}

char	**ft_split(char *str, char c)
{
	char	**array;
	int		words_count;

	words_count = count_words(str, c);
	array = (char **)malloc((words_count + 1) * sizeof(char *));
	if (!array)
		return (0);
	fill_array_with_words(array, str, c);
	return (array);
}
