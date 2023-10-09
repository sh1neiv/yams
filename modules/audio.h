#ifndef _AUDIO_H
#define _AUDIO_H

char* getAudioMasterVolume() {
	int volume = -1;

	FILE *p = popen("amixer get Master | grep Right | grep -E -o '[0-9]{1,3}%'", "r");
	if ( p == NULL) {
		perror("Unable to execute command");
		return NULL;
	}

	fscanf(p, "%d", &volume);
	pclose(p);

	if (volume == -1) {
		p = popen("amixer -D pulse sset Master 0%+", "r");
		if (p == NULL) {
			perror("Unable to execute command");
			return NULL;
		}
		pclose(p);
	}

	char* result = malloc(7);
	snprintf(result, 7, "V %d%%", volume);
	
	return result;
}

#endif
