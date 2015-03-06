#ifndef __INCLUDE_QUEUE_H__
#define __INCLUDE_QUEUE_H__

//#include "enums.h"

enum order_direction;

/**
  Adds a new order to the order queue.

  @param	floor Floor the order came from.
  			dir The direction of the order.

  @return 	none

*/
void queue_addOrder(int floor, order_direction dir);

/**
	Checks whether there is an order in a particular floor and direction.

	@param	floor Floor that is being checked.
			dir Direction that is being checked.

	@return	1 if true, 0 if false.

*/
int queue_hasOrder(int floor, order_direction dir);

/**
	Checks whether there is an order in a particular direction.

	@param	floor Reference floor.
			dir Direction that is being checked.

	@return	1 if true, 0 if false.

*/
int queue_hasOrderInDir(int floor, order_direction dir);

/**
	Clears a specific order in the order table.

	@param	floor Order is being cleared from the specific floor.
			dir Order is being cleared from the specific direction.

	@return	none

*/
void queue_clearOrder(int floor, order_direction dir);

/**
	Clears all orders of the order table.

	@param	none

	@return	none
	
*/
void queue_clearAllOrders();

#endif // #ifndef __INCLUDE_QUEUE_H__