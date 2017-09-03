/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 13:34:52 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/30 14:49:00 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*temp;

	temp = (t_list*)malloc(sizeof(t_list));
	if (!temp)
		return (NULL);
	if (!content)
	{
		temp->content = NULL;
		temp->content_size = 0;
	}
	else
	{
		temp->content = malloc(content_size);
		if (!temp)
			return (NULL);
		ft_memcpy(temp->content, content, content_size);
		temp->content_size = content_size;
	}
	temp->next = NULL;
	return (temp);
}
