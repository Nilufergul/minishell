/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:56:19 by muhademi          #+#    #+#             */
/*   Updated: 2023/10/15 14:56:19 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len1;
	size_t	len2;
	char	*dst;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	dst = (char *)malloc ((len1 + len2 + 1) * sizeof(char));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s1, len1 + 1);
	ft_strlcat(dst, s2, (len1 + len2 + 1));
	return (dst);
}
