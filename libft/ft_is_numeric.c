/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_numeric.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 11:32:56 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:37:11 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_is_numeric(char *str)
{
	size_t		i;
	size_t		sign;

	i = 0;
	sign = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = 1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (sign == 1)
		return ((i > 1) ? 1 : 0);
	else
		return ((i > 0) ? 1 : 0);
}
