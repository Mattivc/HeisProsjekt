// The state machine controlling the logic of the elevator system.
//
// 2015, Matias Christensen & Mikael Kvalvær

#include "stateMachine.h"
#include "queue.h"
#include "elev.h"
#include "hw.h"
#include "timer.h"

typedef enum tag_fsm_state {
	INITIALIZE = 0,
	IDLE       = 1,
	MOVING     = 2,
	STOP       = 3,
	AT_FLOOR   = 4
} fsm_state_t;

static fsm_state_t currentState;
static elev_motor_direction_t currentDirection = DIRN_STOP;
static int lastFloor = -1;
static int returnedFromStop = 0;

// *** Internal function decleration ***

void setState(fsm_state_t newState);
order_direction_t convertMoveStateToOrderState(enum tag_elev_motor_direction dir);
void reverseDirection();

// *** External functions implementation ***

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
			elev_set_button_lamp((int)dir, floor, 1); 
			queue_addOrder(floor, dir);

			int relative_dir = floor - lastFloor;
			if (returnedFromStop) { // We have gotten our first order after stopping betwene two floors.
				if (relative_dir == 0) { // We where asked to return to the floor we came from before we stopped.
					relative_dir = -(int)currentDirection;
					lastFloor = lastFloor - (int)currentDirection;
				}
			}

			if (relative_dir < 0) {
				currentDirection = DIRN_DOWN;
				setState(MOVING);
			} else if (relative_dir > 0) {
				currentDirection = DIRN_UP;
				setState(MOVING);
			} else {
				setState(AT_FLOOR);
			}
			break;
		}
		case AT_FLOOR:
		case MOVING:
			if (floor == lastFloor && currentState == AT_FLOOR) {
				timer_start(); // We got an order for the same floor that we are currently in, so hold the door for a bit longer.
			} else {
				elev_set_button_lamp((int)dir, floor, 1); 
				queue_addOrder(floor, dir);
			}	
			break;
	}
}

void fsm_event_arrivedAtFloor(int floor) {
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
			if (floor == 0 || floor == 3) { // We hit a top or bottom floor, so there has to be an order here since we went here
				reverseDirection();
				setState(AT_FLOOR);
			} else if (queue_hasOrder(floor, convertMoveStateToOrderState(currentDirection)) || // Does this floor has an order in our current direction?
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


void fsm_event_stopPressed(int floorSignal) {
	switch (currentState) {
		case INITIALIZE:
			break;
		case IDLE:
		case MOVING:
		case STOP:
		case AT_FLOOR:
			if (floorSignal != -1) { elev_set_door_open_lamp(1); }
			elev_set_stop_lamp(1);
			setState(STOP);
			break;
	}
}

void fsm_event_stopReleased() {
	elev_set_stop_lamp(0);
	elev_set_door_open_lamp(0);
	switch (currentState) {
		case INITIALIZE:
		case IDLE:
		case MOVING:
		case AT_FLOOR:
			break;
		case STOP:
			returnedFromStop = 1;
			setState(IDLE);
			break;
	}
}

// *** Internal function implementation ***

void setState(fsm_state_t newState) {
	currentState = newState;

	switch (newState) {
		case INITIALIZE:
			break;
		case IDLE:
			break;
		case MOVING:
			if (returnedFromStop) {
				elev_set_motor_direction(currentDirection);
				returnedFromStop = 0;
				break;
			}

			if (queue_hasOrderInDir(lastFloor, convertMoveStateToOrderState(currentDirection))) {
				elev_set_motor_direction(currentDirection);
			} else if (queue_hasOrderInDir(lastFloor, convertMoveStateToOrderState(currentDirection*-1))) {
				reverseDirection();
				elev_set_motor_direction(currentDirection);
			} else {
				setState(IDLE);
			}
			
			break;
		case STOP:
			elev_set_motor_direction(DIRN_STOP);
			queue_clearAllOrders();
			hw_resetAllOrderLamps();
			break;
		case AT_FLOOR:
			elev_set_motor_direction(DIRN_STOP);
			queue_clearOrder(lastFloor, ORDER_DIR_BOTH);
			hw_resetOrderLamps(lastFloor);
			elev_set_door_open_lamp(1);
			timer_start();
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

void reverseDirection() {
	switch (currentDirection) {
	case DIRN_UP:
		currentDirection = DIRN_DOWN;
		break;
	case DIRN_DOWN:
		currentDirection = DIRN_UP;
		break;
	case DIRN_STOP:
		break;
	}
}
