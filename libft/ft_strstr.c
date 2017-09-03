/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 13:41:19 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/03 12:53:16 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	k;
	size_t	j;

	i = 0;
	j = 0;
	k = -1;
	if (needle[i] != '\0' && haystack[i] != '\0')
	{
		while (haystack[i] != '\0')
		{
			while (haystack[i++] == needle[j++])
			{
				if (j == ft_strlen(needle))
					return ((char*)haystack + (i - j));
			}
			j = 0;
			i = ++k;
		}
	}
	if (needle[0] == '\0')
		return ((char*)haystack);
	return (NULL);
}
