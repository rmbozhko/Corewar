#include "op.h"
#include "asm.h"

int		skip_whitespaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '\t')
	{
		printf("PASSING CHARS:%s|%d\n", str + i, i);
		i++;
	}
	printf("CHAR TO BE RETURNED:%d|%s\n", i, str + i);
	return (i);
}

int 	ft_check_each_arg(int argument, int found_num, int seq_num)
{
	int 	arg_type;

	arg_type = op_tab[found_num].args[0][seq_num];
	printf("ARG_TYPE:%d|MY ARG:%d|%d\n", arg_type, argument, seq_num);
	if (arg_type == 1 && argument == 1)
		return (1);
	else if (arg_type == 2 && argument == 2)
		return (1);
	else if (arg_type == 3 && (argument == 2 || argument == 1))
		return (1);
	else if (arg_type == 4 && (argument == 4))
		return (1);
	else if (arg_type == 5 && (argument == 4 || argument == 1))
		return (1);
	else if (arg_type == 6 && (argument == 4 || argument == 2))
		return (1);
	else if (arg_type == 7 && (argument == 4 || argument == 2 || argument == 1))
		return (1);
	else
		return (0);
}

char		*ft_get_mltl_string(size_t i, size_t j, t_valid *valid)
{
	char		*temp;
	char		*str;
	char		*string;
	
	temp = ft_strdup("");
	string = temp;
	while (j < valid->line_num && valid->file[j] != NULL)
	{
		temp = ft_strjoin(temp, ft_strdup(valid->file[j] + i));
		ft_memdel((void**)&string);
		string = temp;
		i = 0;
		j++;
	}
	str = ft_strsub(valid->file[j], i, valid->i);
	temp = ft_strjoin(temp, str);
	ft_memdel((void**)&string);
	ft_memdel((void**)&str);
	return (temp);
}

void		ft_log_handle_dot(t_valid *valid, t_assembler *asml)
{
	char 		*temp;
	size_t		i;
	size_t		j;
	
	temp = ft_strsub(valid->file[valid->line_num], 0, ft_strlen(NAME_CMD_STRING));
	valid->i += ft_strlen((ft_strcmp(temp, NAME_CMD_STRING) == 0) ? NAME_CMD_STRING : COMMENT_CMD_STRING);
	valid->i += skip_whitespaces(valid->file[valid->line_num], valid->i);
	i = valid->i + 1;
	j = valid->line_num;
	ft_handle_double_qoutes(valid);
	if (ft_strcmp(temp, NAME_CMD_STRING) == 0)
		asml->name = ft_get_mltl_string(i, j, valid);
	else
		asml->cmmt = ft_get_mltl_string(i, j, valid);
	ft_memdel((void**)&temp);
	valid->i += ft_strlen(valid->file[valid->line_num] + valid->i);
}

size_t		ft_get_arg_type(char *str)
{
	if (str[0] == 'r' && ft_isdigit(str[1]))
		return (1);
	else if (str[0] == DIRECT_CHAR && str[1] == LABEL_CHAR)
		return (2);
	else if ((str[0] == '-' && ft_isdigit(str[1])) || ft_isdigit(str[0]) || str[0] == DIRECT_CHAR || str[0] == LABEL_CHAR)
		return (4);
	else
		return (0);
}

size_t		ft_handle_argument(char *str, int cmd_opcode, size_t arg_num)
{
	size_t		i;
	size_t		arg_type;
	
	i = 0;
	arg_type = ft_get_arg_type(str);
	printf("PASSED STR:%s|ARG_TYPE:%zu\n", str, arg_type);
	if (i >= op_tab[cmd_opcode].count_args)
	{
		ft_logical_error(i, arg_type, cmd_opcode, 1);
	}
	else if (arg_type)
	{
		printf("PASSED OVER HERE!!\n");
		if (ft_check_each_arg(arg_type, cmd_opcode, arg_num))
			return (8);
	}
	return (arg_type);
}



void		ft_log_handle_command(t_valid *valid, size_t j, char *str)
{
	int			cmd_opcode;
	char		**commands;
	size_t		i;
	size_t		arg_type;
	size_t		commas;

	commas = 0;
	cmd_opcode = ft_is_command(valid->file[valid->line_num]/* + valid->i*/, valid);
	valid->i += ft_strlen(op_tab[cmd_opcode].command_name);
	printf("CURR STR:%s AND cmd_opcode:%i|%zu\n", valid->file[valid->line_num] + valid->i, cmd_opcode, valid->i);
	valid->i = skip_whitespaces(valid->file[valid->line_num], valid->i);
	printf("CURR STR:%s|%zu\n", valid->file[valid->line_num] + valid->i, valid->i);
	j = valid->i;
	printf("CURR STR WITH FLAG:%s|%zu\n", valid->file[valid->line_num] + j, valid->i);
	while (valid->file[valid->line_num][valid->i])
	{
		printf("CURR CHAR IN ARG SEARCH:%c\n", valid->file[valid->line_num][valid->i]);
		if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR || valid->file[valid->line_num][valid->i] == COMMENT_CHAR2)
			break ;
		else if (valid->file[valid->line_num][valid->i] == SEPARATOR_CHAR)
			commas++;
		valid->i++;
	}
	printf("HOW ARE YOU!?!%zu|%d\n", commas, op_tab[cmd_opcode].count_args);
	if (commas + 1 < op_tab[cmd_opcode].count_args)
		ft_logical_error(0, 0, cmd_opcode, 1);
	else
	{
		printf("MOVING UP HERE!\n");
		i = 0;
		commands = ft_strsplit(valid->file[valid->line_num] + j, SEPARATOR_CHAR);
		while (commands[i])
		{
			ft_memdel((void**)&str);
			str = ft_strip(commands[i]);
			printf("ARGUMENT_TO_BE_VALIDATED:%s\n", str);
			if ((arg_type = ft_handle_argument(str, cmd_opcode, i)) != 8)
				ft_logical_error(i, arg_type, cmd_opcode, 0);
			i++;
		}
	}
	ft_memdel((void**)&str);
}

void		ft_logical_validation(t_valid *valid, t_assembler *asml)
{
	printf("HELLo I am here!\n");
	while (valid->file[valid->line_num])
	{
		valid->i = skip_whitespaces(valid->file[valid->line_num], 0);
		printf("CURR STRING TO BE HANDLED:%s\n", valid->file[valid->line_num]);
		while (valid->file[valid->line_num][valid->i])
		{
			if (valid->file[valid->line_num][valid->i] == NAME_CMD_STRING[0]
				|| valid->file[valid->line_num][valid->i] == COMMENT_CMD_STRING[0])
			{
				printf("I HAVE HANDLED DOT!%s|%zu\n", valid->file[valid->line_num] + valid->i, valid->line_num);
				ft_log_handle_dot(valid, asml);
				printf("AFTER I HAVE HANDLED DOT!%s|%zu|%zu|%zu\n", valid->file[valid->line_num] + valid->i, valid->line_num, ft_strlen(valid->file[valid->line_num]), valid->i);
			}
			else if (ft_is_command(valid->file[valid->line_num]/* + valid->i*/, valid) != -1)
			{
				ft_log_handle_command(valid, 0, ft_strnew(0));
			}
			else if (ft_is_label(valid))
			{
				printf("AND LABLE ASLO!\n");
				if (!ft_space_based_line(valid->file[valid->line_num] + valid->i))
				{
					valid->i = skip_whitespaces(valid->file[valid->line_num], valid->i);
					ft_log_handle_command(valid, 0, ft_strnew(0));
				}
			}
			else if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR2 || valid->file[valid->line_num][valid->i] == COMMENT_CHAR)
				break ;
			valid->i += (valid->file[valid->line_num][valid->i] != '\0') ? 1 : 0;
		}
		valid->line_num++;
	}
}