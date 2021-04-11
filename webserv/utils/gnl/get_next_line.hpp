/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 14:27:32 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/13 14:30:09 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define F_LIMIT 256

#include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

namespace ft {
	int get_next_line(int fd, char **line);
	int free_buf(char **buf, int ret);
	char *ft_strjoin_pro(char **s1, const char *s2);
	char *ft_substr_pro(char **s, unsigned int start, size_t len, char flag);
	int ft_strlen_here(const char *s);
	char *ft_strchr(const char *s, int c);
}

#endif
