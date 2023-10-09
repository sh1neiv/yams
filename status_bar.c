/* modules headers */
#include "modules/battery.h"
#include "modules/datetime.h"
#include "modules/audio.h"
#include "modules/network.h"

/* obligatory headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <X11/Xlib.h>

/* related stuff */
char* (*modules[4]) () = {
	getAudioMasterVolume,
	getWrdNetworkInfo,
	getBatteryInfo,
	getTimeInfo
};
char status[512];
short int status_pr = 1;
Display *dpy;



/* signal handlers */
void SIGINT_handler(int signal) {
	status_pr = 0;
}

int main() {
	signal(SIGINT, SIGINT_handler);

	while (status_pr) {
		if ((dpy = XOpenDisplay(NULL)) == NULL) {
			printf("Unable to open display\n");
			status_pr = -1;
			break;
		}

		int counter = 0;
		status[counter++] = ' ';

		for (int i = 0; i < sizeof(modules)/sizeof(modules[0]); i++) {
			char* info = modules[i]();
			if (info == NULL) continue;
			for (int j = 0; j < (int)strlen(info); j++) {
				status[counter++] = info[j];
			}
			free(info);

			status[counter++] = ' ';
			status[counter++] = '|';
			status[counter++] = ' ';
		}

		status[counter-2] = '\0'; 

		XStoreName(dpy, DefaultRootWindow(dpy), status);
		XSync(dpy, 0);
		XCloseDisplay(dpy);
		memset(status, 0, sizeof(status));
		sleep(1);
	}

	return status_pr;
}
