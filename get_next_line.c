/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 15:58:24 by rbozhko           #+#    #+#             */
/*   Updated: 2017/02/22 15:58:27 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus.h"

static	int		ft_no_nl_line(char *temp, char **line)
{
	char		*str;
	char		*string;

	str = temp;
	string = *line;
	ft_memdel((void**)&string);
	*line = ft_strdup(temp);
	ft_memset(temp, 0, ft_strlen(temp));
	ft_memdel((void**)&str);
	return (1);
}

static int		ft_rtn_line(char *temp, char **line)
{
	char		*str;
	char		*string;

	str = temp;
	string = *line;
	if (NL_CODE)
	{
		*line = ft_strsub(temp, 0, S_C_SUB);
		ft_memdel((void**)&string);
		string = *line;
		ft_memdel((void**)&str);
		return (1);
	}
	else
		return (ft_no_nl_line(temp, line));
}

int				get_next_line(const int fd, char **line, char *str)
{
	static	char		*head = NULL;
	char				*temp;
	int					bytes;
	char				buff[BUFF_SIZE + 1];

	if (IF_FP || IF_SP)
		return (-1);
	!(head) ? head = ft_strnew(BUFF_SIZE + 1) : 0;
	temp = head;
	while ((bytes = read(fd, buff, BUFF_SIZE)) >= 0)
	{
		ft_memdel((void**)&str);
		(bytes < BUFF_SIZE) ? buff[bytes] = '\0' : 0;
		temp = ft_strjoin(temp, buff);
		str = temp;
		if (ft_strlen(temp) > 0)
		{
			if ((NL_CODE) || (!NL_CODE && ft_strlen(buff) == 0))
				return (ft_rtn_line(temp, line));
		}
		else if (bytes == 0 || (bytes == 1 && buff[0] == '\n'))
			break ;
	}
	ft_memdel((void**)&str);
	return (0);
}
