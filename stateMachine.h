
#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "enums.h"

void fsm_init();

void fsm_event_newOrder(int floor, enum order_direction dir);

void fsm_event_arrivedAtFloor(int floor);

void fsm_event_doorTimerDone();

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__