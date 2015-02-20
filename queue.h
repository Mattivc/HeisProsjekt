
#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

typedef enum order_direction {
	DIR_DOWN,
	DIR_UP,
	DIR_BOTH
} order_direction

void addOrder(int floor, order_direction dir);

int hasOrder(int floor, order_direction dir);

void clearOrder(int floor, order_direction dir);

void clearAllOrders();

#endif // #ifndef __INCLUDE_QUEUE_H__