#ifndef _NETWORK_H
#define _NETWORK_H

#define WRL_INTERFACE "wlan0"
#define WRD_INTERFACE "eth0"

char* getWrlNetworkInfo() {
	FILE *wrl = fopen("/sys/class/net/"WRL_INTERFACE"/operstate", "r");
	if (wrl == NULL) {
		perror("No "WRL_INTERFACE" network interface");
		return NULL;
	}
	char status[7];
	char* result = malloc(10);
	
	fscanf(wrl, "%s", status);
	fclose(wrl);

	snprintf(result, 10, "WF %s", status);
	return result;
}

char* getWrdNetworkInfo() {
	FILE *wrd = fopen("/sys/class/net/"WRD_INTERFACE"/operstate", "r");
	if (wrd == NULL) {
		perror("No "WRD_INTERFACE" network interface");
		return NULL;
	}
	
	char status[7];
	char* result = malloc(10);

	fscanf(wrd, "%s", status);
	fclose(wrd);

	snprintf(result, 10, "WD %s", status);
	return result;
}

#endif
