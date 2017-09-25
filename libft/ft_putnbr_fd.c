/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 13:53:41 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/16 15:17:00 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
{
	int		i;
	char	rev[11];
	int		tempnb;

	tempnb = nb;
	if (nb == -2147483648)
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
		ft_putchar_fd(rev[i--], fd);
	if (tempnb == -2147483648)
		ft_putchar_fd('8', fd);
}
