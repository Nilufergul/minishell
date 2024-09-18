/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:08:07 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 14:08:08 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *ndl, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ndl[0] == '\0')
		return ((char *)h);
	while (h[i] != '\0' && i < n)
	{
		if (h[i] == ndl[j])
		{
			while (h[i + j] == ndl[j] && i + j < n)
			{
				if (ndl[j + 1] == '\0')
					return ((char *)h + i);
				j++;
			}
			j = 0;
		}
		i++;
	}
	return (NULL);
}
