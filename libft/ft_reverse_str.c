/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/31 16:29:50 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 16:29:51 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_reverse_str(char *str)
{
	char		*temp;
	size_t		i;
	size_t		j;

	i = 0;
	j = ft_strlen(str) - 1;
	temp = (char*)malloc(sizeof(char) * j + 1);
	while (str[j])
	{
		temp[i] = str[j];
		j--;
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
