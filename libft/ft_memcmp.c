/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 15:49:06 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 11:58:48 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *str1, const void *str2, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char*)(str1 + i) > *(unsigned char*)(str2 + i))
			return (*(unsigned char*)(str1 + i) - *(unsigned char*)(str2 + i));
		else if (*(unsigned char*)(str1 + i) < *(unsigned char*)(str2 + i))
			return (*(unsigned char*)(str1 + i) - *(unsigned char*)(str2 + i));
		i++;
	}
	return (0);
}
