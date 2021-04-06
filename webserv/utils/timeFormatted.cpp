//
// Created by Skipjack Adolph on 4/6/21.
//

#include <webserv.hpp>
#include <runtime_error.hpp>

#include <sys/time.h>
#include <vector>

namespace ft {

	static int monthDays[12] = {
			31,
			28, // may be 29
			31,
			30,
			31,
			30,
			31,
			31,
			30,
			31,
			30,
			31
	};

	void				monthCount(tm *timeInfo, bool yearLeap);

	void				timeFormatted(char *format, char *buf, int bufLen) {
		struct timeval	mark_t;
		time_t			rawTime;
		struct tm		timeInfo[1];

		if (gettimeofday(&mark_t, NULL))
			throw ft::runtime_error("timeFormatted: gettimeofday func error");
		rawTime = mark_t.tv_sec;

		timeInfo->tm_year = 1970 + rawTime / 31436000 + 70;					// years from 1900
		int leapYears = (timeInfo->tm_year - 1899) / 4;						// leap years from 1900
		timeInfo->tm_yday = (rawTime / 84600 - leapYears) % 365;			// days from year
		monthCount(timeInfo, !(leapYears % 4));					// months from year & days from month
		int secsFromDay = rawTime - static_cast<int>(rawTime / 86400);		// secs from day
		timeInfo->tm_hour = secsFromDay / 3600;
		timeInfo->tm_min = (secsFromDay - (timeInfo->tm_hour * 3600)) / 60;
		timeInfo->tm_sec = secsFromDay - (timeInfo->tm_min * 60);

		strftime(buf, bufLen, format, timeInfo);
	}

	void				monthCount(tm *timeInfo, bool yearLeap) {
		int				i, daysSubtract;

		i = -1;
		daysSubtract = 0;
		timeInfo->tm_mon = 0;
		while (++i < 12) {
			if (timeInfo->tm_yday > daysSubtract) {
				timeInfo->tm_mon++;
				daysSubtract += monthDays[i + (i == 1 ? yearLeap : 0)];
			} else
				break;
			timeInfo->tm_mon++;
		}
		timeInfo->tm_mday = timeInfo->tm_yday - daysSubtract;
	}

}