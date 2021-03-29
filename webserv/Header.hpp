#pragma once
#include <map>
#include <webserv.hpp>
namespace ft
{
	class Header
	{
	private:
		//typedef std::map<int>
	public:
		Header();
		~Header();
		Header(const Header &ref);
		Header &operator=(const Header &ref);
	};
#include <Header.hpp>

	Header::Header()
	{
	}

	Header::~Header()
	{
	}

	Header::Header(const Header &ref)
	{
	}

	Header &Header::operator=(const Header &ref)
	{
		return (*this);
	}
}