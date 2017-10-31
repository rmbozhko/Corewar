/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_errors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 18:49:46 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 18:49:47 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

size_t		ft_loop_through(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]) && !ft_isalpha(str[i]))
			break ;
		i++;
	}
	return ((i == 0) ? 1 : i);
}

void		ft_exception(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	ft_putchar_fd('\n', fd);
	exit(1);
}

void		ft_lexical_err(t_valid *valid)
{
	if (valid->errors == 0)
	{
		ft_putstr("Lexical error at [");
		ft_putnbr(valid->l_num + 1);
		ft_putstr(":");
		ft_putnbr(valid->i + 1);
		ft_putstr("]\n");
	}
	valid->i += ft_loop_through(valid->file[valid->l_num] + valid->i);
	valid->errors += 1;
}

char		*get_arg_description(size_t arg_type)
{
	if (arg_type == REG_CODE)
		return ("register");
	else if (arg_type == DIR_CODE)
		return ("direct");
	else if (arg_type == IND_CODE)
		return ("indirect");
	else
		return ("NULL");
}

void		ft_log_error(size_t i, size_t arg_type, int opcode, int flag)
{
	if (flag == 1)
	{
		ft_putstr("Invalid parameter count for instruction ");
	}
	else
	{
		ft_putstr("Invalid parameter ");
		ft_putnbr(i);
		ft_putstr(" type ");
		ft_putstr(get_arg_description(arg_type));
		ft_putstr(" for instruction ");
	}
	ft_putstr(g_op_tab[opcode].command_name);
	ft_putchar('\n');
}
