/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 17:30:17 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 15:17:28 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*temp;

	if (s1 && s2)
	{
		temp = (char*)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
		if (temp)
		{
			temp = ft_strcpy(temp, s1);
			temp = ft_strcat(temp, s2);
			return (temp);
		}
	}
	return (NULL);
}
