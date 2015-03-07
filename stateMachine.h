
#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "queue.h"

void fsm_init();

void fsm_event_newOrder(int floor, order_direction_t dir);

void fsm_event_arrivedAtFloor(int floor);

void fsm_event_doorTimerDone();

void fsm_event_stopPressed(int floorSignal);

void fsm_event_stopReleased(int floorSignal);

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__