#include "stateMachine.h"
#include "queue.h"
#include "elev.h"
#include <stdio.h>

typedef enum state {
	INITIALIZE,
	IDLE,
	MOVING,
	STOP,
	AT_FLOOR
} state;

state currentState;
static int lastFloor = -1;

void sm_init() {
	currentState = INITIALIZE;
	if (elev_get_floor_sensor_signal() == 0) {
		currentState = IDLE;
	} else {
		elev_set_motor_direction(DIRN_DOWN);
	}
}

void newOrder(int floor, order_direction dir) {
	switch (currentState) {
		case INITIALIZE:
			break;
		case IDLE:
		{
			int relative_dir = floor - lastFloor;
			if (relative_dir < 0) {
				elev_set_motor_direction(DIRN_DOWN);
				currentState = MOVING;
			} else if (relative_dir > 0) {
				elev_set_motor_direction(DIRN_UP);
				currentState = MOVING;
			} else {

			}
		}
		case MOVING:
		case STOP:
		case AT_FLOOR:
			addOrder(floor, dir);
	}
}

void arrivedAtFloor(int floor) {
	printf("Arrived at floor %i\n", floor);
	lastFloor = floor;
	switch (currentState) {
		case INITIALIZE:
			if (floor == 0) {
				elev_set_motor_direction(DIRN_STOP);
				currentState = IDLE;
			}
			break;
		case IDLE:
			break;
		case MOVING:
			break;
		case STOP:
			break;
		case AT_FLOOR:
			break;
	}
}

void doorTimerDone() {
	switch (currentState) {
		case INITIALIZE:
			break;
		case IDLE:
			break;
		case MOVING:
			break;
		case STOP:
			break;
		case AT_FLOOR:
			break;
	}
}