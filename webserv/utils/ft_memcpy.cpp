
namespace ft
{
	void *ft_memcpy(void *dest, const void *src, unsigned long num)
	{
		unsigned char *p_d;
		unsigned char *p_s;
		unsigned long i;

		if (!dest && !src && num)
			return (0);
		p_s = (unsigned char *)src;
		p_d = (unsigned char *)dest;
		i = 0;
		while (i < num)
		{
			p_d[i] = p_s[i];
			i++;
		}
		return (dest);
	}
}