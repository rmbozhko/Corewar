#include "op.h"
#include "asm.h"


t_op    op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

int			ft_validate(const int fd)
{
	t_valid			valid;
	t_assembler 	asml;

	// valid = (t_valid*)malloc(sizeof(t_valid*));
	valid.line_num = 0;
	valid.errors = 0;
	valid.name = 0;
	valid.cmmt = 0;
	valid.flag = 1;
	valid.file = ft_read_file(fd);
	asml.label = (t_labels**)malloc(sizeof(t_labels**));
	asml.instr_counter = 0;
	asml.oper = (t_operations**)malloc(sizeof(t_operations**));
	// asml.labels->next = NULL;
	ft_lexical_validation(&valid);
	valid.line_num = 0;
	// printf("Number of erros after lex_valid:%d\n", valid.errors);
	(valid.errors == 0) ? ft_syntax_validation(&valid) : 0;
	// printf("Number of erros after syn_valid:%d\n", valid.errors);
	valid.line_num = 0;
	(valid.errors == 0) ? ft_logical_validation(&valid, &asml) : 0;
	valid.line_num = 0;
	(valid.errors == 0) ? ft_gather_commands(&valid, &asml) : 0;
	printf("INSTRUCTION COUnter:%zu\n", asml.instr_counter);
	return ((valid.errors == 0) ? (1) : (0));
}

int			main(int argc, char const *argv[])
{
	int		fd;

	if (argc == 2)
	{
		if (ft_strlen(argv[1]) > 0)
		{
			fd = open(argv[1], O_RDONLY);
			(fd >= 0 && fd <= 4096) ? ft_validate(fd) : /*Handle case as an error*/0;
			// while (1);
		}
	}
	else
		ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and annotated version of code to standard output\n");
	return (0);
}
