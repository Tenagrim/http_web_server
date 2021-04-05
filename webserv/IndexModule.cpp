//
// Created by Skipjack Adolph on 4/5/21.
//

#include "IndexModule.hpp"

// todo remove after testing
/*
<html><head><title>Index of /</title></head>
<body bgcolor="white">
<h1>Index of /</h1><hr><pre><a href="../">../</a>
<a href="phpmyadmin/">phpmyadmin/</a>                                        05-Apr-2021 11:05                   -
<a href="wordpress/">wordpress/</a>                                         05-Apr-2021 11:04                   -
<a href="index.nginx-debian.html">index.nginx-debian.html</a>                            05-Apr-2021 11:04                 612
</pre><hr>

</body></html>
*/

ft::IndexModule::IndexModule() :
	_html(("<html><head><title>Index of /</title></head>\n"
					   "<body bgcolor=\"white\">\n"
					   "<h1>Index of /</h1><hr><pre>")) {
	_state = s_index_start;
}

ft::IndexModule::~IndexModule() {}

ft::IBody * ft::IndexModule::getHtmlPage(LocationInit *location,
										 std::string const &root, const std::string &url) {
	if (_state == s_index_start) {
		setValues(location, root, url);
		setState();
	}

	if (_state == s_search_index_files)
		return fileFromIndex(); // FileBody
	else if (_state == s_search_default_file)
		return defaultFile(); // FileBody
	else if (_state == s_autoindex)
		return generateAutoindex(); // TextBody

/*
	DIR 			* dir;
	struct dirent	* info;

	if ((dir = opendir(_urlPath.c_str()))) {
		info = readdir(dir);
	}
*/
	return nullptr;
}

void ft::IndexModule::setValues(LocationInit *location, std::string const &root,
								std::string const &url) {
	_urlPath = root + url[0] != "/" ? "/" : "" + url;
	_location = location;
}
