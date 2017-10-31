/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_log_valid_helpers.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 22:20:49 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 16:02:44 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

size_t		ft_get_instr_addr(t_operations *curr_oper)
{
	size_t				addr;
	t_operations		*oper;

	addr = 0;
	oper = g_asm.oper;
	while (oper)
	{
		addr += oper->instr_len;
		oper = oper->next;
	}
	if (oper != NULL)
		return (addr - curr_oper->instr_len);
	return (addr);
}

void		ft_add_cmd_to_list(t_operations *oper)
{
	t_operations		*op;

	op = g_asm.oper;
	while (op != NULL && op->next != NULL)
	{
		op = op->next;
	}
	oper->addr = ft_get_instr_addr(oper);
	if (op == NULL)
	{
		g_asm.oper = oper;
	}
	else
	{
		op->next = oper;
	}
	g_asm.instr_counter++;
}

void		ft_add_cmd_to_label_list(t_labels *label)
{
	t_labels *l;

	l = g_asm.label;
	while (l != NULL && l->next != NULL)
	{
		l = l->next;
	}
	if (l == NULL)
	{
		g_asm.label = label;
	}
	else
	{
		l->next = label;
	}
}

char		*ft_validate_string(char *str)
{
	size_t			i;
	size_t			j;
	char			*temp;

	temp = (char*)malloc(sizeof(char) * ft_strlen(str));
	ft_bzero(temp, ft_strlen(str));
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == COMMENT_CHAR || str[i] == COMMENT_CHAR2)
			break ;
		temp[i] = str[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}
