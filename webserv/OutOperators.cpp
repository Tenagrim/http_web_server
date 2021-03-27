#include <IRequest.hpp>
#include <IHeader.hpp>

std::ostream			&operator<<(std::ostream &os, const ft::IRequest &ref)
{
	os << ref.to_string();
	return (os);
}

std::ostream			&operator<<(std::ostream &os, const ft::IHeader &ref)
{
	os << ref.str();
	return (os);
}