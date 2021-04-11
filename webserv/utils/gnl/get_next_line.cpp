/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:34 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/13 17:06:57 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.hpp"
#include <unistd.h>
#include <stdlib.h>

namespace ft {
	static int renew_params(char **remain, char *buf, char **line, char flag) {
		char **choice;
		char *endline;

		if (flag == 'b')
			choice = &buf;
		else
			choice = remain;
		if (!(endline = ft_strchr(*choice, '\n'))) {
			if (!(*line = ft_strjoin_pro(line, *choice)))
				return (flag == 'r' ? free_buf(remain, 1) : 1);
			if (flag == 'r')
				free_buf(remain, 1);
		} else {
			*endline = '\0';
			if (!(*line = ft_strjoin_pro(line, *choice)))
				return (-1);
			if (!(*remain = ft_substr_pro(choice,
										  ft_strlen_here(*choice) + 1,
										  BUFFER_SIZE, flag)))
				return (-1);
			return (1);
		}
		return (0);
	}

	int get_next_line(int fd, char **line) {
		size_t rd;
		char *buf;
		static char *remain[F_LIMIT];

		if (BUFFER_SIZE < 1 || fd < 0 || !line ||
			0 != read(fd, remain[fd], 0) ||
			!(buf = (char *) malloc(BUFFER_SIZE + 1)))
			return (-1);
		*line = (char *)malloc(1);
		**line = '\0';
		if (remain[fd]) {
			if ((rd = renew_params(&remain[fd], remain[fd], line, 'r')))
				return (free_buf(&buf, rd));
		}
		while ((rd = read(fd, buf, BUFFER_SIZE)) > 0) {
			buf[rd] = '\0';
			if ((rd = renew_params(&remain[fd], buf, line, 'b')))
				return (free_buf(&buf, rd));
		}
		free_buf(&remain[fd], 1);
		return (free_buf(&buf, rd));
	}
}