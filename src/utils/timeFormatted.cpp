//
// Created by Skipjack Adolph on 4/6/21.
//

#include <webserv.hpp>
#include <defines.hpp>
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

	void 				currentTimeFormatted(const char *format, char *buf, int bufLen) {
		struct timeval	mark_t;

		if (gettimeofday(&mark_t, NULL))
			throw ft::runtime_error("rawTimeFormatted: gettimeofday func error");
		rawTimeFormatted(mark_t.tv_sec, format, buf, bufLen);
	}

	void				rawTimeFormatted(time_t rawTime, const char *format,
						  							char *buf, int bufLen) {
		struct tm		timeInfo[1];

		timeInfo->tm_year = 1970 + rawTime / 31436000;						// years from 1970
		int leapYears = (timeInfo->tm_year - 1970) / 4;						// leap years from 1970
		timeInfo->tm_yday = (rawTime / 86400 - leapYears) % 365;			// days from year
		monthCount(timeInfo, !((timeInfo->tm_year - 1972) % 4));	// months from year & days from month
		int days = rawTime / 86400;
		int secsFromDay = rawTime - days * 86400;							// secs from day
		timeInfo->tm_hour = secsFromDay / 3600;
		timeInfo->tm_min = (secsFromDay - (timeInfo->tm_hour * 3600)) / 60;
		timeInfo->tm_sec = secsFromDay - ((timeInfo->tm_hour * 3600) + (timeInfo->tm_min * 60));
		timeInfo->tm_hour += TIME_ZONE;
		timeInfo->tm_year -= 1900;
		timeInfo->tm_wday = (days + 4) % 7;

		strftime(buf, bufLen, format, timeInfo);
		buf[bufLen - 1] = '\0';
	}

	void				monthCount(tm *timeInfo, bool yearLeap) {
		int				i, daysSubtract;

		i = -1;
		daysSubtract = 0;
		timeInfo->tm_mon = 0;
		while (++i < 12) {
			if (timeInfo->tm_yday > daysSubtract + monthDays[i + 1]) {
				daysSubtract += monthDays[i + (i == 1 ? yearLeap : 0)];
				timeInfo->tm_mon++;
			} else
				break;
		}
		timeInfo->tm_mday = timeInfo->tm_yday - daysSubtract;
	}

}