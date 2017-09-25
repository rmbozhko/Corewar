/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_bid_arr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:23:38 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 15:16:31 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_create_bid_arr(size_t size, char *str)
{
	size_t		i;
	char		**temp;

	i = 0;
	temp = (char**)malloc(sizeof(char*) * size + 1);
	if (temp != NULL)
	{
		while (i < size)
		{
			temp[i] = ft_strdup(str);
			i++;
		}
		temp[i] = NULL;
		return (temp);
	}
	return (NULL);
}
