#include "stateMachine.h"
#include "queue.h"
#include "elev.h"
#include "hw.h"
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


/*
	Internal function decleration
*/

static void setState(sm_state newState);
static order_direction convertMoveStateToOrderState(enum tag_elev_motor_direction dir);

/*
	External functions implementation
*/

void fsm_init() {
	setState(INITIALIZE);
	if (elev_get_floor_sensor_signal() == 0) {
		lastFloor = 0;
		setState(IDLE);
	} else {
		elev_set_motor_direction(DIRN_DOWN);
	}
}

void fsm_event_newOrder(int floor, order_direction dir) {
	switch (currentState) {
		case INITIALIZE:
		case STOP:
			break;
		case IDLE:
		{
			int relative_dir = floor - lastFloor;
			if (relative_dir < 0) {
				direction = DIRN_DOWN;
				setState(MOVING);
			} else if (relative_dir > 0) {
				direction = DIRN_UP;
				setState(MOVING);
			} else {
				setState(AT_FLOOR);
			}
		}
		case MOVING:
		case AT_FLOOR:
			elev_set_button_lamp((int)dir, floor, 1); 
			queue_addOrder(floor, dir);
			printf("New Order. floor %i direction %i\n", floor, dir);
			break;
	}
}

void fsm_event_arrivedAtFloor(int floor) {
	printf("Arrived at floor %i\n", floor);
	lastFloor = floor;
	elev_set_floor_indicator(floor);
	switch (currentState) {
		case INITIALIZE:
			if (floor == 0) {
				elev_set_motor_direction(DIRN_STOP);
				direction = DIRN_UP; // We are at the bottom floor, so initialize move direction to up
				setState(IDLE);
			}
			break;
		case IDLE:
			break;
		case MOVING:
			if (queue_hasOrder(floor, convertMoveStateToOrderState(direction)) || // Does this floor has an order in our current direction?
				(queue_hasOrder(floor, convertMoveStateToOrderState(direction*-1)) && !queue_hasOrderInDir(floor, convertMoveStateToOrderState(direction))) // Does this floor have an order in the opposite direction and no order above us
				) {
				setState(AT_FLOOR);
			}
			break;
		case STOP:
			break;
		case AT_FLOOR:
			break;
	}
}

void fsm_event_doorTimerDone() {
	switch (currentState) {
		case INITIALIZE:
		case IDLE:
		case MOVING:
		case STOP:
			break;
		case AT_FLOOR:
			elev_set_door_open_lamp(0);
			setState(MOVING);
			break;
	}
}


/*
	Internal function implementation 
*/

static void setState(sm_state newState) {
	printf("Set state: %i\n", newState);
	switch (newState) {
		case INITIALIZE:
			break;
		case IDLE:
			break;
		case MOVING:
			elev_set_motor_direction(direction);
			break;
		case STOP:
			elev_set_motor_direction(DIRN_STOP);
			break;
		case AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			queue_clearOrder(lastFloor, ORDER_DIR_BOTH);
			disableOrderLamps(lastFloor);
			elev_set_door_open_lamp(1);
			startDoorTimer();
			break;
	}
	currentState = newState;
}

static order_direction convertMoveStateToOrderState(enum tag_elev_motor_direction dir) {
	switch (dir) {
		case DIRN_UP:
			return ORDER_DIR_UP;
		case DIRN_DOWN:
			return ORDER_DIR_DOWN;
		case DIRN_STOP:
			return ORDER_DIR_BOTH;
	}
}