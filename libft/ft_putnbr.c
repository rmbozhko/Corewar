/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/04 18:36:32 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 15:17:47 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	int		i;
	char	rev[11];
	int		tempnb;

	tempnb = nb;
	if (nb == (-2147483647 - 1))
		nb = -214748364;
	i = 0;
	if (tempnb < 0)
		nb = -nb;
	while ((nb / 10) > 0)
	{
		rev[i] = nb % 10 + '0';
		i++;
		nb = nb / 10;
	}
	rev[i] = nb % 10 + '0';
	if (tempnb < 0)
		rev[++i] = '-';
	while (i >= 0)
		ft_putchar(rev[i--]);
	if (tempnb == (-2147483647 - 1))
		ft_putchar('8');
}
