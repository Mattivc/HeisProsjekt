


#include "stateMachine.h"

typedef enum state {
	INITIALIZE,
	IDLE,
	MOVING,
	STOP,
	AT_FLOOR
} state

state currentState;

void initialize() {

}

void newOrder(int floor, order_direction dir) {
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

void arrivedAtFloor(int floor) {
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