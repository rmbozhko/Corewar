/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 17:32:35 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 15:37:56 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t num)
{
	char *temp;

	temp = dest;
	while (*src && num > 0)
	{
		*temp++ = *src++;
		num--;
	}
	while (num-- > 0)
		*temp++ = 0;
	return (dest);
}
