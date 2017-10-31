/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 21:36:37 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 21:36:41 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strip(char *str)
{
	char		*temp;
	char		*string;

	temp = ft_lstrip(str);
	string = temp;
	temp = ft_rstrip(temp);
	ft_strdel(&string);
	return (temp);
}
