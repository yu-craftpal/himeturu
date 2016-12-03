#include "joy_stick.h"
#include "ics3_servo.h"

IcsServo ics;
JoyStick ljoy(A1, A2);
JoyStick rjoy(A3, A4);

void setup() {

    Serial.begin(115200);
    ics.begin();
    ics.position(3, 9500);
}

void loop() {

	axis lax = ljoy.getPositionRCFilter(0.99);
	axis rax = rjoy.getPositionRCFilter(0.99);
    char str[50];
    sprintf(str,"%04d, %04d, %04d, %04d", lax.x, lax.y, rax.x, rax.y);
	Serial.println(str);

    lax.x = map(lax.x, 0, 1023, 3500, 11500);
    lax.y = map(lax.y, 0, 1023, 3500, 11500);
    rax.x = map(rax.x, 0, 1023, 3500, 11500);
    rax.y = map(rax.y, 0, 1023, 3500, 11500);
	//ics.position(2, lax.x);
    //ics.position(3, lax.y);
    //ics.position(12, rax.x);
    ics.position(13, rax.y);
    
}
