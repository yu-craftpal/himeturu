#include "joy_stick.h"
#include "ics3_servo.h"

IcsServo ics;
JoyStick ljoy(A2, A1);
JoyStick rjoy(A4, A3);

void setup() {

    Serial.begin(115200);
    ics.begin();
	ljoy.setCenterPosition();
	rjoy.setCenterPosition();

	ics.position(13, 7500);
}

void loop() {

	axis lax = ljoy.getPositionRCFilter(0.9);
	axis rax = rjoy.getPositionRCFilter(0.9);
    char str[50];
    sprintf(str,"%04d, %04d, %04d, %04d", lax.x, lax.y, rax.x, rax.y);
	Serial.println(str);

    lax.x = map(lax.x, -100, 100, 3500, 11500);
    lax.y = map(lax.y, -100, 100, 3500, 11500);
    rax.x = map(rax.x, -100, 100, 3500, 11500);
    rax.y = map(rax.y, -100, 100, 3500, 11500);
	//ics.position(2, lax.x);
    //ics.position(3, lax.y);
    //ics.position(12, rax.x);
	if ((-5 < rax.y && rax.y < 5) == false) {
		ics.position(13, rax.y);
	}
    
    
}
