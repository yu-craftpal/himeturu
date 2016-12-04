#include "joy_stick.h"

JoyStick::JoyStick(int x, int y){
    xpin = x;
    ypin = y;
	pinMode(xpin, INPUT);
	pinMode(ypin, INPUT);
	for (int i = AXHISTORYNUM; i >= 0; i--) {
		axhistory[i].x = 0;
		axhistory[i].y = 0;
	}
}

axis JoyStick::read(boolean all = false){
	if (all == true) {
		for (int i = AXHISTORYNUM; i > 0; i--) {
			axhistory[i].x = analogRead(xpin);
			axhistory[i].y = analogRead(ypin);
		}
	}
	else{
		for (int i = AXHISTORYNUM; i > 0; i--) {
			axhistory[i] = axhistory[i - 1];
		}
	}
	axhistory[0].x = analogRead(xpin);
	axhistory[0].y = analogRead(ypin);
	return axhistory[0];
}

axis JoyStick::getPosition() {
	axis ax;
	ax = read();
	ax = joymap(ax);
	return ax;
}

axis JoyStick::getPositionRCFilter(double a) {
	axis ax;
	read();
	ax.x = (a * axhistory[1].x) + ((1 - a) * axhistory[0].x);
	ax.y = (a * axhistory[1].y) + ((1 - a) * axhistory[0].y);
	ax = joymap(ax);
	return ax;
}

axis JoyStick::getPositionAveFilter() {
	axis ax;
	int sumx, sumy;
	read();
	for (int i = 0; i < AXHISTORYNUM; i++) {
		axis tmp = axhistory[i];
		sumx += tmp.x;
		sumy += tmp.y;
	}
	ax.x = sumx / AXHISTORYNUM;
	ax.y = sumy / AXHISTORYNUM;
	ax = joymap(ax);
	return ax;
}

mapxy JoyStick::setCenterPosition() {
	axis ax;
	mapxy axm;
	read(true);
	int sumx, sumy;
	for (int i = 0; i < AXHISTORYNUM; i++) {
		axis tmp = axhistory[i];
		sumx += tmp.x;
		sumy += tmp.y;
	}
	ax.x = sumx / AXHISTORYNUM;
	ax.y = sumy / AXHISTORYNUM;
	axm.x.center = ax.x;
	axm.y.center = ax.y;
	
	int lowdiff = ax.x - 1;
	int highdiff = 1023 - ax.x;
	if (lowdiff == highdiff) {
		axm.x.min = 1;
		axm.x.max = 1023;
	}
	else if (lowdiff < highdiff) {
		axm.x.min = 1;
		axm.x.max = axm.x.center + (axm.x.center - 1);
	}
	else if (lowdiff > highdiff) {
		axm.x.min = axm.x.center - (1023 - axm.x.center);
		axm.x.max = 1023;
	}

	lowdiff = ax.y - 1;
	highdiff = 1023 - ax.y;
	if (lowdiff == highdiff) {
		axm.y.min = 1;
		axm.y.max = 1023;
	}
	else if (lowdiff < highdiff) {
		axm.y.min = 1;
		axm.y.max = axm.y.center + (axm.y.center - 1);
	}
	else if (lowdiff > highdiff) {
		axm.y.min = axm.y.center - (1023 - axm.y.center);
		axm.y.max = 1023;
	}
	posmap = axm;
	return axm;
}

axis JoyStick::joymap(axis axin) {
	axis axout;
	axout.x = map(axin.x, posmap.x.min, posmap.x.max, -100, 100);
	if (axout.x < -100)	axout.x = -100;
	else if (axout.x > 100)	axout.x = 100;
	axout.y = map(axin.y, posmap.y.min, posmap.y.max, -100, 100);
	if (axout.y < -100)	axout.y = -100;
	else if (axout.y > 100)	axout.y = 100;
	return axout;
}