#include <fstream>
#include <string>
#include <cstring>
#include <iostream>
#include <list>

bool is_sep(char c)
{
	char seps[] = " \r\n\t(){}.:;";
	return (strchr(seps,c));
}

int main (int ac, char **av)
{
	std::ifstream fin;
	std::string lines;
	fin.open(av[1]);
	getline(fin, lines, '\0');

	std::list<std::string> items;
	std::string buff;

	std::cout << lines << "========\n";

	for (std::string::iterator it = lines.begin(); it != lines.end(); it++)
	{
		if (is_sep(*it))
		{
			if (buff.size())
			{
				items.push_back(buff);
				buff.clear();
			}
			items.push_back(std::string(1, *it));
		}
		else
			buff += *it;
	}

	for ( std::list<std::string>::iterator it = items.begin(); it != items.end();it++ )
	{

			std::cout << ">" << *it << "<" ;
	}
	std::cout << "\n";

}