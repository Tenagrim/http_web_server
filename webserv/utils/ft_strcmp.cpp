//
// Created by Gerry Shona on 4/4/21.
//

namespace ft {
	int ft_strcmp(const char *string1, const char *string2) {
		char *s1;
		char *s2;

		s1 = (char *) string1;
		s2 = (char *) string2;
		while (*s1 != '\0' && *s2 != '\0' && (*s1 == *s2)) {
			s1++;
			s2++;
		}
		return (*(unsigned char *) s1 - *(unsigned char *) s2);
	}
}