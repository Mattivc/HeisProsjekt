#include "stateMachine.h"
#include "queue.h"
#include "elev.h"
#include "timer.h"
#include <stdio.h>

typedef enum sm_state {
	INITIALIZE,
	IDLE,
	MOVING,
	STOP,
	AT_FLOOR
} sm_state;

static sm_state currentState;
static enum tag_elev_motor_direction direction;
static int lastFloor = -1;

void setDirection(elev_motor_direction_t dir) {
	if (dir != DIRN_STOP) { // We want to remember our previus direction when stopping
		direction = dir;
	}
	elev_set_motor_direction(dir);
}

void setState(sm_state newState) {
	printf("Set state: %i\n", newState);
	switch (newState) {
		case INITIALIZE:
			break;
		case IDLE:
			break;
		case MOVING:
			break;
		case STOP:
			break;
		case AT_FLOOR:
			clearOrder(lastFloor, ORDER_DIR_BOTH);
			elev_set_button_lamp(BUTTON_CALL_UP, lastFloor, 0);
			elev_set_button_lamp(BUTTON_CALL_DOWN, lastFloor, 0);
			elev_set_button_lamp(BUTTON_COMMAND, lastFloor, 0);
			elev_set_door_open_lamp(1);
			startDoorTimer();
			break;
	}
	currentState = newState;
}

void sm_init() {
	setState(INITIALIZE);
	if (elev_get_floor_sensor_signal() == 0) {
		setState(IDLE);
	} else {
		setDirection(DIRN_DOWN);
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
				setDirection(DIRN_DOWN);
				setState(MOVING);
			} else if (relative_dir > 0) {
				setDirection(DIRN_UP);
				setState(MOVING);
			} else {
				setState(AT_FLOOR);
			}
		}
		case MOVING:
		case STOP:
		case AT_FLOOR:
			elev_set_button_lamp((int)dir, floor, 1);
			
			addOrder(floor, dir);
			printf("New Order. floor %i direction %i\n", floor, dir);
			break;
	}
}

void arrivedAtFloor(int floor) {
	printf("Arrived at floor %i\n", floor);
	lastFloor = floor;
	elev_set_floor_indicator(floor);
	switch (currentState) {
		case INITIALIZE:
			if (floor == 0) {
				setDirection(DIRN_STOP);
				setState(IDLE);
			}
			break;
		case IDLE:
			break;
		case MOVING:
			if (direction == DIRN_UP && hasOrder(floor, ORDER_DIR_UP)) {
				setDirection(DIRN_STOP);
				setState(AT_FLOOR);
			} else if (direction == DIRN_DOWN && hasOrder(floor, ORDER_DIR_DOWN)) {
				setDirection(DIRN_STOP);
				setState(AT_FLOOR);
			}
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
		case IDLE:
		case MOVING:
		case STOP:
			break;
		case AT_FLOOR:
			elev_set_door_open_lamp(0);

			if (direction == DIRN_UP) { // We should continue in our current direction if any orders above us.
				if (hasOrderAbove(lastFloor, ORDER_DIR_BOTH)) {
					setDirection(DIRN_UP);
					setState(MOVING);
				} else if (hasOrderBelow(lastFloor, ORDER_DIR_BOTH)) { // Nothing above us, is there anything below?
					setDirection(DIRN_DOWN);
					setState(MOVING);
				} else {
					setState(IDLE);
				}
			} else {
				if (hasOrderBelow(lastFloor, ORDER_DIR_BOTH)) {
					setDirection(DIRN_DOWN);
					setState(MOVING);
				} else if (hasOrderAbove(lastFloor, ORDER_DIR_BOTH)) {
					setDirection(DIRN_UP);
					setState(MOVING);
				} else {
					setState(IDLE);
				}
			}
			break;
	}
}