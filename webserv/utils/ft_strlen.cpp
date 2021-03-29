namespace ft
{
	unsigned long	ft_strlen(char *str)
	{
		unsigned long len = 0;
		while(str[len])
			len++;
		return(len);
	}
}