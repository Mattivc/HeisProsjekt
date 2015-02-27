#include "channels.h"
#include "elev.h"
#include "io.h"
#include "timer.h"

#include <assert.h>
#include <stdlib.h>

time_t startTime;
time_t currentTime;

void startDoorTimer (void) {
	startTime = time( NULL );
}
bool isDoorTimerDone (void) {
	currentTime = time ( NULL );
	return difftime ( startTime + 3 ) >= currentTime;
}
void resetDoorTimer (void) {
	startTime = NULL;
	currentTime = NULL;
}