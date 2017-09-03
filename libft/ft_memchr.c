/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:35:27 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 16:46:25 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t i;

	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			if (((unsigned char*)str)[i] == ((unsigned char)c))
				return ((void*)str + i);
			i++;
		}
	}
	return (NULL);
}
