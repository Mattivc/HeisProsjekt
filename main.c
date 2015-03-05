#include "hw.h"
#include "elev.h"
#include "stateMachine.h"
#include "timer.h"
#include "enums.h"
#include <stdio.h>

int lastFloor = -1;
int buttonsStatusArray[10] = {0};
int inputStatusArray[10] = {0};
/*
0 - Command 1
1 - Command 2
2 - Command 3
3 - Command 4
4 - Floor 1 up
5 - Floor 2 up
6 - Floor 3 up
7 - Floor 2 down
8 - Floor 3 down
9 - Floor 4 down 
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
    
    sm_init();

    printf("Press STOP button to stop elevator and exit program.\n");
    while (1) {
        int currentFloot = elev_get_floor_sensor_signal();
        if (currentFloot != -1 && currentFloot != lastFloor) {
            arrivedAtFloor(currentFloot);
            lastFloor = currentFloot;
        }

        updateInputStatusArray(inputStatusArray);
        for (int i = 0; i < 10; ++i) {
            if (buttonsStatusArray[i] == 0 && inputStatusArray[i] == 1) {
                buttonsStatusArray[i] = 1;

                newOrder(idToFloor[i], idToDir[i]);
            }
            if (buttonsStatusArray[i] == 1 && inputStatusArray[i] == 0) {
                buttonsStatusArray[i] = 0;
            }
        }

        if (isDoorTimerDone()) {
            doorTimerDone();
            resetDoorTimer();
        }

        // Stop elevator and exit program if the stop button is pressed
        if (elev_get_stop_signal()) {
            elev_set_motor_direction(DIRN_STOP);
            break;
        }
    }

    return 0;
}
