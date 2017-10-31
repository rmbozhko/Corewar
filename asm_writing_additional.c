/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_writing_additional.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:02:59 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 22:25:09 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

unsigned int		move_bits(unsigned int number)
{
	unsigned int	f_part;
	unsigned int	s_part;
	unsigned int	th_part;
	unsigned int	fourth_part;

	f_part = number >> 24;
	s_part = (number << 8) >> 24;
	th_part = (number << 16) >> 24;
	fourth_part = (number << 24) >> 24;
	number = (fourth_part << 24) + (th_part << 16) + (s_part << 8) + f_part;
	return (number);
}

void				ft_handle_short_int(char **str, signed short int value)
{
	char		*c;

	c = (char*)&value;
	**str = c[1];
	(*str)++;
	**str = c[0];
	(*str)++;
}

void				ft_handle_int(char **str, int value)
{
	char		*c;
	int			num;
	size_t		i;

	i = 0;
	num = move_bits(value);
	c = (char*)&num;
	while (i < DIR_SIZE)
	{
		**str = c[i++];
		(*str)++;
	}
}

void				ft_handle_args(t_arg *arg, char **str, t_operations *oper)
{
	if (arg->type == REG_CODE)
	{
		**str = ft_atoi(arg->value);
		(*str)++;
	}
	else if ((arg->type == DIR_CODE && (ft_get_label_size(oper->command) == 2))
			|| arg->type == IND_CODE)
	{
		if (!(arg->label))
			ft_handle_short_int(str, (short int)ft_atoi(arg->value));
		else if (!(arg->value))
			ft_handle_short_int(str, (short int)CALCULATE_REF_ADDR);
	}
	else if (arg->type != 0)
	{
		if (!(arg->label))
			ft_handle_int(str, ft_atoi(arg->value));
		else if (!(arg->value))
			ft_handle_int(str, CALCULATE_REF_ADDR);
	}
}
