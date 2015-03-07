// Timer functions
//
// 2015, Matias Christensen & Mikael Kvalvær

#include <time.h>

#define time_length 3

time_t startTime;
time_t currentTime;

int isSet = 0;

void timer_start() {
	startTime = time(0);
	isSet = 1;
}

int timer_isDone() {
	if (!isSet) {
		return 0;
	} else {
		currentTime = time(0);
		return currentTime - startTime > time_length;	
	}
}

void timer_reset() {
	isSet = 0;
}
