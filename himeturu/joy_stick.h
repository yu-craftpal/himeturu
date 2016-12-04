#ifndef _INC_JOYSTICK
#define _INC_JOYSTICK

#include "arduino.h"

#define AXHISTORYNUM 10

typedef struct axis{
    int x;
    int y; 
};
typedef struct axismap {
	int max;
	int center;
	int min;
};
typedef struct mapxy {
	axismap x;
	axismap y;
};

class JoyStick {
private:

    int xpin, ypin;
    axis axhistory[AXHISTORYNUM];
	mapxy posmap;

public:

    JoyStick(int x, int y);
    axis read(boolean all);
    axis getPosition();
    axis getPositionRCFilter(double a);
    axis getPositionAveFilter();
	mapxy setCenterPosition();
	axis joymap(axis axin);
	mapxy getMap();
	mapxy setMap(int minx, int cetx, int maxx, int miny, int cety, int maxy);

};

#endif
