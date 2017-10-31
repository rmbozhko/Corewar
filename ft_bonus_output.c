/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 19:07:47 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/29 19:08:43 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

static void		ft_print_label_if_on_line(size_t key)
{
	t_labels			*label;

	label = g_asm.label;
	while (label)
	{
		if (label->f_key == key)
		{
			ft_putstr(label->name);
			ft_putchar(':');
			break ;
		}
		label = label->next;
	}
}

static void		ft_handle_arguments(int i, t_arg **args)
{
	while (args[i])
	{
		if (args[i]->type == 1)
		{
			ft_putstr("r");
			ft_putstr(args[i]->value);
		}
		else if (args[i]->type == 2)
		{
			ft_putchar('%');
			(!(args[i]->value)) ? ft_putchar(':') : 0;
			ft_putstr((args[i]->value) ? args[i]->value : args[i]->label);
		}
		else if (args[i]->type == 3)
		{
			(args[i]->label) ? ft_putchar(':') : 0;
			ft_putstr((args[i]->label) ? args[i]->label : args[i]->value);
		}
		i++;
		if (i < ARG_MAX_NUM && args[i]->type != 0)
			ft_putstr(",\t");
		else
			break ;
	}
	ft_putstr("\n\n");
}

static void		ft_handle_gen_info(void)
{
	ft_putendl("Dumping annotated program on standard output");
	ft_putstr("Program size : ");
	ft_putnbr(g_asm.prog_size);
	ft_putendl(" bytes");
	ft_putstr("Name : \"");
	ft_putstr(g_asm.name);
	ft_putendl("\"");
	ft_putstr("Comment : \"");
	ft_putstr(g_asm.cmmt);
	ft_putendl("\"");
}

static void		ft_handle_oper_info(t_operations *oper)
{
	ft_putstr("Coding byte value of current operation: ");
	ft_putnbr(oper->cod_byte);
	ft_putstr("\nLength of current operation: ");
	ft_putnbr(oper->instr_len);
	ft_putstr("\nAddress of current operation: ");
	ft_putnbr(oper->addr);
	ft_putchar('\n');
}

void			ft_dump_info(void)
{
	size_t				i;
	t_operations		*oper;

	oper = g_asm.oper;
	i = 0;
	ft_handle_gen_info();
	while (oper)
	{
		ft_putendl("#####################################################");
		ft_handle_oper_info(oper);
		ft_print_label_if_on_line(i);
		ft_putstr("\t");
		ft_putstr(g_op_tab[oper->command].command_name);
		ft_putstr("\t");
		ft_handle_arguments(0, oper->args);
		i++;
		oper = oper->next;
	}
}
