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
	fscanf(f, "%s", &status);
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
	
	char* result = malloc(16);
	snprintf(result, 16, "B %s%d%%", status, battery_percantage);

	return result;
}

#endif
