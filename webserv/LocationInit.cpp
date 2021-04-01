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
	int count_args = 0;
	for (size_t i = 0; i != 9; i++) {
		str_list_it it = list.begin();
		it = std::find(list.begin(), list.end(), LocationsKeyWord[i]);
		if (it != list.end())
		{
			state = parseKeyWord(list, it);
			count_args++;
		}
	}
	if (count_args == 0)
		throw std::runtime_error("No argument in Locations");
	return state;
}

bool ft::LocationInit::parseKeyWord(std::list<std::string> &list, std::list<std::string>::iterator &it)
{
	bool state = false;
	std::list<std::string> *tmp = new std::list<std::string>;
	str_list_it back = std::find(it, list.end(), ";");
	tmp->splice(tmp->begin(), list, it, ++back);
	std::list<std::string>::iterator key = tmp->begin();
	if (tmp->back() != ";"){
		state = false;
		throw std::runtime_error("No close BRACKET in " + *key + " argument");
	} else {
	tmp->pop_back();
	_locations_arguments[*key];
	tmp->erase(tmp->begin());
	std::list<std::string>::iterator tmp_it = tmp->begin();
	std::string buff;
	for(; tmp_it != tmp->end(); ++tmp_it) {
		buff += *tmp_it;
	}
	_locations_arguments[*key] = buff;
	}
	delete tmp;
	return true;
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
