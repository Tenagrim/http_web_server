#pragma once
#include <string>
#include <sys/time.h>
#include <time.h>
class ITimaMachine
{
	// get current time as string as presented in http header "Date" or "Last-Modified"
	//
	// Date: Sat, 27 Mar 2021 03:09:18 GMT
	//       ^---------------------------^
	virtual std::string		getTimestamp(void) = 0;

	// get time as string in presented format from struct timeval
	virtual std::string		getTimestamp(struct timeval &time) = 0;
	
	// get time as string from the POSIX time
	virtual std::string		getTimestamp(time_t time) = 0;

	// maybe timediffs ...
};