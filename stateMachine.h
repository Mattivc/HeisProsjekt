
#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "enums.h"

/**
  Initializes the state machine.

  @param	none

  @return	none
*/
void fsm_init();

/**
  Executes a new order.

  @param    floor The floor the order came from.
  			dir The direction of the incoming order.

  @return 	none

*/
void fsm_event_newOrder(int floor, enum order_direction dir);

/**
  Executes event if elevator has arrived at the desired floor. 

  @param    floor The floor the order came from.

  @return 	none

*/
void fsm_event_arrivedAtFloor(int floor);

/**
  Executes event if door timer is done.

  @param    none

  @return 	none

*/
void fsm_event_doorTimerDone();

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__