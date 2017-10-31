/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymushet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:22:30 by ymushet           #+#    #+#             */
/*   Updated: 2017/10/29 19:30:41 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static char			*ft_yegor_strjoin(char const *s1, char const *s2)
{
	char	*ptr;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return (ft_strdup(s2));
	if (s2 == NULL)
		return (ft_strdup(s1));
	ptr = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ptr = ft_strcpy(ptr, s1);
	ptr = ft_strcat(ptr, s2);
	return (ptr);
}

static t_struct		*static_struct(int fd, t_struct **head)
{
	t_struct	*tmp;

	tmp = *head;
	if (tmp != NULL)
	{
		while ((tmp != NULL) && (tmp->fd != fd))
			tmp = tmp->next;
		if (tmp && tmp->fd == fd)
			return (tmp);
	}
	if (tmp == NULL)
	{
		tmp = malloc(sizeof(t_struct));
		tmp->fd = fd;
		tmp->line = NULL;
		tmp->next = NULL;
	}
	*head != NULL ? tmp->next = *head : 0;
	*head = tmp;
	return (*head);
}

static char			*check_balance(char **str)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

	if (*str == NULL)
		return (NULL);
	if ((tmp = strchr(*str, '\n')) != NULL)
	{
		line = strncpy(ft_strnew(tmp - *str), *str, tmp - *str);
		tmp2 = strdup(tmp + 1);
		ft_strdel(&(*str));
		*str = tmp2;
		return (line);
	}
	return (tmp);
}

static char			*get_line(char *buff, t_struct *balance)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

	tmp2 = NULL;
	tmp = NULL;
	line = NULL;
	if ((tmp = strchr(buff, '\n')) != NULL)
	{
		tmp2 = strncpy(ft_strnew(tmp - buff), buff, tmp - buff);
		line = ft_yegor_strjoin(balance->line, tmp2);
		ft_strdel(&tmp2);
		ft_strdel(&balance->line);
		balance->line = strdup((tmp + 1));
		return (line);
	}
	balance->line != NULL ? tmp = strdup(balance->line) : 0;
	ft_strdel(&balance->line);
	balance->line = ft_yegor_strjoin(tmp, buff);
	ft_strdel(&tmp);
	return (NULL);
}

int					get_next_line(int fd, char **line)
{
	static t_struct	*head = NULL;
	t_struct		*balance;
	char			buff[BUFF_SIZE + 1];

	if (read(fd, NULL, 0) == -1)
		return (-1);
	balance = static_struct(fd, &head);
	if ((*line = check_balance(&balance->line)) != NULL)
		return (1);
	bzero(buff, BUFF_SIZE + 1);
	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		if ((*line = get_line(buff, balance)) != NULL)
			return (1);
		bzero(buff, BUFF_SIZE + 1);
	}
	*line = ft_yegor_strjoin(balance->line, buff);
	if (strcmp(*line, "") == 0)
		return (0);
	ft_strdel(&balance->line);
	balance->line = strdup("");
	return (1);
}
