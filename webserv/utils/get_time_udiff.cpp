//
// Created by Gerry Shona on 4/4/21.
//
#include <sys/time.h>
unsigned long	get_time_udiff(struct timeval *t1, struct timeval *t2)
{
	struct timeval diff;

	diff.tv_sec = t2->tv_sec - t1->tv_sec;
	diff.tv_usec = t2->tv_usec - t1->tv_usec;
	return (diff.tv_sec * 1000000 + diff.tv_usec);
}

