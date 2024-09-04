/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhademi <muhademi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 14:56:17 by muhademi          #+#    #+#             */
/*   Updated: 2023/10/15 14:56:17 by muhademi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s2;

	s2 = (char *) malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!s2)
		return (0);
	ft_strlcpy(s2, s1, (ft_strlen(s1) + 1));
	return (s2);
}
