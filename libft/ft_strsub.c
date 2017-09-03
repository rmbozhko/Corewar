/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 17:20:17 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/28 17:21:05 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*temp;

	i = 0;
	temp = (char*)malloc(len + 1);
	if (s)
	{
		if (temp != NULL)
		{
			while (i < len)
				temp[i++] = s[start++];
			temp[i] = '\0';
			return (temp);
		}
	}
	return (NULL);
}
