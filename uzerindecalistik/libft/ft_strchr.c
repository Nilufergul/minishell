/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngulcift <ngulcift@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 14:35:02 by ngulcift          #+#    #+#             */
/*   Updated: 2024/09/20 14:35:04 by ngulcift         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	while ((*str != '\0') && (*str != (char)ch))
	{
		str++;
	}
	if (*str == (char)ch)
	{
		return ((char *)str);
	}
	return (NULL);
}
