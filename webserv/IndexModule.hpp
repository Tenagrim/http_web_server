//
// Created by Skipjack Adolph on 4/5/21.
//

#pragma once

#include <IIndexModule.hpp>

#include <sys/types.h>
#include <dirent.h>

namespace ft {
	class IndexModule : public IIndexModule {
	public:
		IndexModule();
		virtual ~IndexModule();

		IBody * getHtmlPage(LocationInit *location,
							std::string const &root, const std::string &url);

	private:
		std::string 	_url;		// full path (+root), ends with '/'
		std::string 	_reqUrl;	// URL from request

		IBody			*fileFromIndex(LocationInit *location);
		IBody			*defaultFile(LocationInit *location);
		IBody			*generateAutoindex(LocationInit *location);

		void 			setValue(std::string const &root, std::string const &url);
		IBody *			searchFile(std::string const & filePath);
		std::string		generateHtmlLine(dirent *info);

		class Forbidden403 : public std::exception { const char * what() const throw(); };

		IndexModule(IndexModule const & other);
		IndexModule & operator=(IndexModule const & other);
	};
}
