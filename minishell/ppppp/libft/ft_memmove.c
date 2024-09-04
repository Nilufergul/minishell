/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:54:41 by muhademi          #+#    #+#             */
/*   Updated: 2023/10/15 14:54:41 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	long	i;
	char	*ds;
	char	*sr;

	i = len - 1;
	ds = (char *) dst;
	sr = (char *) src;
	if (dst == 0 && src == 0)
		return (0);
	if (ds < sr)
		return (ft_memcpy(ds, sr, len));
	while (i >= 0)
	{
		ds[i] = sr[i];
		i -= 1;
	}
	return (ds);
}
