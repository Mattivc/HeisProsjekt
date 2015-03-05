#include <time.h>
#include <stdio.h>

#define time_length 3

time_t startTime;
time_t currentTime;

int isSet = 0;

void startDoorTimer() {
	startTime = time(0);
	isSet = 1;
}

int isDoorTimerDone() {
	if (isSet == 0) {
		return 0;
	} else {
		currentTime = time(0);
		return currentTime - startTime > time_length;	
	}
}

void resetDoorTimer() {
	isSet = 0;
}