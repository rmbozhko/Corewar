/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:27:49 by rbozhko           #+#    #+#             */
/*   Updated: 2017/01/05 16:27:52 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(const char *s, char c)
{
	size_t	index;
	char	**temp;
	int		words;

	if (!(s))
		return (NULL);
	index = 0;
	words = ft_words_count(s, c);
	if (!(temp = (char**)malloc(sizeof(temp) * words + 1)))
		return (NULL);
	while (words--)
	{
		while (*s == c && *s != '\0')
			s++;
		if ((temp[index] = ft_strsub(s, 0, ft_wordlen(s, c))) == NULL)
			return (NULL);
		s = s + ft_wordlen(s, c);
		index++;
	}
	temp[index] = NULL;
	return (temp);
}
