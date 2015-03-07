// The state machine controlling the logic of the elevator system.
//
// 2015, Matias Christensen & Mikael Kvalvær

#ifndef __INCLUDE_STATE_MACHINE_H__
#define __INCLUDE_STATE_MACHINE_H__

#include "queue.h"

/**
  Initializes the state machine.
*/
void fsm_init();

/**
  Called when a order button is pressed.
  @param floor The floor the order came from.
  @param dir   The direction of the order.
*/
void fsm_event_newOrder(int floor, order_direction_t dir);

/**
  Called when the elevator arrives at a floor.
  @param floor The floor the elevator arrived at.
*/
void fsm_event_arrivedAtFloor(int floor);

/**
  Called when the timer elapses.
*/
void fsm_event_doorTimerDone();

/**
  Called when the stop button is pressed.
  @param floorSignal The signal from the floor sensor when the stop button is pressed.
*/
void fsm_event_stopPressed(int floorSignal);

/**
  Called when the stop button is released.
*/
void fsm_event_stopReleased();

#endif // #ifndef __INCLUDE_STATE_MACHINE_H__
