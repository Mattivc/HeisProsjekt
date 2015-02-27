
#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "enums.h"

void sm_init();

enum order_direction;

void newOrder(int floor, enum order_direction dir);

void arrivedAtFloor(int floor);

void doorTimerDone();

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__