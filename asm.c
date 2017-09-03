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

void		ft_lexical_err(int line_num, int char_index)
{
	ft_putstr("Lexical error at [");
	ft_putnbr(line_num + 1); // line number
	ft_putstr(":");
	ft_putnbr(char_index + 2); // index of char in line 
	ft_putstr("]\n");
	// exit(0);
}

char 		**ft_read_file(const int fd)
{
	char 		**arr;
	size_t		i;
	char		*line;

	arr = (char**)malloc(sizeof(char*) * 1000000000000);
	i = 0;
	line = ft_strnew(0);
	while (get_next_line(fd, &line, ft_strnew(0)) > 0)
		arr[i++] = ft_strdup(line);
	arr[i] = NULL;
	return (arr);
}

int 		ft_spaces_based_line(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}



int 		ft_str_amongst(char *str, char *base)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(base, str[i]))
			return (0);
	}
	return (1);
}

int 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char 		*temp;
	char		*str;
	size_t		i;

	
	temp = ft_strip(line);
	str = ft_strsub(temp, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
	{
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		while (str[i] && str[i] != '"')
		{
			if (!ft_strchr(LABEL_CHARS, str[i]) && str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
			{
				ft_lexical_err(valid->line_num, i);
				break ; // Lexical error case
			}
			i++;
		}
	}
	//return ERROR
}

int 		ft_handle_dot(char *str, t_valid* valid)
{
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		ft_name_cmmt(str, 1, valid);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		ft_name_cmmt(str, 0, valid);
	}
	else
		ft_lexical_err(valid->line_num, 1); // Lexical error return -> .extend || .nam || .comme
}

int 		ft_handle_label(char *str, t_valid* valid)
{
	size_t		i;

	i = 0;
	printf("str:%s\n", str);
	while (str[i] && str[i] != ':')
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			printf("OLOL\n");
			ft_lexical_err(valid->line_num, i);// Lexical error
		}
		i++;
	}
	if (i == 0)
	{
		printf("HAHAHAHAH\n");
		ft_lexical_err(valid->line_num, i);
		// no chars before semicolon -> lexical error
 	}
}

int 		ft_lexical_validation(t_valid* valid)
{
	char 		*temp;

	while (valid->file[valid->line_num])
	{
		temp = ft_lstrip(valid->file[valid->line_num]);
		if (temp[0] == '.')
		{
			printf("HERE!%c\n", temp[0]);
			ft_handle_dot(temp, valid);
		}
		else if (!ft_strchr(LABEL_CHARS, temp[0]) && temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2)
		{
			printf("YO!\n");
			ft_lexical_err(valid->line_num, 1); // Lexical Error
			// printf("HERE!\n");
		}
		else if (ft_strchr(LABEL_CHARS, temp[0]) && temp[0])
		{
			printf("temp_error:%c\n", temp[0]);
			ft_handle_label(temp, valid);
			//	handle custom label-function
		}
		valid->line_num++;
	}
	return (1);
}

int			ft_validate(t_valid *valid)
{
	if (ft_lexical_validation(valid))
	{
		printf("Lexically validated!\n");
		// if (ft_syntax_validation()) 
	}
	return (0);
}

void		ft_manipulate(const int fd)
{
	t_valid		*valid;

	valid = (t_valid*)malloc(sizeof(t_valid*));
	valid->line_num = 0;
	valid->file = ft_read_file(fd);
	if (ft_validate(valid))
	{
		printf("GOOD!\n");
	}
	else
	{
		printf("BAD\n");
	}
}

int			main(int argc, char const *argv[])
{
	int		fd;

	if (argc == 2)
	{
		if (ft_strlen(argv[1]) > 0)
		{
			fd = open(argv[1], O_RDONLY);
			(fd >= 0 && fd <= 4096) ? ft_manipulate(fd) : /*Handle case as an error*/0;
		}
	}
	else
		//ft_putstr("Usage: ./asm [-a] <sourcefile.s>\n\t-a : Instead of creating a .cor file, outputs a stripped and annotated version of code to standard output\n");
	return (0);
}