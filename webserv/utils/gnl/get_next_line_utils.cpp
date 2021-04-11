/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadolph <sadolph@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 18:50:34 by sadolph           #+#    #+#             */
/*   Updated: 2020/10/13 17:06:59 by sadolph          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.hpp"
#include <stdlib.h>

namespace ft {
	int free_buf(char **buf, int ret) {
		free(*buf);
		*buf = NULL;
		return (ret);
	}

	int ft_strlen_here(const char *s) {
		int i;

		i = 0;
		while (*s++)
			i++;
		return (i);
	}

	char *ft_strjoin_pro(char **s1, const char *s2) {
		char *res;
		size_t i;

		i = 0;
		if (!(**s1)) {
			if (!(res = (char *) malloc((ft_strlen_here(s2) + 1))))
				return (NULL);
		} else if (!(res = (char *) malloc(
				(ft_strlen_here(*s1) + ft_strlen_here(s2) + 1))))
			return (NULL);
		else {
			while ((*s1)[i]) {
				res[i] = (*s1)[i];
				i++;
			}
		}
		while (*s2)
			res[i++] = *(s2++);
		res[i] = '\0';
		free_buf(s1, 1);
		return (res);
	}

	char *ft_substr_pro(char **s, unsigned int start, size_t len, char flag) {
		size_t l;
		size_t i;
		char *res;

		l = ft_strlen_here(*s + start);
		l = l > len ? len : l;
		if ((res = (char *) malloc((l + 1) * sizeof(char)))) {
			i = -1;
			while ((*s)[start + ++i] && l--)
				res[i] = (*s)[start + i];
			res[i] = '\0';
		}
		if (flag == 'r')
			free_buf(s, 1);
		return (res);
	}

	char *ft_strchr(const char *s, int c) {
		while (*s)
			if (*s++ == (unsigned char) c)
				return ((char *) --s);
		if ((unsigned char) c == '\0')
			return ((char *) s);
		return (NULL);
	}
}