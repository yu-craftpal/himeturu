#include "joy_stick.h"
#include "ics3_servo.h"

IcsServo ics;
JoyStick ljoy(A1, A2);
JoyStick rjoy(A3, A4);

void setup() {
    
    Serial.begin(115200);
    ics.begin();

}

void loop() {



}
