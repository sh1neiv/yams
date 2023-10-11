/* modules headers */
#include "modules/battery.h"
#include "modules/datetime.h"
#include "modules/audio.h"
#include "modules/network.h"
#include "modules/cmus.h"

/* obligatory headers */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <X11/Xlib.h>

/* related stuff */
#define MAX_SB_LENGTH 512
#define SB_PADDING 2
char* (*modules[]) () = {
	getCmusCurrentSong,
	getAudioMasterVolume,
	getWrlNetworkInfo,
	getWrdNetworkInfo,
	getBatteryInfo,
	getTimeInfo
};
char status[MAX_SB_LENGTH];
short int status_pr = 1;
Display *dpy;



/* signal handlers */
void SIGINT_handler(int signal) {
	status_pr = 0;
}

/* utils */
void mssleep(long ms) {
	if (ms < 0) {
		return;
	}

	struct timespec ts;
	ts.tv_sec = ms / 1000;
	ts.tv_nsec = ms * 1000000;
	nanosleep(&ts, &ts);
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
			if (counter < MAX_SB_LENGTH) {
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
			else {
				break;
			}
		}

		status[counter - SB_PADDING] = '\0'; 

		XStoreName(dpy, DefaultRootWindow(dpy), status);
		XSync(dpy, 0);
		XCloseDisplay(dpy);
		memset(status, 0, sizeof(status));
		mssleep(250);
	}

	return status_pr;
}
