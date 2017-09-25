/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/10 14:51:26 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/25 17:00:24 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int len;

	len = 0;
	if (s)
	{
		while (*s && ft_isspace(*s))
			s++;
		len = ft_strlen(s) - 1;
		while (len > 0 && s[len] && ft_isspace(s[len]))
			len--;
		return (ft_strsub(s, 0, len + 1));
	}
	return (ft_strnew(0));
}
