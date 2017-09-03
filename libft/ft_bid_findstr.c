/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bid_findstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 13:18:49 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 15:15:21 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_bid_findstr(char *room, char **temp)
{
	size_t		i;

	i = 0;
	while (temp[i])
	{
		if (ft_strcmp(room, temp[i]) == 0)
			return (i);
		i++;
	}
	return (-1);
}
