/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbozhko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 13:20:48 by rbozhko           #+#    #+#             */
/*   Updated: 2017/08/17 13:20:49 by rbozhko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_BONUS_H
# define LEM_IN_BONUS_H

# include "libft/libft.h"
# include <fcntl.h>

# define LINK "%c%c%c%c", 0xF0, 0x9F, 0x94, 0x97
# define ST_FLAG "%c%c%c%c", 0xF0, 0x9F, 0x9A, 0xA9
# define FINISH "%c%c%c%c", 0xF0, 0x9F, 0x8F, 0x81
# define ANT "%c%c%c%c", 0xF0, 0x9F, 0x90, 0x9C
# define HOUSE "%c%c%c%c", 0xF0, 0x9F, 0x8F, 0xA0
# define ERROR_SIGN "%c%c%c", 0xE2, 0x9B, 0x94

# define BUFF_SIZE 1
# define NL_CODE ft_strchr(temp, '\n')
# define S_C_SUB (NL_CODE - temp)
# define IF_FP ((fd < 0 || fd > 4096) || ((read(fd, buff, 0)) == -1 && !(head)))
# define IF_SP (!(line) || !(ft_memset(buff, 0, BUFF_SIZE + 1)))

void			ft_handle_error(void);
int				get_next_line(const int fd, char **line, char *str);
#endif
