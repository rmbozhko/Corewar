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

void		ft_lexical_err(t_valid *valid)
{
	// printf("H________________E_______________R______________E!%s | %c\n", valid->file[valid->line_num] + valid->i + 1, valid->file[valid->line_num][valid->i + 1]);
	if (valid->errors == 0)
	{
		ft_putstr("Lexical error at [");
		ft_putnbr(valid->line_num + 1); // line number
		ft_putstr(":");
		ft_putnbr(valid->i + 1); // index of char in line + num of spaces omitted by ft_lstrip function
		ft_putstr("]\n");
	}
	valid->i += ft_loop_through(valid->file[valid->line_num] + valid->i);
	valid->errors += 1;
}

char 		*get_arg_description(size_t arg_type)
{
	if (arg_type == 1)
		return ("register");
	else if (arg_type == 2)
		return ("direct");
	else if (arg_type == 4)
		return ("indirect");
	else
		return ("unknown");
}

void		ft_logical_error(size_t i, size_t arg_type, int cmd_opcode, int flag)
{
	if (flag == 1)
	{
		/*(valid->errors == 0) ? */ft_putstr("Invalid parameter count for instruction ");// : 0;
	}
	else
	{
		/*if (valid->errors == 0)
		{*/
			ft_putstr("Invalid parameter ");
			ft_putnbr(i);
			ft_putstr(" type ");
			ft_putstr(get_arg_description(arg_type));
			ft_putstr(" for instruction ");
		// }
	}
	// if (valid->errors == 0)
	// {
		ft_putstr(op_tab[cmd_opcode].command_name);
		ft_putchar('\n');
	// }
}