/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/15 14:09:09 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/15 14:09:12 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_count_char(char *str, char c)
{
	int			i;
	size_t		counter;

	counter = 0;
	i = -1;
	while (str[++i])
		counter += (str[i] == c) ? 1 : 0;
	return (counter);
}
