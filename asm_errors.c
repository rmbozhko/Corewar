#include "asm.h"
#include "op.h"

void		ft_lexical_err(int line_num, int char_index, t_valid *valid)
{
	printf("H________________E_______________R______________E!%s | %c\n", valid->file[line_num] + char_index + valid->left_offset + 1, valid->file[line_num][char_index + valid->left_offset + 1]);
	if (valid->errors == 0)
	{
		ft_putstr("Lexical error at [");
		ft_putnbr(line_num + 1); // line number
		ft_putstr(":");
		ft_putnbr(valid->left_offset + char_index + 1); // index of char in line + num of spaces omitted by ft_lstrip function
		ft_putstr("]\n");
	}
	valid->errors += 1;
}