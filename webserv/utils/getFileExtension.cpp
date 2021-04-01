#include <string>
//#include <iostream>
namespace ft
{
	std::string			getFileExtension(std::string const & filename)
	{
		std::string::size_type pos = filename.rfind('.');
		if (pos == std::string::npos)
			return ("");
//		std::cout << "POS: " << pos << "\n";
		return filename.substr(pos + 1, filename.size() - pos);
	}
} // namespace ft