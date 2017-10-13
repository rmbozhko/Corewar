int 	compare_command(char *str)
{
	int 	i;

	i = 0;
	while (i < 16)
	{
		if(ft_strcmp(str, op_tab[i].name) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int		skip_whitespaces(char *str, int i)
{
	while (str[i] == ' ' || str[i] == '	')
		i++;
	return (i);
}

int		check_if_reg(char *str)
{
	int 	i;

	i = 0;
	i = skip_whitespaces(str, i);
	if (str[i] != 'r')
		return (-1);
	else
		return (1);
}

int		check_if_dir(char *str)
{
	int 	i;

	i = 0;
	i = skip_whitespaces(str, i);
	if (str[i] != DIRECT_CHAR)
		return (-1);
	else
		return (1);
}

int		check_if_ind(char *str)
{
	int 	i;

	i = 0;
	i = skip_whitespaces(str, i);
	if (str[i] == LABEL_CHAR || (str[i] >= '0' && str[i] <= '9'))
		return (1);
	else
		return (-1);
}

int 	check_each_arg(char *str, int found_num, int seq_num)
{
	int 	arg_type;

	arg_type = op_tab[found_num].arg[seq_num];
	if (arg_type == 1)
	{
		if (check_if_reg(str) == 1)
			return (1);
	}
	else if (arg_type == 2)
	{
		if (check_if_dir(str) == 1)
			return (1);
	}
	else if (arg_type == 3)
	{
		if (check_if_dir(str) == 1 || check_if_reg(str) == 1)
			return (1);
	}
	else if (arg_type == 4)
	{
		if (check_if_ind(str) == 1)
			return (1);
	}
	else if (arg_type == 5)
	{
		if (check_if_ind(str) == 1 || check_if_reg(str) == 1)
			return (1);
	}
	else if (arg_type == 6)
	{
		if (check_if_ind(str) == 1 || check_if_dir(str) == 1)
			return (1);
	}
	else if (arg_type == 7)
	{
		if (check_if_ind(str) == 1 || check_if_dir(str) == 1 || check_if_reg(str) == 1)
			return (1);
	}
	return (-1);
}

int 	parse_args(char *str, int found_num)
{
	int 	i;
	int 	comma;
	char 	**args;

	i = 0;
	comma = 0;
	while (str[i])
	{
		if (str[i] == SEPARATOR_CHAR)
			comma++;
		i++;
	}
	if (comma + 1 != op_tab[found_num].count_arg)
		return (-1);
	args = ft_strsplit(str, SEPARATOR_CHAR);
	i = 0;

	while (args[i])
	{
		if (check_each_arg(args[i], found_num, i) == -1)
			return (-1);
		i++;
	}
	return (1);
}

int 	validate_command(char *str, t_valid *valid)
{
	int 	i;
	char 	*cropped;
	int 	found_num;
	int 	found_i;
	int 	start;

	i = 0;
	found_num = -1;
	found_i = -1;
	start = skip_whitespaces(str, i);
	while (str[i])
	{
		cropped = ft_strsub(str, start, i);
		if (compare_command(cropped) >= 0)
		{
			found_num = compare_command(cropped);
			found_i = i;
		}
		i++;
	}
	if (found_num == -1)
		return (-1);
	// if (str[found_i] != DIRECT_CHAR && str[found_i] != ' ' && str[found_i] != '	')
		// return (-1);
	// if (parse_args(ft_strsub(str, found_i, ft_strlen(str) - found_i), found_num) == 1)
		// return (found_num);
	return (ft_strlen(op_tab[found_num].command_name));
}
