/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrip.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 15:30:19 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/13 15:31:10 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_lstrip(char *str)
{
	size_t		i;
	char		*temp;

	temp = NULL;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if ((temp = ft_strsub(str, i, ft_strlen(str) - i)) == NULL)
		return (NULL);
	return (temp);
}
