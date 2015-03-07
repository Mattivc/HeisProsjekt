#include "hw.h"
#include "elev.h"


void hw_updateInputStatusArray(int *statusArray) {
	
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
	// Stop
	statusArray[10] = elev_get_stop_signal();
}

void hw_disableOrderLamps(int floor) {
	if (floor != 3) { elev_set_button_lamp(BUTTON_CALL_UP, floor, 0); }
	if (floor != 0) { elev_set_button_lamp(BUTTON_CALL_DOWN, floor, 0); }
	elev_set_button_lamp(BUTTON_COMMAND, floor, 0);
}

void hw_resetAllOrderLamps() {
	// Command buttons
	elev_set_button_lamp(BUTTON_COMMAND, 0, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 1, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 2, 0);
	elev_set_button_lamp(BUTTON_COMMAND, 3, 0);
	// Order up 
	elev_set_button_lamp(BUTTON_CALL_UP, 0, 0);
	elev_set_button_lamp(BUTTON_CALL_UP, 1, 0);
	elev_set_button_lamp(BUTTON_CALL_UP, 2, 0);
	// Order down
	elev_set_button_lamp(BUTTON_CALL_DOWN, 1, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, 2, 0);
	elev_set_button_lamp(BUTTON_CALL_DOWN, 3, 0);
}

void hw_resetAllLamps() {
	// Order buttons
	hw_resetAllOrderLamps();
	// Door & stop
	elev_set_door_open_lamp(0);
	elev_set_stop_lamp(0);
}