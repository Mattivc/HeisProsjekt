#include "stateMachine.h"
#include "queue.h"
#include "elev.h"
#include "hw.h"
#include "timer.h"
#include <stdio.h>

typedef enum sm_state {
	INITIALIZE = 0,
	IDLE = 1,
	MOVING = 2,
	STOP = 3,
	AT_FLOOR = 4
} sm_state;

static sm_state currentState;
static elev_motor_direction_t currentDirection = DIRN_STOP;
static int lastFloor = -1;


/*
	Internal function decleration
*/

void setState(sm_state newState);
order_direction_t convertMoveStateToOrderState(enum tag_elev_motor_direction dir);
void printState();
void printDirection();

/*
	External functions implementation
*/

void fsm_init() {
	setState(INITIALIZE);
	hw_resetAllLamps();
	if (elev_get_floor_sensor_signal() == 0) {
		lastFloor = 0;
		setState(IDLE);
	} else {
		elev_set_motor_direction(DIRN_DOWN);
	}
}

void fsm_event_newOrder(int floor, order_direction_t dir) {
	switch (currentState) {
		case INITIALIZE:
		case STOP:
			break;
		case IDLE:
		{
			int relative_dir = floor - lastFloor;
			if (relative_dir < 0) {
				currentDirection = DIRN_DOWN;
				setState(MOVING);
			} else if (relative_dir > 0) {
				currentDirection = DIRN_UP;
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
	queue_printState();
}

void fsm_event_arrivedAtFloor(int floor) {
	printf("Arrived at floor %i\n", floor);
	printDirection();
	lastFloor = floor;
	elev_set_floor_indicator(floor);
	switch (currentState) {
		case INITIALIZE:
			if (floor == 0) {
				elev_set_motor_direction(DIRN_STOP);
				currentDirection = DIRN_UP; // We are at the bottom floor, so initialize move direction to up
				setState(IDLE);
			}
			break;
		case IDLE:
			break;
		case MOVING:
			if (queue_hasOrder(floor, convertMoveStateToOrderState(currentDirection)) || // Does this floor has an order in our current direction?
				(queue_hasOrder(floor, convertMoveStateToOrderState(currentDirection*-1)) && !queue_hasOrderInDir(floor, convertMoveStateToOrderState(currentDirection))) // Does this floor have an order in the opposite direction and no order above us
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

void setState(sm_state newState) {
	currentState = newState;

	printState();
	printDirection();

	switch (newState) {
		case INITIALIZE:
			break;
		case IDLE:
			break;
		case MOVING:
			elev_set_motor_direction(currentDirection);
			break;
		case STOP:
			elev_set_motor_direction(DIRN_STOP);
			break;
		case AT_FLOOR:
			
			elev_set_motor_direction(DIRN_STOP);
			queue_clearOrder(lastFloor, ORDER_DIR_BOTH);
			hw_disableOrderLamps(lastFloor);
			elev_set_door_open_lamp(1);
			startDoorTimer();
			break;
	}
	
}

order_direction_t convertMoveStateToOrderState(elev_motor_direction_t dir) {
	switch (dir) {
		case DIRN_UP:
			return ORDER_DIR_UP;
		case DIRN_DOWN:
			return ORDER_DIR_DOWN;
		case DIRN_STOP:
			return ORDER_DIR_BOTH;
	}
}

void printState() {
	printf("New state: ");
		switch (currentState) {
		case INITIALIZE:
			printf("INITIALIZE\n");
			break;
		case IDLE:
			printf("IDLE\n");
			break;
		case MOVING:
			printf("MOVING\n");
			break;
		case STOP:
			printf("STOP\n");
			break;
		case AT_FLOOR:
			printf("AT_FLOOR\n");
			break;
	}
}

void printDirection() {
	printf("Direction: ");
	switch (currentDirection) {
	case DIRN_UP:
		printf("DIRN_UP\n");
		break;
	case DIRN_DOWN:
		printf("DIRN_DOWN\n");
		break;
	case DIRN_STOP:
		printf("DIRN_STOP\n");
		break;
	}
	
}