//
// Created by Skipjack Adolph on 4/5/21.
//

#include <IndexModule.hpp>
#include <TextBody.hpp>
#include <FileBody.hpp>
#include <FileManager.hpp>
#include <webserv.hpp>

#include <vector>

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
/*
	_html(("<html><head><title>Index of /</title></head>\n"
					   "<body bgcolor=\"white\">\n"
					   "<h1>Index of /</h1><hr><pre>"))
*/

namespace ft {

	IndexModule::IndexModule() {
		_state = s_index_start;
	}

	IndexModule::~IndexModule() {}

	IBody *IndexModule::getHtmlPage(LocationInit *location,
									std::string const &root,
									const std::string &url) {
		if (_state == s_index_start) {
			setValues(root, url);
			setState(NULL);
		}

		switch (_state) {
			case s_search_index_files:
				return fileFromIndex(location);    // FileBody
			case s_search_default_file:
				return defaultFile();            // FileBody
			case s_autoindex:
				return generateAutoindex();        // TextBody
		}

		return nullptr;
	}

	IBody *IndexModule::fileFromIndex(LocationInit *location) {
		typedef std::vector<std::string> t_vector;
		std::string filePath;
		t_vector split;
		IBody		*file;

		split = splitString(location->getArgs().find("index")->second, " ");
		for (t_vector::iterator it = split.begin(); it < split.end(); it++) {
			filePath = _url + *it;
////	todo delete it
			std::cout << "file path: " << filePath << std::endl;
////
			if ((file = searchFile(filePath)))
				return file;
		}
		return defaultFile();
	}

	IBody *IndexModule::defaultFile() {
		std::string fileName;
		std::string filePath;
		IBody		*file;

		fileName = "index.html";
		filePath = _url + fileName;
		if ((file = searchFile(filePath)))
			return file;
		return generateAutoindex();
	}

	IBody *IndexModule::generateAutoindex() {
		DIR *dir;
		struct dirent *info;
		std::string html;

		if ((dir = opendir(_url.c_str()))) {
			info = readdir(dir);
		}

		return new TextBody(html);
	}

	void
	IndexModule::setValues(std::string const &root, std::string const &url) {
		_url = root + url[0] != "/" ? "/" : "" + url;
	}

	IBody *IndexModule::searchFile(const std::string &filePath) {
		FileBody	*file;

		if (!stat(filePath.c_str(), nullptr)) {
			file = new FileBody(filePath);
			file->setContentType(FileManager::getContentType(filePath));
			return file;
		}
		return nullptr;
	}

//	s_index_start,
//	s_search_index_files,
//	s_search_default_file,
//	s_autoindex

	void IndexModule::setState(LocationInit *location) {
		if (location->getArgs().find("index")->second.empty())
	}

//	TODO is there another error? (404, maybe)
	const char *IndexModule::Forbidden403::what() const throw() {
		return "IndexModule: no such file from index directive";
	}
}
