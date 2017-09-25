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

char 		*ft_handle_double_qoutes(size_t *index, t_valid *valid)
{
	char 		*temp;
	size_t		i;
	int 		db_quote_flag;

	db_quote_flag = 1;
	ft_putnbr(*index);
	write(1, "ALOHA\n", 6);
	ft_putnbr(ft_strlen(valid->file[valid->line_num]) - (*index + 1));
	ft_putstr(valid->file[valid->line_num]);
	temp = ft_strsub(valid->file[valid->line_num], *index + 1, ft_strlen(valid->file[valid->line_num]) - (*index + 1));
	while (valid->file[valid->line_num])
	{
		i = 0;
		while (temp[i] && db_quote_flag)
		{
			db_quote_flag = (temp[i] == '"') ? 0 : db_quote_flag;
			// if (temp[i] == COMMENT_CHAR || temp[i] == COMMENT_CHAR2)
				// break ;
			i++;
		}
		if (!db_quote_flag)
			break ;
		ft_memdel((void**)&temp);
		valid->line_num++;
		temp = (valid->file[valid->line_num]) ? ft_strdup(valid->file[valid->line_num]) : temp;
	}
	printf("YO_MA_NIgga!%i\n", i);
	*index = (temp[i] == '\0') ? 0 : i - 1;
	printf("INDEX:%zu\n", i);
	return ((temp[i] == '\0') ? NULL : temp);
}

void 		ft_name_cmmt(char *line, int flag, t_valid *valid)
{
	char		*str;
	size_t		i;

	str = ft_strsub(line, 0, ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING));
	if (ft_strcmp(((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING), str) == 0)
	{
		i = ft_strlen((flag) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
		while (line[i])
		{
			if (line[i] == '"')
			{
				if ((line = ft_handle_double_qoutes(&i, valid)) == NULL)
					break ;
			}
			else if (line[i] == COMMENT_CHAR || line[i] == COMMENT_CHAR2)
				break ;
			else if (!ft_strchr(LABEL_CHARS, line[i]) && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != SEPARATOR_CHAR)
				ft_lexical_err(valid->line_num, i, valid);
			i++;
		}
	}
	else
		ft_lexical_err(valid->line_num, 0, valid);
	ft_memdel((void**)&str);
}

void 		ft_handle_dot(char *str, t_valid* valid)
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
		ft_lexical_err(valid->line_num, 0, valid);
}

int			ft_is_command(char *str)
{
	int			i;
	char 		*temp;

	i = -1;
	while (op_tab[++i].count_args != 0)
	{
		if (ft_strlen(str) >= ft_strlen(op_tab[i].command_name))
			temp = ft_strsub(str, 0, ft_strlen(op_tab[i].command_name));
		else
			continue ;
		if (ft_strcmp(temp, op_tab[i].command_name) == 0)
		{
			ft_memdel((void**)&temp);
			return (1);
		}
		ft_memdel((void**)&temp);
	}
	return (0);
}

void		ft_check_label_chars(char *str, size_t end, t_valid *valid)
{
	size_t		i;

	i = 0;
	write(1, "TA-DA\n", 6);
	while (i < end && str[i])
	{
		if (str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR)
			break ;
		else if (!ft_strchr(LABEL_CHARS, str[i]) && str[i] != SEPARATOR_CHAR)
			ft_lexical_err(valid->line_num, i, valid);
		i++;
	}
}

void 		ft_handle_label_declaration(char *str, t_valid* valid)
{
	size_t		i;
	size_t		distance;
	char 		*temp;

	temp = NULL;
	distance = ft_strlen(str);
	if (ft_strchr(str, LABEL_CHAR) && !(i = 0))
	{
		distance = ft_strchr(str, LABEL_CHAR) - str;
		temp = ft_strsub(str, 0, distance + 1);
	}
	if (ft_strchr(temp, COMMENT_CHAR) || ft_strchr(temp, COMMENT_CHAR2) || ft_strchr(temp, LABEL_CHAR) == NULL)
	{
		write(1, "OLA\n", 4);
		ft_putnbr(distance);
		// ft_putstr(temp + distance);
		// printf("_____________----------__________%d%s\n", distance, temp + distance);
		ft_check_label_chars(str, distance, valid);
	}
	else
	{
		while (str[i] && str[i] != LABEL_CHAR)
		{
			// if (str[i] == '"')
			// {
			// 	if ((str = ft_handle_double_qoutes(&i, valid)) == NULL)
			// 		break ;
			// }
			// else if (!ft_strchr(LABEL_CHARS, str[i])) // additional not-allowed chars -> #,."lol"
			if (!ft_strchr(LABEL_CHARS, str[i]))
				(str[i + 1] == LABEL_CHAR || str[i + 1] == '\0') ? ft_lexical_err(valid->line_num, i, valid) : 0; // ft_lexical_err(valid->line_num, i, valid);
			i++;
		}
		// living_life:	ld 1, r09 -> chars after LABEL_CHAR should also be validated
	}
	(temp == NULL) ? 0 : ft_memdel((void**)&temp);
}

void 		ft_handle_label_invocation(char *str, t_valid* valid)
{
	size_t		i;
	
	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if ((str = ft_handle_double_qoutes(&i, valid)) == NULL)
				break ;
		}
		else if (str[i] == COMMENT_CHAR2 || str[i] == COMMENT_CHAR)
			break ;
		// else if (!ft_strchr(LABEL_CHARS, str[i]) && str[i] != ' ' && str[i] != '\t' && str[i] != SEPARATOR_CHAR)
		else if (!ft_strchr(LABEL_CHARS, str[i]))
		{
			printf("AND CURRENT ERROR IS - %c\n", str[i]);
			ft_lexical_err(valid->line_num, i, valid);
		}
		i++;
	}
	(i == 0) ? ft_lexical_err(valid->line_num, 0, valid) : 0;
}

void		ft_handle_command(char *command, t_valid *valid)
{
	printf("Current line is command:%s\n", command);
}

// void		ft_check_str_chars(char *str, t_valid *valid)
// {
// 	size_t		i;

// 	i = 1;
// 	printf("STR:%s\n", str);
// 	if (str[0] == '"')
// 	{
// 		ft_handle_double_qoutes(&i, valid);
// 		i += 3;
// 		printf("Current_index:%zu%s\n", i, str + i);
// 		if (str[i] != '\0')
// 			ft_check_str_chars(str + i, valid);
// 	}
// 	else if (ft_is_command(str))
// 		ft_handle_command(str, valid);
// 	else if (str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
// 	{
// 		printf("______________---------________________----------______\n");
// 		ft_handle_label_invocation(str + 2, valid);
// 	}
// 	else if (str[0] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[0]))
// 	{
// 		printf("YO, Line is in da club:%s\n", str);
// 		(str[0] == LABEL_CHAR) ? ft_handle_label_invocation(str + 1, valid) :  ft_handle_label_declaration(str, valid);
// 	}
// 	else if (str[0] == SEPARATOR_CHAR)
// 		;//handle SEPARATOR_CHAR at the beginning of the string but then can be other chars
// 	else
// 		ft_lexical_err(valid->line_num, 0, valid);
// }

void		ft_check_str_chars(char *str, size_t i, t_valid *valid)
{
	// size_t		i;

	// i = 1;
	printf("STR:%s | %zu\n", str, i);
	if (str[i] == '"')
	{
		ft_handle_double_qoutes(&i, valid);
		i += 2;
		printf("Current_index:%zu%s\n", i, str + i);
		// if (str[i] != '\0')
		// {
		// 	printf("Moving HERE!\n");
		// 	ft_check_str_chars(str, i, valid);
		// }
	}
	else if (ft_is_command(str))
	{
		printf("ATTENTION!__________________________________----------------------------------------------------------________________________COMMAND!??????????????????////////\n");
		ft_handle_command(str, valid);
	}
	else if (str[i] == DIRECT_CHAR && str[i + 1] == LABEL_CHAR)
	{
		printf("DIRECT_CHAR______________---------________________----------______LABEL_CHAR\n");
		ft_handle_label_invocation(str + i + 2, valid);
	}
	else if (str[i] == LABEL_CHAR || ft_strchr(LABEL_CHARS, str[i]))
	{
		printf("YO, Line is in da club:%s\n", str);
		(str[i] == LABEL_CHAR) ? ft_handle_label_invocation(str + i + 1, valid) :  ft_handle_label_declaration(str + i, valid);
	}
	else if (str[i] == SEPARATOR_CHAR)
	{
		i++;//handle SEPARATOR_CHAR at the beginning of the string but then can be other chars
		printf("SEPARATOR_CHAR is here %c\n", str[i]);
		// ft_check_str_chars(str, i, valid);
	}
	else
		ft_lexical_err(valid->line_num, 0, valid);
	(str[i] != '\0') ? ft_check_str_chars(str, i, valid) : 0;
}

void		ft_lexical_validation(t_valid *valid)
{
	char 		*temp;

	temp = ft_strnew(0);
	while (valid->file[valid->line_num])
	{
		// printf("Line:%s\n", valid->file[valid->line_num]);
		ft_memdel((void**)&temp);
		temp = ft_lstrip(valid->file[valid->line_num]);
		valid->left_offset = ft_strlen(valid->file[valid->line_num]) - ft_strlen(temp);
		if (temp[0] == NAME_CMD_STRING[0] || temp[0] == COMMENT_CMD_STRING[0])
			ft_handle_dot(temp, valid);
		else if (temp[0] != COMMENT_CHAR && temp[0] != COMMENT_CHAR2 && !ft_spaces_based_line(temp))
			ft_check_str_chars(temp, 0, valid);
		valid->line_num++;
	}
	ft_memdel((void**)&temp);
}
