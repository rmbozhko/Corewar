/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:54:24 by rbozhko           #+#    #+#             */
/*   Updated: 2016/11/28 18:10:55 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	k;

	i = ft_strlen(dest);
	k = 0;
	while (k < n)
	{
		dest[i++] = src[k++];
		if (src[k] == '\0')
			break ;
	}
	dest[i] = '\0';
	return (dest);
}
