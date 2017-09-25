/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/17 14:48:17 by rbozhko           #+#    #+#             */
/*   Updated: 2016/12/17 17:38:31 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *temp;
	t_list *next_node;

	if (alst && (*del))
	{
		temp = *alst;
		while (temp)
		{
			next_node = temp->next;
			(*del)(temp->content, temp->content_size);
			free(temp);
			temp = next_node;
		}
		*alst = NULL;
	}
}
