#include "op.h"
#include "asm.h"

t_labels		*ft_create_label(char *str, size_t	key)
{
	t_labels		*label;

	label = (t_labels*)malloc(sizeof(t_labels*));
	label->name = str;
	label->f_key = key;
	label->next = NULL;
	return (label);
}

t_labels		*ft_update_list(t_assembler *asml)
{
	t_labels		*label;

	label = *(asml->label);
	while (label)
		label = label->next;
	return (label);
}

char 			*ft_extract_value(char *arg)
{
	char 		*temp;

	if (arg[0] == 'r' && ft_isdigit(arg[1]))
	{
		temp = ft_strsub(arg, 1, ft_strlen(arg + 1));
	}
	else if ((arg[0] == '-' && ft_isdigit(arg[1])) || ft_isdigit(arg[0]) || (arg[0] == DIRECT_CHAR))
	{
		temp = ft_strsub(arg, ((arg[0] == DIRECT_CHAR) ? 1 : 0), ft_strlen(arg + ((arg[0] == DIRECT_CHAR) ? 1 : 0)));
	}
	else
		printf("WHAT ARGUMENT I HAVEn'T VALIDATED?!?!?!?:%s\n", arg);
	return (temp);
}

t_arg			*ft_create_arg(char *arg)
{
	t_arg		*argument;

	argument = (t_arg*)malloc(sizeof(t_arg*));
	argument->type = ft_get_arg_type(arg);
	if ((arg[0] == DIRECT_CHAR && arg[1] == LABEL_CHAR) || (arg[0] == LABEL_CHAR))
	{
		argument->label = ft_strsub(arg, ((arg[0] == LABEL_CHAR) ? 1 : 2), ft_strlen(arg + ((arg[0] == LABEL_CHAR) ? 1 : 2)));
		argument->value = NULL;
	}
	else
	{
		argument->value = ft_extract_value(arg);
		argument->label = NULL;
	}
	return (argument);
}

t_operations	*ft_create_command(char *str, char *arguments)
{
	t_operations		*oper;
	size_t				i;
	char 				**args;
	char 				*temp;

	i = 0;
	oper = (t_operations*)malloc(sizeof(t_operations*));
	oper->command = str;
	args = ft_strsplit(arguments, SEPARATOR_CHAR);
	while (i < ARG_MAX_NUM && args[i])
	{
		temp = ft_strip(args[i]);
		oper->args[i] = *(ft_create_arg(temp));
		ft_memdel((void**)&temp);
		i++;
	}
	oper->next = NULL;
	return (oper);
}

t_operations	*ft_handle_command(t_valid *valid, t_assembler *asml)
{
	int 				cmd_id;
	t_operations		*oper;

	oper = NULL;
	if ((cmd_id = ft_is_command(valid->file[valid->line_num] + valid->i, valid)) != -1)
	{
		valid->i += ft_strlen(op_tab[cmd_id].command_name);
		valid->i = skip_whitespaces(valid->file[valid->line_num], valid->i);
		ft_putstr("Oh nO!!!oh NO!\n");
		ft_putstr(valid->file[valid->line_num] + valid->i);
		oper = ft_create_command(op_tab[cmd_id].command_name, valid->file[valid->line_num] + valid->i);
		asml->instr_counter++;
		ft_putstr("\nOh YES!!!!!!!!!!!oh YES!!!!!!!!!:)!\n");
		ft_putstr(valid->file[valid->line_num] + valid->i);
		ft_putstr("\nGAME IS OVER!\n");
		printf("COMMAND NAME OF OPER:%s\n", oper->command);
	}
	return (oper);
}

t_operations	*ft_get_command(t_valid *valid, t_assembler *asml)
{
	t_operations		*oper;

	oper = NULL;
	while (valid->file[valid->line_num])
	{
		valid->i = skip_whitespaces(valid->file[valid->line_num], valid->i);
		while (valid->file[valid->line_num][valid->i])
		{
			if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR || valid->file[valid->line_num][valid->i] == COMMENT_CHAR2)
				break ;
			else if (valid->file[valid->line_num][valid->i] != ' ' && valid->file[valid->line_num][valid->i] != '\t')
			{
				oper = ft_handle_command(valid, asml);
				if (oper)
					break ;
			}
			valid->i++;
		}
		valid->line_num++;
	}
	return (oper);
}

t_labels		*ft_gather_label(t_valid *valid, t_assembler *asml, char *temp)
{
	size_t				i;
	t_labels			*label;
	t_operations		*oper;

	i = valid->i;
	if (ft_is_label(valid))
	{
		ft_memdel((void**)&temp);
		temp = ft_strsub(valid->file[valid->line_num], i, valid->i - 1);
		ft_putstr("Ta-DA\n");
		if (!ft_space_based_line(valid->file[valid->line_num] + valid->i))
		{
			ft_putstr("MeoW!\n");
			// printf("*****************@@@@@***********\n");
			valid->i = skip_whitespaces(valid->file[valid->line_num], valid->i);
			ft_putstr("------------------------------");
			ft_putstr(valid->file[valid->line_num] + valid->i);
			oper = ft_handle_command(valid, asml);
		}
		else
		{
			ft_putstr("Woof-woof!\n");
			// printf("MOVE ON!!!!!!!!!!!!!!!!\n");
			oper = ft_get_command(valid, asml);
			printf("COMMAND NAME OF OPER:%s\n", oper->command);
		}
		label = ft_create_label(temp, asml->instr_counter);
		printf("LEt's ROCKCKCKCK!+++)_\n");
		ft_putstr(label->name);
		ft_memdel((void**)&temp);
		return (label);
	}
	ft_memdel((void**)&temp);
	return (NULL);
}

void		ft_print_links(t_labels		**arg)
{
	t_labels		*link;

	link = *arg;
	printf("%s\n", link->name);
	// while (link)
	// {
	// 	ft_putstr(link->name);
	// 	link = link->next;
	// 	ft_putchar('\n');
	// }
}

void		ft_gather_commands(t_valid *valid, t_assembler *asml)
{
	t_labels		*label;
	t_operations	*oper;

	label = *(asml->label);
	oper = *(asml->oper);
	// printf("|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
	while (valid->file[valid->line_num])
	{
		valid->i = skip_whitespaces(valid->file[valid->line_num], 0);
		while (valid->file[valid->line_num][valid->i])
		{
			if (ft_is_command(valid->file[valid->line_num] + valid->i, valid) != -1)
			{
				// ft_putstr("OLA!!\n");
				oper = ft_handle_command(valid, asml);
				oper = oper->next;
			}
			else if (ft_strchr(LABEL_CHARS, valid->file[valid->line_num][valid->i]))
			{
				if ((label = ft_gather_label(valid, asml, ft_strnew(0))) != NULL)
					label = label->next;
			}
			else if (valid->file[valid->line_num][valid->i] == COMMENT_CHAR2 || valid->file[valid->line_num][valid->i] == COMMENT_CHAR)
				break ;
			valid->i += (valid->file[valid->line_num][valid->i] != '\0') ? 1 : 0;
		}
		valid->line_num++;
	}
	// printf("\n\n\n\n\n\nLET's see what we have got\n");
	// ft_print_links(asml->label);
	// ft_print_links((void*)oper);
}