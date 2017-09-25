/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/26 13:23:56 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 14:53:38 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*srce;
	char		*dest;
	size_t		a;

	srce = src;
	dest = dst;
	a = 0;
	if (dest > srce)
	{
		a = len - 1;
		while ((int)a >= 0)
		{
			dest[a] = srce[a];
			a--;
		}
		return (dst);
	}
	while (a < len)
	{
		dest[a] = srce[a];
		a++;
	}
	return (dst);
}
