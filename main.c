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
    DIR_BOTH, DIR_BOTH, DIR_BOTH, DIR_BOTH,
    DIR_UP, DIR_UP, DIR_UP,
    DIR_DOWN, DIR_DOWN, DIR_DOWN
};

int main() {
    // Initialize hardware
    sm_init();
    if (!elev_init()) {
        printf("Unable to initialize elevator hardware!\n");
        return 1;
    }
    
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
                printf("Button %i was pressed.\n", i);
            }
            if (buttonsStatusArray[i] == 1 && inputStatusArray[i] == 0) {
                buttonsStatusArray[i] = 0;
                printf("Button %i was released.\n", i);
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
