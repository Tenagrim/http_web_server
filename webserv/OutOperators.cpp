#include <IRequest.hpp>
#include <IHeader.hpp>
#include <IResponse.hpp>

std::ostream			&operator<<(std::ostream &os, const ft::IRequest &ref)
{
	os << ref.to_string();
	return (os);
}
std::ostream			&operator<<(std::ostream &os, const ft::IResponse &ref)
{
	os << ref.to_string();
	return (os);
}

std::ostream			&operator<<(std::ostream &os, const ft::IHeader &ref)
{
	os << ref.str();
	return (os);
}