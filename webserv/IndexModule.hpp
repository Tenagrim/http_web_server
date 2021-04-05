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

		enum states {
			s_index_start,
			s_search_index_files,
			s_search_default_file,
			s_autoindex
		};

		IndexModule();
		virtual ~IndexModule();

		IBody * getHtmlPage(LocationInit *location,
							std::string const &root, const std::string &url);

	private:
		std::string 	_url;	// full path (+root), ends with '/'
		states			_state;

		IBody			*fileFromIndex(LocationInit *location);
		IBody			*defaultFile();
		IBody			*generateAutoindex();

		void 			setValues(std::string const &root, std::string const &url);
		void setState(LocationInit *location);
		IBody *			searchFile(std::string const & filePath);
		std::string		generateRef(std::string const & filePath);

		class Forbidden403 : public std::exception { const char * what() const throw(); };

		IndexModule(IndexModule const & other);
		IndexModule & operator=(IndexModule const & other);
	};
}
