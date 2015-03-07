// File storing the orders that are currently recived.
//
// 2015, Matias Christensen & Mikael Kvalvær

#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

// Enum describing the direction states of orders.
typedef enum tag_order_direction {
	ORDER_DIR_UP   = 0,
    ORDER_DIR_DOWN = 1,
    ORDER_DIR_BOTH = 2
} order_direction_t;

/**
  Add an order to the queue.
  @param floor The origin floor of the order.
  @param dir   The direction of the order.
*/
void queue_addOrder(int floor, order_direction_t dir);

/**
  Check if the the queue has a specific order.
  @param floor The origin floor of the order.
  @param dir   The direction of the order.
*/
int queue_hasOrder(int floor, order_direction_t dir);

/**
  Check if there exist a order in any floor below or above a given floor.
  @param floor The floor we are checking from.
  @param dir   Indicates whether we are checking above or below the given floor.
*/
int queue_hasOrderInDir(int floor, order_direction_t dir);

/**
  Clear an order from the queue.
  @param floor The origin floor of the order.
  @param dir   The direction of the order.
*/
void queue_clearOrder(int floor, order_direction_t dir);

/**
  Remove all orders from the queue.
*/
void queue_clearAllOrders();

#endif // #ifndef __INCLUDE_QUEUE_H__
