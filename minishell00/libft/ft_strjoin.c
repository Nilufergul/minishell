/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usisman <usisman@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 13:40:41 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/14 21:58:29 by usisman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *lft_str, char *buff)
{
	int		i;
	int		j;
	char	*str;

	if (!lft_str)
	{
		lft_str = malloc(1);
		lft_str[0] = '\0';
	}
	if (!buff)
		return (0);
	str = malloc(sizeof(char) * ((ft_strlen(lft_str) + ft_strlen(buff)) + 1));
	if (!str)
		return (0);
	i = -1;
	while (lft_str[++i] != '\0')
		str[i] = lft_str[i];
	j = 0;
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[i] = '\0';
	if (lft_str)
		free(lft_str);
	return (str);
}