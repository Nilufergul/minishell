/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcan <rcan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 14:08:24 by rcan              #+#    #+#             */
/*   Updated: 2024/09/18 14:08:25 by rcan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	max;

	if (!s)
	{
		return (NULL);
	}
	max = 0;
	slen = ft_strlen(s);
	if (start > slen)
	{
		return (ft_strdup(""));
	}
	if (start < slen)
		max = slen - start;
	if (max > len)
		max = len;
	substr = (char *)malloc((sizeof(char)) * max + 1);
	if (!substr)
	{
		return (NULL);
	}
	ft_strlcpy(substr, s + start, max + 1);
	return (substr);
}
