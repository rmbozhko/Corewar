/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_words_count.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 17:44:57 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/28 17:44:59 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_words_count(const char *s, char c)
{
	int		counter;
	int		delimiter;

	counter = 0;
	delimiter = 0;
	while (*s != '\0')
	{
		if (delimiter == 1 && *s == c)
			delimiter = 0;
		if (delimiter == 0 && *s != c)
		{
			delimiter = 1;
			counter++;
		}
		s++;
	}
	return (counter);
}
