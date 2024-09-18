/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:08:11 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 14:08:12 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	index;

	index = ft_strlen(str);
	while (index >= 0)
	{
		if (str[index] == (char)ch)
		{
			return ((char *)(str + index));
		}
		index--;
	}
	return (NULL);
}
