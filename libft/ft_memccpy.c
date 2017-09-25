/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 14:54:50 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 14:54:55 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *str1, const void *str2, int c, size_t n)
{
	size_t	i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			*(unsigned char*)(str1 + i) = *(unsigned char*)(str2 + i);
			if (*(unsigned char*)(str1 + i) == (unsigned char)c)
				return ((char*)((str1 + i) + 1));
			i++;
		}
	}
	return (NULL);
}
