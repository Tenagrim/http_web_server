#include <LocationInit.hpp>

ft::LocationInit::LocationInit(int id): _id(id) {
}

ft::LocationInit::~LocationInit() {
}

bool ft::LocationInit::InitParse(std::list<std::string> &list)
{
	bool state = false;

	str_list_it it = list.begin();
	it = ft::isSpace(it);
	pathParse(list);
	state = openBracket(list);
	state = argumentParse(list);

	return state;
}

void ft::LocationInit::pathParse(std::list<std::string> &list)
{
	_path = list.front();
	list.pop_front();
}

bool ft::LocationInit::openBracket(std::list<std::string> &list)
{
	bool state = false;
	str_list_it it = list.begin();
	str_list_reit reit = list.rbegin();
	it = isSpace(it);
	reit = isSpace(reit);
	if (*it != "{")
		throw std::runtime_error("No Open Bracket ...");
	if (*reit != "}")
		throw std::runtime_error("No Close Bracket ...");
	state = true;
	return state;
}

bool ft::LocationInit::argumentParse(std::list<std::string> &list)
{
	bool state = false;
	state = findKeyWord(list);
	return state;
}

bool ft::LocationInit::findKeyWord(std::list<std::string> &list)
{
	bool state = false;

//	TODO: Stay Here
	str_list_it it = list.begin();
	for (size_t i = 0; i != LocationsKeyWord->size(); ++i) {
		it = std::find(list.begin(), list.end(), LocationsKeyWord[i]);

	}
	return state;
}

unsigned int ft::LocationInit::getId() const
{
	return _id;
}

const std::string &ft::LocationInit::getPath() const
{
	return _path;
}

const ft::LocationInit::argument_map &ft::LocationInit::getLocationsArguments() const
{
	return _locations_arguments;
}
