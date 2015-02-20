
#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

void initialize();

void newOrder(int floor, order_direction dir);

void arrivedAtFloor(int floor);

void doorTimerDone();

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__