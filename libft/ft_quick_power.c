/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quick_power.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/25 17:08:12 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 17:32:46 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_quick_power(int num, int degree, int i)
{
	if (degree >= 0)
	{
		if (degree == 0)
			return (i);
		if ((degree % 2) == 0)
			return (ft_quick_power(num * num, degree / 2, i));
		if ((degree % 2) != 0)
			return (ft_quick_power(num, degree - 1, i * num));
	}
	return (0);
}
