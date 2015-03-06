#include "enums.h"

int orderArray[2][3] = {{0}};


void addOrder(int floor, order_direction dir) {
	switch (dir) {
		case ORDER_DIR_DOWN:
			orderArray[0][floor-2] = 1;
			break;
		case ORDER_DIR_UP:
			orderArray[1][floor-1] = 1;
			break;
		case ORDER_DIR_BOTH:
			orderArray[0][floor-2] = 1;
			orderArray[1][floor-1] = 1;
			break;
	}
}

int hasOrder(int floor, order_direction dir) {
	switch (dir) {
		case ORDER_DIR_DOWN:
			return orderArray[0][floor-2];
		case ORDER_DIR_UP:
			return orderArray[1][floor-1];
		case ORDER_DIR_BOTH:
			return orderArray[0][floor-2] + orderArray[1][floor-1];
	}
}

int hasOrderInDir(int floor, order_direction dir) {
	if (dir == ORDER_DIR_UP) {
		return hasOrderAbove(floor)
	} else {
		return hasOrderBelow(floor)
	}
}

int hasOrderAbove(int floor) {
	for (int i = floor+1; i < 4; ++i) {
		if (hasOrder(floor, ORDER_DIR_BOTH) {
			return 1;
		}
	}
	return 0;
}

int hasOrderBelow(int floor) {
	for (int i = floor-1; i >= 0; --i) {
		if (hasOrder(floor, ORDER_DIR_BOTH) {
			return 1;
		}
	}
	return 0;
}

void clearOrder(int floor, order_direction dir) {
	switch (dir) {
		case ORDER_DIR_DOWN:
			orderArray[0][floor-2] = 0;
			break;
		case ORDER_DIR_UP:
			orderArray[1][floor-1] = 0;
			break;
		case ORDER_DIR_BOTH:
			orderArray[0][floor-2] = 0;
			orderArray[1][floor-1] = 0;
			break;
	}
}

void clearAllOrders() {
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 3; ++j) {
			orderArray[i][j] = 0;
		}
	}
}