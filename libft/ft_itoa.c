/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 11:25:23 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/26 14:52:33 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	int		i;
	int		num_length;
	char	*result;

	i = n;
	num_length = ft_numlen(n);
	result = ft_strnew(num_length);
	if (n == (-2147483647 - 1))
		return (ft_strdup("-2147483648"));
	if (result != NULL)
	{
		if (i < 0)
			i = (-1) * n;
		result[--num_length] = ((i % 10) + 48);
		while (i /= 10)
			result[--num_length] = ((i % 10) + 48);
		if (n < 0)
			result[0] = '-';
		return (result);
	}
	return (NULL);
}
