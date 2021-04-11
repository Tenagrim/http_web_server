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

		class ErrorException : public std::exception {
			private:
				int _code;
			public:
				ErrorException() : _code(0){}
				explicit ErrorException(int code):_code(code){}
				int whatCode(){return _code;}
			};

	private:
		std::string 	_url;		// full path (+root), ends with '/'
		std::string 	_requestUrl;	// URL from request, ends with '/'
		static bool _index_on;

		IBody			*fileFromIndex(LocationInit *location);
		IBody			*defaultFile(LocationInit *location);
		IBody			*generateAutoindex(LocationInit *location);

		void 			setValue(std::string const &root, std::string const &url);
		IBody *			searchFile(std::string const & filePath);
		std::string		generateHtmlLine(dirent *info);

		std::string		addSlash(std::string const & url);

		IndexModule(IndexModule const & other);
		IndexModule & operator=(IndexModule const & other);
		void 			addSlashBetween(std::string &target, const std::string &add);
		IBody			*defaultRules(const std::string &root, const std::string &url);
	};
}
