/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rstrip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 21:38:23 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:38:24 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_rstrip(char *str)
{
	size_t		i;
	char		*temp;

	temp = NULL;
	i = ft_strlen(str) - 1;
	while (str[i] == ' ' || str[i] == '\t')
		i--;
	if ((temp = ft_strsub(str, 0, ++i)) == NULL)
		return (NULL);
	return (temp);
}
