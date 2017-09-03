/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 16:45:56 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 14:53:18 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*temp;
	int		i;

	temp = (char*)malloc((sizeof(char) * ft_strlen(s)) + 1);
	if (temp == NULL)
		return (NULL);
	else
	{
		i = 0;
		while (s[i] != '\0')
		{
			temp[i] = s[i];
			i++;
		}
		temp[i] = '\0';
	}
	return (temp);
}
