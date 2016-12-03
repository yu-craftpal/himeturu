#ifndef _INC_JOYSTICK
#define _INC_JOYSTICK

#include "arduino.h"
#include <PID_v1.h>

typedef struct axis{
    int x;
    int y; 
    int diffx;
    int diffy;
};

class JoyStick {
private:

    int xpin, ypin;
    axis lastax, currentax;  

public:

    JoyStick(int x, int y);
    axis read();
    axis getPosition();
    axis getPositionRCFilter(double a);
    axis getPositionAveFilter(int a);
    axis getPositionFilter();

};

#endif
