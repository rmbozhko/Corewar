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
	printf("H________________E_______________R______________E!%s | %c\n", valid->file[valid->line_num] + valid->i + 1, valid->file[valid->line_num][valid->i + 1]);
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