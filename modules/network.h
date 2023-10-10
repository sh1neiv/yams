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
	char status[32];	
	fscanf(wrl, "%31s", status);
	fclose(wrl);

	size_t sz = snprintf(NULL, 0, "WF %s", status) + 1;
	char *result = malloc(sz);
	snprintf(result, sz, "WF %s", status);
	return result;
}

char* getWrdNetworkInfo() {
	FILE *wrd = fopen("/sys/class/net/"WRD_INTERFACE"/operstate", "r");
	if (wrd == NULL) {
		perror("No "WRD_INTERFACE" network interface");
		return NULL;
	}
	
	char status[32];
	fscanf(wrd, "%31s", status);
	fclose(wrd);

	size_t sz = snprintf(NULL, 0, "WD %s", status) + 1;
	char *result = malloc(sz);
	snprintf(result, sz, "WD %s", status);
	return result;
}

#endif
