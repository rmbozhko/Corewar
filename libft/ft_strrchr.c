/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:03:50 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 14:48:10 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	int		sign;
	char	*result;

	i = 0;
	sign = 0;
	result = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == (char)c)
		{
			sign = 1;
			result = (char*)(str + i);
		}
		i++;
	}
	if (str[i] == '\0' && (char)c == '\0')
		return (((char*)str) + i);
	if (sign)
		return (result);
	return (NULL);
}
