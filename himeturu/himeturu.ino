#include "joy_stick.h"
#include "ics3_servo.h"

IcsServo ics;
JoyStick ljoy(A1, A2);
JoyStick rjoy(A3, A4);


void setup() {

    Serial.begin(115200);
    ics.begin();
	mapxy lmap, rmap;
	lmap = ljoy.setCenterPosition();
	rmap = rjoy.setCenterPosition();

	ics.position(13, 7500);
}

void loop() {

	axis lax = ljoy.getPosition();
	axis rax = rjoy.getPosition();
    char str[50];
    sprintf(str,"%04d, %04d, %04d, %04d", lax.x, lax.y, rax.x, rax.y);
	Serial.println(str);

	if ((-10 < lax.x && lax.x < 10) == false) {
		lax.x = map(lax.x, -100, 100, 3500, 11500);
		ics.position(2, lax.x);
	}
	else {
		ics.position(2, 7500);
	}

	if ((-10 < lax.y && lax.y < 10) == false) {
		lax.y = map(lax.y, -100, 100, 3500, 11500);
		ics.position(3, lax.y);
	}
	else {
		ics.position(3, 7500);
	}

	if ((-10 < rax.x && rax.x < 10) == false) {
		rax.x = map(rax.x, -100, 100, 3500, 11500);
		ics.position(12, rax.x);
	}
	else {
		ics.position(12, 7500);
	}

	if ((-10 < rax.y && rax.y < 10) == false) {
		rax.y = map(rax.y, -100, 100, 3500, 11500);
		ics.position(13, rax.y);
	}
	else{
		ics.position(13, 7500);
	}
    
    
}
