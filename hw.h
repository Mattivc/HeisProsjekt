// Wrapper for the elev.c file, providing additional functionality.
//
// 2015, Matias Christensen & Mikael Kvalvær

#ifndef __INCLUDE_HW_H__
#define __INCLUDE_HW_H__

/**
  Updates all the hardware parameters in the status array.
  @param statusArray Pointer to a array for storing button status.
*/
void hw_updateInputStatusArray(int *statusArray);

/**
  Resets the order lamps at a floor.
  @param floor The floor of the button lamps to disable.
*/
void hw_resetOrderLamps(int floor);

/**
	Resets all order lamps.	
*/
void hw_resetAllOrderLamps();

/**
	Resets all maps, including stop lamp and door open lamp.
*/
void hw_resetAllLamps();

#endif // #ifndef __INCLUDE_HW_H__
