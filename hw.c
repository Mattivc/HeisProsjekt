#include "hw.h"
#include "elev.h"


void updateInputStatusArray(int *statusArray) {
	
	// Command buttons
	statusArray[0] = elev_get_button_signal(BUTTON_COMMAND, 0);
	statusArray[1] = elev_get_button_signal(BUTTON_COMMAND, 1);
	statusArray[2] = elev_get_button_signal(BUTTON_COMMAND, 2);
	statusArray[3] = elev_get_button_signal(BUTTON_COMMAND, 3);
	// Order up
	statusArray[4] = elev_get_button_signal(BUTTON_CALL_UP, 0);
	statusArray[5] = elev_get_button_signal(BUTTON_CALL_UP, 1);
	statusArray[6] = elev_get_button_signal(BUTTON_CALL_UP, 2);
	// Order down
	statusArray[7] = elev_get_button_signal(BUTTON_CALL_DOWN, 1);
	statusArray[8] = elev_get_button_signal(BUTTON_CALL_DOWN, 2);
	statusArray[9] = elev_get_button_signal(BUTTON_CALL_DOWN, 3);
}

void disableOrderLamps(int floor) {
	elev_set_button_lamp(BUTTON_CALL_UP, floor, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0);
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
}