#include "hw.h"
#include "elev.h"
#include "stateMachine.h"
#include "timer.h"
#include <stdio.h>

int lastDetectedFloor = -1;
int buttonsStatusArray[11] = {0};
int inputStatusArray[11] = {0};

/*
0  - Command 1
1  - Command 2
2  - Command 3
3  - Command 4
4  - Floor 1 up
5  - Floor 2 up
6  - Floor 3 up
7  - Floor 2 down
8  - Floor 3 down
9  - Floor 4 down
10 - Stop
*/

int idToFloor[10] = {
    0,1,2,3,
    0,1,2,
    1,2,3
};
int idToDir[10] = {
    ORDER_DIR_BOTH, ORDER_DIR_BOTH, ORDER_DIR_BOTH, ORDER_DIR_BOTH,
    ORDER_DIR_UP, ORDER_DIR_UP, ORDER_DIR_UP,
    ORDER_DIR_DOWN, ORDER_DIR_DOWN, ORDER_DIR_DOWN
};

int main() {
    // Initialize hardware
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }

    fsm_init();
    while (1) {

        // Check floor sensor
        int currentFloor = elev_get_floor_sensor_signal();
        if (currentFloor != -1 && currentFloor != lastDetectedFloor) {
            fsm_event_arrivedAtFloor(currentFloor);
            lastDetectedFloor = currentFloor;
        }

        hw_updateInputStatusArray(inputStatusArray);

        // Check order buttons
        for (int i = 0; i < 10; ++i) {
            if (inputStatusArray[i] == 1 && buttonsStatusArray[i] == 0) {
                buttonsStatusArray[i] = 1;

                fsm_event_newOrder(idToFloor[i], idToDir[i]);
            } else if (inputStatusArray[i] == 0 && buttonsStatusArray[i] == 1) {
                buttonsStatusArray[i] = 0;
            }
        }

        // Check stop button
        if (inputStatusArray[10] == 1 && buttonsStatusArray[10] == 0) {
            buttonsStatusArray[10] = 1;
            fsm_event_stopPressed(currentFloor);
        } else if (inputStatusArray[10] == 0 && buttonsStatusArray[10] == 1) {
            buttonsStatusArray[10] = 0;
            lastDetectedFloor = -1;
            fsm_event_stopReleased(currentFloor);
        }

        // Check timer
        if (isDoorTimerDone()) {
            fsm_event_doorTimerDone();
            resetDoorTimer();
        }
    }
}
