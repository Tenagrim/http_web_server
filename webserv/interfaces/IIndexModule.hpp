//
// Created by Skipjack Adolph on 4/5/21.
//

#pragma once

#include <TextBody.hpp>
#include <LocationInit.hpp>
#include <Request.hpp>

namespace ft {
	class IIndexModule {
	public:
		virtual IBody * getHtmlPage(LocationInit *location,
									std::string const &root, const std::string &request) = 0;

		virtual ~IIndexModule() {};
	};
}