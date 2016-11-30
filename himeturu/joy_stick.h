#ifndef _INC_JOYSTICK
#define _INC_JOYSTICK

#include "arduino.h"


class JoyStick {
private:
    int xpin, ypin;
    int xaxis, yaxis;
    
public:

    JoyStick(int x, int y);

};

#endif
