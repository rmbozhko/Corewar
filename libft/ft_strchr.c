/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 12:26:34 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/03 15:19:35 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int i;

	i = 0;
	if (str != NULL)
	{
		while (str[i] != '\0')
		{
			if (str[i] == (char)c)
				return ((char*)(str + i));
			i++;
		}
		// if (str[i] == '\0' && (char)c == '\0')
		// 	return (((char*)str) + i);
	}
	return (NULL);
}
