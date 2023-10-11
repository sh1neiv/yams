#ifndef _CMUS_H
#define MAX_SONG_LENGTH 40

const char c_play[] = "\u25b6";
const char c_pause[] = "\u23f8";

char *getCmusCurrentSong() {
	char status[16];
	char song[MAX_SONG_LENGTH];
	FILE* p = popen("pgrep cmus>& /dev/null; [[ $? -eq 0 ]] && cmus-remote -Q | grep status | awk '{print $2}'", "r");
	if (p == NULL) {
		perror("Unable to execute command");
		return NULL;
	}
	
	fscanf(p, "%16s", status);
	pclose(p);

	if (strcmp(status, "playing") == 0) {
		memset(status, 0, 16);
		sprintf(status, "%s", c_play);
	}
	else if(strcmp(status, "paused") == 0) {
		memset(status, 0, 16);
		sprintf(status, "%s ", c_pause);
	}
	else {
		return NULL;
	}

	p = popen("cmus-remote -Q | grep file | awk '{n=split($0, pth, \"/\"); split(pth[n], fn, \".mp3\"); print(fn[1])}'", "r");
	if (p == NULL) {
		perror("Unable to execute command");
		return NULL;
	}
	fgets(song, MAX_SONG_LENGTH, p);
	pclose(p);

	if (strlen(song) == MAX_SONG_LENGTH - 1) {
		for (int i = MAX_SONG_LENGTH - 5; i <= MAX_SONG_LENGTH - 2; i++) {
			song[i] = '.';
		}
	}	

	size_t sz = snprintf(NULL, 0, "%s %s", status, song);
	char *result = malloc(sz);
	snprintf(result, sz, "%s %s", status, song);

	return result;
}

#endif
