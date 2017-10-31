/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_label_ref.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:28:08 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 19:28:21 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

size_t					ft_check_is_label(size_t type, char *str, char *string)
{
	char		*temp;

	temp = NULL;
	if (type == DIR_CODE)
		temp = ft_strsub(string, 2, ft_strlen(str));
	else if (type == IND_CODE)
		temp = ft_strsub(string, 1, ft_strlen(str));
	if (!ft_strcmp(temp, str))
	{
		ft_strdel(&temp);
		return (1);
	}
	return (0);
}

size_t					ft_find_line(size_t t, char *str, char **file, int flag)
{
	size_t		i;
	size_t		j;
	int			dbq_flag;

	j = 0;
	dbq_flag = 0;
	while (file[j] && !(i = 0))
	{
		while (file[j][i])
		{
			if (file[j][i] == '"')
				dbq_flag = (dbq_flag) ? 0 : 1;
			else if (CMMT(file, j, i) && !dbq_flag)
				break ;
			else if (((DIRECT_CHARS(file[j], i)) || (file[j][i] == LABEL_CHAR
				&& ft_strchr(LABEL_CHARS, file[j][i + 1]))) && !dbq_flag)
			{
				if (ft_check_is_label(t, str, file[j] + i))
					return ((flag) ? j + 1 : i + 1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

void					ft_ref_error(size_t t, char *l, char **f, t_valid *v)
{
	char		*temp;

	if (v->errors == 0)
	{
		temp = l;
		ft_putstr("No such label live while attempting to dereference [");
		ft_putnbr(ft_find_line(t, l, f, 1));
		ft_putchar(':');
		ft_putnbr(ft_find_line(t, l, f, 0));
		ft_putstr((t == 2) ? "] DIRECT_LABEL \"" : "] INDIRECT_LABEL \"");
		l = ft_strjoin(((t == 2) ? "%:" : ":"), l);
		ft_strdel(&temp);
		ft_putstr(l);
		ft_putstr("\"\n");
	}
	v->errors++;
}

size_t					ft_find_label(char *str)
{
	t_labels			*label;

	label = g_asm.label;
	while (label)
	{
		if (ft_strcmp(str, label->name) == 0)
			return (1);
		label = label->next;
	}
	return (0);
}

void					ft_check_label_appear(char **file, t_valid *valid)
{
	t_operations		*oper;
	size_t				i;

	oper = g_asm.oper;
	while (oper)
	{
		i = 0;
		while (i < ARG_MAX_NUM)
		{
			if ((oper->args[i]->type == IND_CODE
				|| oper->args[i]->type == DIR_CODE)
				&& (oper->args[i]->label))
			{
				if (!ft_find_label(oper->args[i]->label))
				{
					ft_ref_error(oper->args[i]->type,
						oper->args[i]->label, file, valid);
				}
			}
			i++;
		}
		oper = oper->next;
	}
	ft_gen_info_errors_handling(valid);
}
