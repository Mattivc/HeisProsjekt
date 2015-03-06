#ifndef __INCLUDE_TIMER_H__
#define __INCLUDE_TIMER_H__
/**
  Activates door timer.
*/
void startDoorTimer();

/**
  Checks if door timer has been set for three or more seconds.
  @return 1 if true, 0 if false.
*/
int isDoorTimerDone();

/**
  Resets the door timer.
*/
void resetDoorTimer();


#endif // ifndef __INCLUDE_TIMER_H__