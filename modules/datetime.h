#ifndef _DATETIME_H
#define _DATETIME_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char* getTimeInfo() {
	time_t t;
	struct tm *curtime;
	time(&t);
	curtime = localtime(&t);

	size_t sz = snprintf(NULL, 0, "%d.%d.%d %d:%.2d", 
			curtime -> tm_mday,
			curtime -> tm_mon,
			curtime -> tm_year + 1900,
			curtime -> tm_hour,
			curtime -> tm_min
		) + 1;
	char* result = malloc(sz);
	snprintf(result, sz, "%d.%d.%d %d:%.2d", 
			curtime -> tm_mday, 
			curtime -> tm_mon, 
			curtime -> tm_year + 1900, 
			curtime -> tm_hour, 
			curtime -> tm_min
		);
	return result;
}

#endif
