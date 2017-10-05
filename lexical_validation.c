#include "asm.h"
#include "op.h"

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

size_t		ft_skip_chars(char *str, int(*f)(int), int c)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (c != -1 && f == NULL)
		{
			if (str[i] != c)
				break ;
		}
		else if (c == -1 && f != NULL)
		{
			if (!f(str[i]))
				break ;
		}
		i++;
	}
	return (i);
}

char 		*ft_handle_double_qoutes(t_valid *valid)
{
	char 		*temp;
	size_t		i;
	int 		db_quote_flag;

	db_quote_flag = 1;
	temp = ft_strsub(valid->file[valid->line_num], valid->i + 1, ft_strlen(valid->file[valid->line_num]));
	printf("temp_string:%s | %zu | %zu\n", temp, ft_strlen(valid->file[valid->line_num]), valid->line_num);
	while (valid->file[valid->line_num])
	{
		i = 0;
		printf("TEMP_STRING_AT_THE_BEGINNING:%s | %zu\n", temp, ft_strlen(valid->file[valid->line_num]));
		while (temp[i] && db_quote_flag)
		{
			db_quote_flag = (temp[i] == '"') ? 0 : db_quote_flag;
			i++;
		}
		// Previously it was here!
		// if (temp[i] == '\0')
		// {
		// 	valid->line_num++;
		// 	valid->i = (db_quote_flag) ? 0 : valid->i;
		// }
		if (!db_quote_flag)
		{
			printf("I WAS HERE!%s\n", temp + i);
			break ;
		}
		if (temp[i] == '\0')
		{
			valid->line_num++;
			valid->i = (db_quote_flag) ? 0 : valid->i;
		}
		ft_memdel((void**)&temp);
		// valid->line_num++;
		temp = (valid->file[valid->line_num]) ? ft_strdup(valid->file[valid->line_num]) : temp;
	}
	printf("BEFORE VALID->I:%zu|%zu\n", valid->i, valid->line_num);
	valid->i += i;
	printf("AFTER VAlid->I:%zu\n", valid->i);
	if (valid->file[valid->line_num] == NULL)
		return (NULL);
	printf("UPDATED_STRING:%c\n", temp[i]);
	return ((temp[i] == '\0') ? NULL : temp);
}

size_t 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	i = ft_strlen(str);
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	else
		ft_lexical_err(valid);
	ft_memdel((void**)&str);
	return (i);
}

void 		ft_handle_dot(char *str, t_valid* valid)
{
	size_t		i;

	i = 1;
	if (ft_strstr(str, NAME_CMD_STRING))
	{
		i = ft_name_cmmt(str, 1, valid);
	}
	else if (ft_strstr(str, COMMENT_CMD_STRING))
	{
		i = ft_name_cmmt(str, 0, valid);
	}
	else
		ft_lexical_err(valid);
	valid->i += i;
}

size_t		ft_till_is_word(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == DIRECT_CHAR || str[i] == LABEL_CHAR || (str[i] == '-' && ft_isdigit(str[i + 1])))//(!ft_isdigit(str[i]) && ())
			break ;
		i++;
	}
	return (i);
}

int			ft_is_command(char *str, t_valid *valid)
{
	int			i;
	char 		*temp;
	char 		*string;//

	string = str;
	str = ft_lstrip(str);
	i = -1;
	printf("STRING COMMAND TEST CASE:%s\n", str);
	while (op_tab[++i].count_args != 0)
	{
		if (ft_strlen(str) >= ft_strlen(op_tab[i].command_name))
		{
			temp = ft_strsub(str, 0, ft_till_is_word(str)/*ft_skip_chars(str, ft_isalpha, -1)*/); //ld2: -> Not command
			printf("COMMAND TESTING:%s|%c\n", temp, str[ft_strlen(temp)]);
			if (ft_strcmp(temp, "live") == 0 && str[ft_strlen(temp)] == LABEL_CHAR)
			{
				printf("THAT'S IT!\n");
				break ;
			}
		}
		else
			continue ;
		if (ft_strcmp(temp, op_tab[i].command_name) == 0)
		{
			printf("TRUELY COMMAND STR:%s | %zu\n", str, valid->i);
			valid->i += ft_strlen(string) - ft_strlen(str);
			printf("AFTER ADDITION:%zu\n", valid->i);
			ft_memdel((void**)&str);
			return (i);
		}
		ft_memdel((void**)&temp);
	}
	printf("STR AS COMMAND:%s\n", str);
	return (-1);
}

// void		ft_check_label_chars(char *str, size_t end, t_valid *valid)
// {
// 	printf("%s | %zu | %zu\n",str + valid->i, end, valid->i);
// 	while (valid->i < end && str[valid->i])
// 	{
// 		// if (str[valid->i] == '"')
// 		// {
// 		// 	printf("%s | %zu | %zu\n",str + valid->i, end, valid->i);
// 		// 	if ((str = ft_handle_double_qoutes(valid)) == NULL)
// 		// 	{
// 		// 		break ;
// 		// 	}
// 		// }
// 		// else if (str[valid->i] == COMMENT_CHAR2 || str[valid->i] == COMMENT_CHAR)
// 		// 	break ;
// 		// else if (!ft_strchr(LABEL_CHARS, str[valid->i]) && str[valid->i] != SEPARATOR_CHAR && str[valid->i] != ' ' && str[valid->i] != '\t')
// 		// printf("CHAR AT ONE GLANCE:%c\n", str[valid->i]);
// 		printf("CHAR IN CYCLE:%c\n", str[valid->i]);
// 		if (!ft_strchr(LABEL_CHARS, str[valid->i])) //&& str[valid->i] != SEPARATOR_CHAR && str[valid->i] != ' ' && str[valid->i] != '\t')
// 		{
// 			// ft_lexical_err(valid);
// 			printf("CHAR CAUSES BREAK:%c\n", str[valid->i]);
// 			break ;
// 		}
// 		valid->i++;
// 	}
// 	printf("STRING IS HERE: %s | %zu | %zu\n",str + valid->i, end, valid->i);
// 	// if (str != NULL)
// 		// (!(str[valid->i] != '\0' && str[valid->i] != COMMENT_CHAR2 && str[valid->i] != COMMENT_CHAR)) ? valid->i = ft_strlen(str) : 0; // - 1 : 0;
// 	// valid->i += (str[valid->i] != '\0' && str[valid->i] != COMMENT_CHAR2 && str[valid->i] != COMMENT_CHAR) ? 0 : ft_strlen(str) - 1;
// 	// return (i);
// }

void		ft_check_label_chars(char *str, size_t end, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (i < end && str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]))
			break ;
		i++;
	}
	valid->i += i;
}

void 		ft_handle_label_declaration(char *str, t_valid* valid)
{
	size_t		distance;
	char 		*temp;

	temp = NULL;
	distance = ft_strlen(str);
	printf("WHAT THE FUCK IS GOING ON!%s|%zu\n", str + valid->i, distance);
	if (ft_strchr(str + valid->i, LABEL_CHAR))
	{
		printf("<<<<<<<<<<<<<<<||||||||||||||||||||||||||||||||>>>>>>>>>>>>>>>>>>>>>>@@@@@@@@@@@@@@@@@@@@@@@@@@@\n");
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str + valid->i, 0, distance + 1);
		printf("TEMP STRING IS OVER HERE:%s\n", temp);
	}
	if (ft_strchr(temp, COMMENT_CHAR) || ft_strchr(temp, '"') || ft_strchr(temp, COMMENT_CHAR2) || ft_strchr(temp, LABEL_CHAR) == NULL || ft_strchr(temp, DIRECT_CHAR))
	{
		printf("YO________-------_____________DC DRE!%s|%zu|%c\n", str + valid->i, distance, str[distance]);
		ft_check_label_chars(str, distance, valid);
		write(1, "OLA!\n", 5);
	}
	else
	{
		printf("SJDOASJDOISAJDOASJDOIJASDOIJA_____________!!!!@@#@!#!@#!@#\n");
		while (str[valid->i] && str[valid->i] != LABEL_CHAR)
		{
			// if (str[valid->i] == '"')
			// {
			// 	printf("QWERTT!!!!!!!!!\n");
			// 	if ((str = ft_handle_double_qoutes(valid)) == NULL)
			// 	{
			// 		write(1, "CO-PARTNER\n", 11);
			// 		break ;
			// 	}
			// 	else if (str[valid->i + 1] == LABEL_CHAR)
			// 	{
			// 		write(1, "COMRADE\n", 8);
			// 		ft_lexical_err(valid);
			// 	}
			// }
			// else if (!ft_strchr(LABEL_CHARS, str[valid->i]))
			if (!ft_strchr(LABEL_CHARS, str[valid->i]))
				((str[valid->i] == SEPARATOR_CHAR || str[valid->i] == ' ' || str[valid->i] == '\t') && str[valid->i + 1] != LABEL_CHAR) ? 0 : ft_lexical_err(valid);//, printf("?????????????????????????????????????????????????????\n");
			valid->i++;
		}
		if (str != NULL)
			valid->i += (str[valid->i] == '\0') ? 0 : 1;
	}
	printf("SASHA\n");
	(temp == NULL) ? 0 : ft_memdel((void**)&temp);
}

void 		ft_handle_label_invocation(char *str, t_valid* valid)
{
	// size_t		i;
	
	// i = 0;
	// while (str[i])
	// {
	// 	if (str[i] == '"' && i != 0)
	// 	{
	// 		if ((str = ft_handle_double_qoutes(valid)) == NULL)
	// 			break ;
	// 	}
	// 	else if ((str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR) && i != 0)
	// 		break ;
	// 	else if (!ft_strchr(LABEL_CHARS, str[i]))
	// 		((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && i != 0) ? 0 : ft_lexical_err(valid);
	// 	i++;
	// }
	// if (str != NULL)
	// 	valid->i += (str[i] == '\0') ? i : ft_strlen(str) - 1;
	// (i == 0) ? ft_lexical_err(valid) : 0;
	size_t		i;

	i = 0;
	printf(">>>>>>>>>>>>>>>>>>----------------<<<<<<%s\n", str);
	while (str[i])
	{
		if (!ft_strchr(LABEL_CHARS, str[i]) && !((str[i] == SEPARATOR_CHAR || str[i] == ' ' || str[i] == '\t') && i != 0))
		{
			break ;
		}
		i++;
	}
	valid->i += i;
	printf("CURRENT I AS INDEX IS:%zu\n", i);
	(i == 0) ? ft_lexical_err(valid) : 0;
}

size_t		ft_skip_hex_digits(char *str)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			if (str[i] == 'x' && ft_isdigit(str[i - 1]) && ft_isdigit(str[i + 1]))
				;
			else
				break ;
		}
		i++;
	}
	return (i);
}

size_t		ft_handle_indirect(char *str, t_valid *valid)
{
	if (str[valid->i] == DIRECT_CHAR && ((str[valid->i + 1] == '-' && ft_isdigit(str[valid->i + 2])) || ft_isdigit(str[valid->i + 1])))
	{
		valid->i += (str[valid->i + 1] == '-') ? 2 : 1;
		valid->i += ft_skip_hex_digits(str + valid->i);//ft_skip_chars(str + valid->i, ft_isdigit, -1);
		return (1);
	}
	else if (str[valid->i] == '-' && ft_isdigit(str[valid->i + 1]))
	{
		valid->i += 1;
		valid->i += ft_skip_hex_digits(str + valid->i);//ft_skip_chars(str + valid->i, ft_isdigit, -1);
		return (1);
	}
	else if (ft_isdigit(str[valid->i]))
	{
		printf("NUMBERS ARE FOUND!!!!!!!!!!!!!!!!!!!!valid->i:%zu\n", valid->i);
		valid->i += ft_skip_hex_digits(str + valid->i);//ft_skip_chars(str + valid->i, ft_isdigit, -1);
		printf("______________________AFTER SKIP________________!!!!!!!!!!!!valid->i:%zu\n", valid->i);
		return (1);
	}
	else
	{
		printf("ERROR MIGHT BE HERE!\n");
		return (0);
	}
}

void		ft_handle_register(char *str, t_valid *valid)
{
	size_t		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '-' && !ft_isdigit(str[i + 1]))
		{
			if (!ft_handle_indirect(str + i, valid))
				ft_lexical_err(valid);
		}
		else if ((str[i] == ' ' || str[i] == '\t') && str[i - 1] == '-')
		{
			printf("OR MAYBE ERROR IS HERE!!\n");
			ft_lexical_err(valid);
		}
		else if (str[i])
		i++;
	}
	valid->i += i;
}

void		ft_check_str_chars(char *str, t_valid *valid)
{
	int 		command_id;
	char 		*temp;

	// if (valid->file[valid->line_num] == NULL)
	// 	return ;
	temp = str;
	// str = ft_lstrip(str + valid->i);
	// valid->i += ft_strlen(temp) - ft_strlen(str);
	(str[valid->i] == '\0') ? ft_memdel((void**)&temp): 0;
	printf("STRING AT THE BEGINNING:%s\n", str + valid->i);
	if (str[valid->i] == NAME_CMD_STRING[0] || str[valid->i] == COMMENT_CMD_STRING[0])
	{
		printf("DOT CASE\n");
		ft_handle_dot(str + valid->i, valid);
	}
	else if (str[valid->i] == COMMENT_CHAR || str[valid->i] == COMMENT_CHAR2)
		valid->i += ft_strlen(str + valid->i);
	else if (str[valid->i] == '"')
	{
		str = ft_handle_double_qoutes(valid);
		if (str == NULL)
			return ;
		valid->i += 1;
	}
	else if ((command_id = ft_is_command(str + valid->i, valid)) != -1)
	{
		valid->i += ft_strlen(op_tab[command_id].command_name);
		printf("AND THAN HE JUST FUCKED UP!%zu | %zu\n", valid->i, ft_strlen(op_tab[command_id].command_name));
	}
	else if (str[valid->i] == DIRECT_CHAR && str[valid->i + 1] == LABEL_CHAR)
	{
		printf("I AM GODDAM HERE!\n");
		valid->i += 2;
		ft_handle_label_invocation(str + valid->i, valid);
	}
	else if (str[valid->i] == 'r')
	{
		printf("MOVING UP TO REGISTER!!!!!!!!!!!!\n");
		valid->i += ft_skip_chars(str + valid->i, NULL, 'r');
		// ft_handle_register(str + (++valid->i), valid);
	}
	else if ((str[valid->i] == '-' && ft_isdigit(str[valid->i + 1])) || ft_isdigit(str[valid->i]) || (str[valid->i] == DIRECT_CHAR))
	{
		printf("SMTH BAD GONNA HAPPEN!\n");
		(!ft_handle_indirect(str, valid)) ? ft_lexical_err(valid) : 0;
	}
	else if (str[valid->i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[valid->i]))
	{
		printf("MEHELAGENESCA!\n");
		printf("WHAT IS THERE:%c\n", str[valid->i]);
		(str[valid->i] == LABEL_CHAR) ? ft_handle_label_invocation(str + (++valid->i), valid)
										: ft_handle_label_declaration(str, valid);// : ft_handle_label_declaration(str + valid->i, valid);
	}
	else if (str[valid->i] == SEPARATOR_CHAR)
	{
		printf("MAYBE HERE, NO?!?!?!\n");
		valid->i += ft_skip_chars(str + valid->i, NULL, SEPARATOR_CHAR);
	}
	else
	{
		(str[valid->i] != ' ' && str[valid->i] != '\t') ? printf("ERROR TYPE%s\n", str + valid->i), ft_lexical_err(valid) : valid->i++;
	}
	printf("GOING FURTHER:%s\n", str + valid->i);
	// if (valid->file[valid->line_num + 1] == NULL &&  str[valid->i] == '\0')
		// return ;
	(str[valid->i] != '\0' /*&& (!valid->errors)*/ && valid->file[valid->line_num]) ? ft_check_str_chars(str, valid) : 0;
}

void		ft_lexical_validation(t_valid *valid)
{
	char 		*temp;

	temp = ft_strnew(0);
	ft_putbidstr(valid->file);
	while (valid->file[valid->line_num])
	{
		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->i = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		if (temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2 && !ft_spaces_based_line(temp))
		{
			printf("GO HERE!\n");
			ft_check_str_chars(valid->file[valid->line_num], valid);
		}
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}
