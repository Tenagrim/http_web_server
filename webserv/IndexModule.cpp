//
// Created by Skipjack Adolph on 4/5/21.
//

#include <IndexModule.hpp>
#include <TextBody.hpp>
#include <FileBody.hpp>
#include <FileManager.hpp>
#include <webserv.hpp>
#include <defines.hpp>

#include <vector>

#define HTML_LINE_LEN 88

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

	IndexModule::IndexModule() {}

	IndexModule::~IndexModule() {}

	IBody *IndexModule::getHtmlPage(LocationInit *location,
									std::string const &root,
									const std::string &url) {
		setValue(root, url);

		return fileFromIndex(location);
	}

	IBody *IndexModule::fileFromIndex(LocationInit *location) {
		typedef std::vector<std::string> t_vector;
		std::string filePath;
		t_vector	split;
		IBody		*file;

		split = splitString(location->getArgs().find("index")->second, " ");
		for (t_vector::iterator it = split.begin(); it < split.end(); it++) {
			filePath = _url + *it;
			if ((file = searchFile(filePath)))
				return file;
		}
		return defaultFile(location);
	}

	IBody *IndexModule::defaultFile(LocationInit *location) {
		std::string fileName;
		std::string filePath;
		IBody		*file;

		fileName = "index.html";
		filePath = _url + fileName;
		if ((file = searchFile(filePath)))
			return file;
		return generateAutoindex(location);
	}

	IBody *IndexModule::generateAutoindex(LocationInit *location) {
		if (location->getArgs().find("autoindex") == location->getArgs().end())
			return nullptr;

		DIR			* dir;
		dirent		* info;
		std::string	html;

		if ((dir = opendir(_url.c_str()))) {
			html += "<html><head><title>Index of /</title></head>\n"
					"<body bgcolor=\"white\">\n"
					"<h1>Index of /</h1><hr><pre>";
			while ((info = readdir(dir)))
				html += generateHtmlLine(info);
			html += "</pre><hr>\n"
		   			"\n"
					"</body></html>";
			closedir(dir);
		} else
			throw ft::runtime_error("IndexModule: directory isn't exist");
		return new TextBody(html);
	}

//	<a href="../">../</a>
//	<a href="phpmyadmin/">phpmyadmin/</a>                                        05-Apr-2021 11:05                   -
//	<a href="wordpress/">wordpress/</a>                                         05-Apr-2021 11:04                   -
//	<a href="index.nginx-debian.html">index.nginx-debian.html</a>                            05-Apr-2021 11:04                 612

	std::string IndexModule::generateHtmlLine(dirent *info) {
		std::string		line;
		char 			lineLen;
		char 			buf[TIME_BUFF_AUTOINDEX];
		struct stat		statbuf = {};

		line += "a href=\"";
		line += info->d_name;
		line += "\">";
		line += info->d_name;
		line += "</a>";
		lineLen = info->d_namlen;
		line.resize(line.size() + (HTML_LINE_LEN - 37 - lineLen), ' ');
		buf[TIME_BUFF_AUTOINDEX - 1] = '\0';
		currentTimeFormatted("%d-%b-%Y %H-%M", buf, TIME_BUFF_AUTOINDEX);
		line += buf;
		if (info->d_type != DT_DIR) {
			stat(info->d_name, &statbuf);
			std::string fileLen = to_string(statbuf.st_size);
			line.resize(line.size() + 20 - fileLen.size(), ' ');
			line += fileLen;
			line += '\n';
		} else {
			line.resize(line.size() + 19, ' ');
			line += "-\n";
		}

		return line;
	}

	IBody *IndexModule::searchFile(const std::string &filePath) {
		FileBody	*file;
		struct stat statbuf = {};

		if (!stat(filePath.c_str(), &statbuf)) {
			file = new FileBody(filePath);
			file->setContentType(FileManager::getContentType(filePath));
			return file;
		}
		return nullptr;
	}

	void IndexModule::setValue(std::string const &root, std::string const &url) {
		_url = root + (url[0] != '/' ? "/" : "") + url;
	}

}
