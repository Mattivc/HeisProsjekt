#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

//#include "enums.h"

enum order_direction;

void queue_addOrder(int floor, order_direction dir);

int queue_hasOrder(int floor, order_direction dir);

int queue_hasOrderInDir(int floor, order_direction dir);

void queue_clearOrder(int floor, order_direction dir);

void queue_clearAllOrders();

#endif // #ifndef __INCLUDE_QUEUE_H__