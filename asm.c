/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/29 17:43:27 by rbozhko           #+#    #+#             */
/*   Updated: 2017/10/31 19:29:45 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"

static void				ft_display_err_amount(size_t lvl, t_valid *valid)
{
	static	size_t		flag = 1;

	if (valid->errors - 1 > 0 && flag)
	{
		ft_putstr("Amount of errors on ");
		if (lvl == 0)
			ft_putstr("lexical");
		else if (lvl == 1)
			ft_putstr("syntax");
		else if (lvl == 2)
			ft_putstr("logical");
		ft_putstr(" level: ");
		ft_putnbr(valid->errors - 1);
		ft_putendl(".");
		flag = 0;
	}
	valid->l_num = 0;
	valid->i = 0;
}

int						ft_validate(const int fd, char *file)
{
	t_valid					valid;
	size_t					i;
	t_ft_valid_layers		*layers_keeper;

	if (fd >= 0 && fd <= 4096)
	{
		i = 0;
		layers_keeper = NULL;
		ft_init(fd, &valid);
		layers_keeper = ft_init_layers();
		while (i < VALIDATION_LAYERS_AMOUNT)
		{
			(valid.errors == 0) ? layers_keeper[i](&valid) : 0;
			ft_display_err_amount(i, &valid);
			i++;
		}
		ft_free_bidarr(valid.file, ft_bidlen(valid.file));
		free(layers_keeper);
	}
	else
	{
		ft_putstr("Can't read source file ");
		ft_exception(file, 2);
	}
	return ((valid.errors == 0 && (fd >= 0 && fd <= 4096)) ? 1 : 0);
}

bool					ft_validate_input_file(char *file_name)
{
	if (file_name != NULL && ft_strlen(file_name))
	{
		if (!ft_strcmp(file_name + (ft_strlen(file_name) - 2), ".s"))
			return (true);
	}
	return (false);
}

bool					ft_write_to_stdout(char **arr)
{
	size_t		i;
	char		*str;

	str = ft_strnew(0);
	i = 0;
	while (arr[i])
	{
		ft_strdel(&str);
		str = ft_strip(arr[i]);
		if (!ft_strcmp(str, DUMP_FLAG))
		{
			return (false);
		}
		i++;
	}
	ft_strdel(&str);
	return (true);
}

int						main(int argc, char const *argv[])
{
	int			fd;

	if (argc > 1)
	{
		if (ft_validate_input_file((char*)argv[argc - 1]))
		{
			fd = open(argv[argc - 1], O_RDONLY);
			if (ft_validate(fd, (char*)argv[argc - 1]))
			{
				g_asm.prog_size = ft_count_prog_len();
				(!ft_write_to_stdout((char**)argv + 1)) ? ft_dump_info()
				: ft_write_file((char*)argv[argc - 1], g_asm.oper, NULL);
				return (0);
			}
		}
		else
			ft_exception("Wrong file extension.", 2);
	}
	else
	{
		ft_putendl("Usage: ./asm <sourcefile.s>");
		ft_exception("\t-a : Instead of creating a .cor file, outputs a \
		stripped and annotated version of the code to the standard output", 2);
	}
	return (1);
}
