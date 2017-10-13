#include "asm.h"
#include "op.h"

size_t		ft_handle_label_reference(char *str, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			printf("OH, NO!!!! IT IS ERROR:\'%c\'|%zu\n", str[i], i);
			break ;
		}
		i++;
	}
	valid->i += i;
	return ((i > 0) ? 1 : 0);
}

void		ft_handle_null_err_description(t_valid *valid)
{
	size_t		i;
	char 		*temp;
	size_t		j;

	i = valid->i;
	printf("COUNTER BEFORE %zu\n", valid->i);
	if (ft_strchr(LABEL_CHARS, valid->file[valid->line_num][valid->i]))
				ft_handle_label_reference(valid->file[valid->line_num] + valid->i, valid);
	else if ()
		
	printf("COUNTER AFTER %zu\n", valid->i);
	temp = ft_strsub(valid->file[valid->line_num], i, valid->i - i);
	j = valid->i;
	valid->i = i;
	ft_handle_repeating_error("INSTRUCTION", temp, valid);
	valid->i = j;
}

void		ft_syntax_error(t_valid *valid, char *error_description)
{
	if (valid->errors == 0)
	{
		if (error_description)
		{
			ft_putstr("Syntax error at [");
			ft_putnbr(valid->line_num + 1);
			ft_putchar(':');
			ft_putnbr(valid->i + 1);
			ft_putstr("] ");
			ft_putstr(error_description);
			ft_putchar('\n');
		}
		else
		{
			printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<ERROR %s|%c|%zu\n", valid->file[valid->line_num] + valid->i,
																		valid->file[valid->line_num][valid->i+2], valid->i);
			ft_handle_null_err_description(valid);
		}
	}
	valid->errors += (error_description) ? 1 : 0;
}

void		ft_handle_repeating_error(char *str, char *temp, t_valid *valid)
{
	char 	*string;
	char 	*direct_str;

	string = "";
	string = ft_strjoin(string, str);
	direct_str = string;
	string = ft_strjoin(string , " \"");
	ft_memdel((void**)&direct_str);
	direct_str = string;
	string = ft_strjoin(string, temp);
	ft_memdel((void**)&direct_str);
	direct_str = string;
	string = ft_strjoin(string, "\"");
	ft_memdel((void**)&direct_str);
	direct_str = string;
	ft_syntax_error(valid, string);
	ft_memdel((void**)&direct_str);
}

size_t		ft_is_gen_info_repeating(char *str, t_valid *valid)
{
	char 	*temp;
	

	temp = ft_strsub(str, 0, ft_strlen((ft_strstr(str, NAME_CMD_STRING)) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(temp, NAME_CMD_STRING) == 0)
	{
		if (valid->name)
			ft_handle_repeating_error((char*)NAME_CMD_STRING, temp, valid);
		valid->name = 1;
	}
	else if (ft_strcmp(temp, COMMENT_CMD_STRING) == 0)
	{
		if (valid->cmmt)
			ft_handle_repeating_error((char*)COMMENT_CMD_STRING, temp, valid);
		valid->cmmt = 1;
	}
	return (ft_strlen(temp));
}

char 		*ft_syn_handle_dot(char *str, t_valid *valid)
{
	int		double_qoute_counter;

	double_qoute_counter = 0;
	valid->i += ft_is_gen_info_repeating(str, valid);
	printf("STRING IN DOT CASE HANDLING:%s\n", str + valid->i);
	while (str[valid->i])
	{
		if (str[valid->i] == '"' && double_qoute_counter == 0)
		{
			if ((str = ft_handle_double_qoutes(valid)) == NULL)
				break ;
			double_qoute_counter = 1;
		}
		else if (str[valid->i] == COMMENT_CHAR || str[valid->i] == COMMENT_CHAR2)
		{
			if (double_qoute_counter != 1)
				ft_syntax_error(valid, "ENDLINE");
			break ;
		}
		else if (str[valid->i] != ' ' && str[valid->i] != '\t')
			ft_syntax_error(valid, NULL);
		valid->i++;
	}
	return (str);
}

void		ft_check_gen_info(t_valid *valid)
{
	char		*temp;

	temp = ft_strnew(0);
	while (valid->file[valid->line_num] && (!valid->name || !valid->cmmt))
	{
		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->i = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		printf("YO, ANY PROBLEMS PRICKS!?\n");
		while (valid->file[valid->i])
		{
			if (valid->file[valid->line_num][valid->i] == NAME_CMD_STRING[0]
				|| valid->file[valid->line_num][valid->i] == COMMENT_CMD_STRING[0])
			{
				printf("STRING WITH DOT CASE:%s\n", valid->file[valid->line_num] + valid->i);
				if (ft_syn_handle_dot(valid->file[valid->line_num] + valid->i, valid) == NULL)
				{
					printf("YOYOYOYOYOUYO)&@(*&*(!@!\n");
					break ;
				}
				printf("Alah akbar!\n");
			}
			else if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR2 || valid->file[valid->line_num][valid->i] == COMMENT_CHAR)
				break ;
			else if (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t')
			{
				printf("STRING WITH TROUBLES!!!!!!!!!!!%c\n", valid->file[valid->line_num][valid->i]);
				ft_syntax_error(valid, NULL);
			}
			valid->i++;
		}
		valid->line_num++;
	}
	printf("END OF HEADER PART:%zu\n", valid->line_num);
	ft_memdel((void**)&temp);
}

int			ft_find_operations(t_valid *valid)
{
	size_t		i;
	size_t		j;

	i = valid->line_num;
	while (valid->file[i])
	{
		j = 0;
		while (valid->file[i][j])
		{
			if ((ft_is_command(valid->file[i] + j, valid) != -1))
				return (1);
		}
		i++;
	}
	return (0);
}

size_t		ft_handle_register(t_valid *valid)
{
	size_t		i;
	size_t		num_counter;
	char 		*temp;

	temp = NULL;
	num_counter = 1;
	while (valid->file[valid->line_num][valid->i])
	{
		if (!ft_isdigit(valid->file[valid->line_num][valid->i]))
			break ;
		else
			num_counter++;
		valid->i++;
	}
	temp = ft_strsub(valid->file[valid->line_num], 0, num_counter - 1);
	i = ft_atoi(temp);
	ft_memdel((void**)&temp);
	return (i > REG_NUMBER) ? (0) : (1);

}	

size_t		ft_is_valid_param(t_valid *valid)
{
	size_t		i;

	printf("CURRENT_PARAM IS %s\n", valid->file[valid->line_num] + valid->i);
	if (valid->file[valid->line_num][valid->i] == 'r'
		&& (valid->file[valid->line_num][valid->i - 1] == ' ' || valid->file[valid->line_num][valid->i - 1] == '\t')
		&& ft_isdigit(valid->file[valid->line_num][valid->i + 1]))
	{
		valid->i++;
		return (ft_handle_register(valid));
	}
	else if ((valid->file[valid->line_num][valid->i] == DIRECT_CHAR && valid->file[valid->line_num][valid->i + 1] == LABEL_CHAR) || (valid->file[valid->line_num][valid->i] == LABEL_CHAR))
	{
		printf("YO, I've found SOME REFERENCING!%s\n", valid->file[valid->line_num] + valid->i);
		valid->i += (valid->file[valid->line_num][valid->i] == LABEL_CHAR) ? 1 : 2;
		printf("YO, I've found SOME REFERENCING!%s\n", valid->file[valid->line_num] + valid->i);
		return (ft_handle_label_reference(valid->file[valid->line_num] + valid->i, valid));
	}
	else if ((valid->file[valid->line_num][valid->i] == '-' && ft_isdigit(valid->file[valid->line_num][valid->i + 1]))
		|| ft_isdigit(valid->file[valid->line_num][valid->i]) || valid->file[valid->line_num][valid->i] == DIRECT_CHAR)
	{
		printf("GODDAM WE HAVE MOVED OVER HERE!\n");
		return (ft_handle_indirect(valid->file[valid->line_num], valid));
	}
	else if (valid->file[valid->line_num][valid->i] == 'r' && (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t'))
		return (2);
	else
		return (0);
}

size_t		ft_to_separator(t_valid *valid)
{
	while (valid->file[valid->line_num][valid->i])
	{
		if (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t')
		{
			if (valid->file[valid->line_num][valid->i] == SEPARATOR_CHAR)
				break ;
			else
				ft_syntax_error(valid, NULL);
		}
		valid->i++;
	}
	if (valid->file[valid->line_num][valid->i] == SEPARATOR_CHAR)
	{
		if (valid->file[valid->line_num][valid->i + 1] == '\0' ||
			ft_space_based_line(valid->file[valid->line_num] + (valid->i + 1)))
		{
			ft_syntax_error(valid, "ENDLINE");
		}
		else
			return (1);
	}
	return (0);
}

void		ft_handle_instr_invoke(char *str, t_valid *valid)
{
	// char 		*temp;

	// temp = ft_lstrip(valid->file[valid->line_num][valid->i]);
	// valid->i += ft_strlen(valid->file[valid->line_num] + valid->i) - ft_strlen(temp);
	// ft_memdel(temp);
	size_t		i;
	short int 	flag;

	flag = 1;
	while (/*valid->file[valid->line_num]*/str[valid->i] && flag)
	{
		if ((i = ft_is_valid_param(valid)) && flag)
		{
			printf("ARGUMENT HAS PASSED!%s|%i\n", /*valid->file[valid->line_num]*/str + valid->i, flag);
			flag = ft_to_separator(valid);
			printf("RENEWED VALUE OF FLAG:%i\n", flag);
		}
		else if (/*valid->file[valid->line_num]*/str[valid->i] != ' ' && /*valid->file[valid->line_num]*/str[valid->i] != '\t')
		{
			printf("///////////////////////////////////////////////\n");
			ft_syntax_error(valid, NULL);
		}
		if (i == 2)
			break ;
		valid->i++;
	}
	printf("73647236478236482364871209810937726478628091-9§1-920-§91-209§1-209-§012-§912-0woaps[;'Z/\'/`\'Z/A'/Z'''/'/''/'/'/'/'/'\n");
}

void		ft_syn_handle_instr(char *str, t_valid *valid)
{
	size_t		i;

	i = valid->i;
	while (str[valid->i])
	{
		if (!ft_strchr(LABEL_CHARS, str[valid->i]))
			break ;
		valid->i++;
	}
	printf("AFtER LOOPING THROUGH LABEL_CHARS:%s\n", str + valid->i);
	if (str[valid->i] != '\0')
	{
		ft_handle_instr_invoke(valid->file[valid->line_num], valid);
		printf("CHARS AFTER PARAMS_HANDLING:%s\n", str + valid->i);
		valid->i = i;
		ft_syntax_error(valid, NULL);
		valid->i += ft_strlen(valid->file[valid->line_num] + valid->i);
	}
	else if (ft_space_based_line(str + valid->i) || str[valid->i] == '\0')
		ft_syntax_error(valid, "ENDLINE");
}

void		ft_syn_handle_label(t_valid *valid)
{
	int 		cmd_num;

	cmd_num = 1;
	while (valid->file[valid->line_num][valid->i])
	{
		printf("MOVING ALONG!%c\n", valid->file[valid->line_num][valid->i]);
		if ((cmd_num = ft_is_command(valid->file[valid->line_num] + valid->i, valid)) != -1)
		{
			printf("IT IS REALLY A CMD?!%zu\n", valid->i);
			valid->i += ft_strlen(op_tab[cmd_num].command_name);
			printf("IT IS REALLY A CMD?!%zu\n", valid->i);
			ft_handle_instr_invoke(valid->file[valid->line_num], valid);
		}
		else if (ft_strchr(LABEL_CHARS, valid->file[valid->line_num][valid->i]))
		{
			printf("INSTRUCtION CHARS ARE FOUND!\n");
			ft_syn_handle_instr(valid->file[valid->line_num], valid);
			printf("INSTRUCtION STR:%s\n", valid->file[valid->line_num] + valid->i);
		}
		else if (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t')
			ft_syntax_error(valid, NULL);
		valid->i += (valid->file[valid->line_num][valid->i]) ? 1 : 0;
	}
}

size_t		ft_is_label(t_valid *valid)
{
	size_t		i;

	i = valid->i;
	while (valid->file[valid->line_num][valid->i])
	{
		if (valid->file[valid->line_num][valid->i] != LABEL_CHAR
			&& !ft_strchr(LABEL_CHARS, valid->file[valid->line_num][valid->i]))
		{
			valid->i = i;
			return (0);
		}
		else if (valid->file[valid->line_num][valid->i] == LABEL_CHAR)
		{
			valid->i++;
			break ;
		}
		valid->i++;
	}
	return (1);
}

void		ft_check_main_body(t_valid *valid)
{
	char		*temp;
	int 		cmd_num;

	temp = ft_strnew(0);
	cmd_num = -1;
	printf("_______________-------____________________++++++++++++++++++=========+++++++++++++++++++++++++++++++!@@#!@#!@#!@|%zu|%zu\n", ft_bidlen(valid->file), valid->line_num);
	while (valid->file[valid->line_num])
	{

		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->i = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		while (valid->file[valid->line_num][valid->i])
		{
			printf("LINE OF MAIN BODY:%s\n", valid->file[valid->line_num] + valid->i);
			if ((cmd_num = ft_is_command(valid->file[valid->line_num] + valid->i, valid)) != -1)
			{
				valid->i += ft_strlen(op_tab[cmd_num].command_name);
				ft_handle_instr_invoke(valid->file[valid->line_num], valid);
				printf("I AM HERE OR UP THERE!\n");
			}
			else if (ft_is_label(valid))
			{
				printf("HERE WE CAN FIND LABEL:%s\n", valid->file[valid->line_num] + valid->i);
				if (!ft_space_based_line(valid->file[valid->line_num] + valid->i))
				{
					printf("WE THAN CAN MOVE FURTHER!>>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<>>>>>>>>\n");
					ft_syn_handle_label(valid);
				}
				else
					break ;
			}
			else if (ft_strchr(LABEL_CHARS, valid->file[valid->line_num][valid->i]))
				ft_syn_handle_instr(valid->file[valid->line_num], valid);
			else if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR2 || valid->file[valid->line_num][valid->i] == COMMENT_CHAR)
				break ;
			else if (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t')
				ft_syntax_error(valid, NULL);
			valid->i++;
		}
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}

void 		ft_syntax_validation(t_valid* valid)
{
	valid->i = 0;
	valid->line_num = 0;
	printf("_________-------------<<<<<<<<<<<<<<<<<<<>>>>>>>>>>>>>>><<<<<<<<<<<>>>>>>>>>>>>>############$$$$$$$$$$##############\n");
	ft_check_gen_info(valid);
	if (!valid->file[valid->line_num] /*&& !ft_find_operations(valid)*/) // -> find another way to determine whether further we can find any predefined commands.
		ft_syntax_error(valid, "END \"(null)\"");
	printf("HOW ARE YOU!\n");
	ft_check_main_body(valid);
	printf("LET'S ROCK BITCHY!!!!!!!!!!!_+_+_+_+_+_+_+_+_+_+_+_+_");
}