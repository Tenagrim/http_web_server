#include <string>
namespace ft
{
	static	void	rec_to_string(int num, std::string &res)
	{
		res = std::string(1, (num % 10) + '0') + res;
		if (num >= 10)
			rec_to_string(num / 10, res);
	}

	std::string		to_string(int num)
	{
		std::string res("");
		bool min = false;

		if (num == 0)
			return ("0");

		if (num < 0)
		{
			min = true;
			num = -num;
		}
		rec_to_string(num, res);
		if (min)
		res = "-" + res;	
		return (res);
	}	
} // namespace ft
