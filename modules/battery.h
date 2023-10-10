#ifndef _BATTERY_H
#define _BATTERY_H
#define BAT "BAT0"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char arrowUp[] = "\u2191";
const char arrowDown[] = "\u2193";

char* getBatteryInfo() {
	int battery_percantage = -1;
	char status[16];

	FILE *f = fopen("/sys/class/power_supply/"BAT"/capacity", "r");
	if (f == NULL) {
		perror("No battery named "BAT" presented. Unload the module if you want to continue");
		return NULL;
	}

	fscanf(f, "%d", &battery_percantage);
	fclose(f);

	f = fopen("/sys/class/power_supply/"BAT"/status", "r");
	fscanf(f, "%15s", &status);
	fclose(f);

	if (strcmp(status, "Charging") == 0) {
		memset(status, 0, 16);
		strcpy(status, arrowUp);
	}
	else if (strcmp(status, "Full") == 0) {
		memset(status, 0, 16);
	}
	else {
		memset(status, 0, 16);
		strcpy(status, arrowDown);
	}

	size_t sz = snprintf(NULL, 0, "B %s%d%%", status, battery_percantage) + 1;
	char* result = malloc(sz);
	snprintf(result, sz, "B %s%d%%", status, battery_percantage);

	return result;
}

#endif
