//
// Created by Skipjack Adolph on 4/5/21.
//

#pragma once

#include <IIndexModule.hpp>
#include <ABody.hpp>

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
		std::string 	_html;
		std::string 	_urlPath;	// full path (+root)
		states			_state;
		LocationInit	*_location;

		void			setValues(LocationInit *location,
				   			std::string const &root, std::string const &url);
		void 			setState();
		std::string		searchFile();
		std::string		generateRef(std::string const & filePath);
		std::string		makeFilePath(std::string const & fileName);

		IndexModule(IndexModule const & other);
		IndexModule & operator=(IndexModule const & other);
	};
}
