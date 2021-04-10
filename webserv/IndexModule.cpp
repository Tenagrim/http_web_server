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
			if (!(*it).empty() && (file = searchFile(filePath)))
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
			html += "<html><head><title>Index of ";
			html += _requestUrl;
			html += "</title></head>\n"
					"<body bgcolor=\"white\">\n"
	 				"<h1>Index of ";
			html += _requestUrl;
			html += "</h1><hr><pre>";
			while ((info = readdir(dir)))
				if (strcmp(info->d_name, "."))
					html += generateHtmlLine(info);
			html += "</pre><hr>\n"
		   			"\n"
					"</body></html>";
			closedir(dir);
		} else
			throw ft::runtime_error("IndexModule: directory isn't exist");
		return new TextBody(html);
	}

	std::string IndexModule::generateHtmlLine(dirent *info) {
		std::string		line;
		char 			lineLen;
		char 			buf[TIME_BUFF_AUTOINDEX];
		struct stat		statbuf = {};

		line += "<a href=\"";
		line += info->d_name;
		line += "\">";
		line += info->d_name;
		line += "</a>";
		lineLen = info->d_namlen;
		line.resize(line.size() + (HTML_LINE_LEN - 37 - lineLen), ' ');
		buf[TIME_BUFF_AUTOINDEX - 1] = '\0';
		stat((_url + static_cast<std::string>(info->d_name)).c_str(), &statbuf);
		rawTimeFormatted(statbuf.st_ctime, "%d-%b-%Y %H-%M", buf, TIME_BUFF_AUTOINDEX);
		line += buf;
		if (info->d_type != DT_DIR) {
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
		_requestUrl = url;
		_url = root + (url[0] != '/' ? "/" : "") + addSlash(_requestUrl);
	}

	std::string IndexModule::addSlash(const std::string &url) {
		return url + (url.back() != '/' ? "/" : "");
	}

}
