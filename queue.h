#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

typedef enum order_direction {
	ORDER_DIR_UP   = 0,
    ORDER_DIR_DOWN = 1,
    ORDER_DIR_BOTH = 2
} order_direction_t;

void queue_addOrder(int floor, order_direction_t dir);

int queue_hasOrder(int floor, order_direction_t dir);

int queue_hasOrderInDir(int floor, order_direction_t dir);

void queue_clearOrder(int floor, order_direction_t dir);

void queue_clearAllOrders();

void queue_printState();

#endif // #ifndef __INCLUDE_QUEUE_H__