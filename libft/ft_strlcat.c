/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 18:13:03 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 16:27:58 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dst_len;

	i = 0;
	dst_len = 0;
	if (src && size > 0)
	{
		while (dst[i] && i < size)
			i++;
		dst_len = i;
		while (i < size - 1 && src[i - dst_len])
		{
			dst[i] = src[i - dst_len];
			i++;
		}
		(i < size) ? dst[i] = '\0' : 0;
	}
	if (!(dst))
		return (0);
	return (dst_len + ft_strlen(src));
}
