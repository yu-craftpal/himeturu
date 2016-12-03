#include "joy_stick.h"

JoyStick::JoyStick(int x, int y){
    xpin = x;
    ypin = y;
	pinMode(xpin, INPUT);
	pinMode(ypin, INPUT);
}

axis JoyStick::read(){
	lastax.x = currentax.x;
	lastax.y = currentax.y;
    currentax.x = analogRead(xpin);
    currentax.y = analogRead(ypin);
	return currentax;
}

axis JoyStick::getPosition() {
	axis ax;
	ax = read();
	ax.x = map(ax.x, 0, 1023, -512, 512);
	ax.y = map(ax.y, 0, 1023, -512, 512);
	return ax;
}

axis JoyStick::getPositionRCFilter(double a) {
	axis ax;
	read();
	ax.x = (a * lastax.x) + ((1 - a)*currentax.x);
	ax.y = (a * lastax.y) + ((1 - a)*currentax.y);
    ax.diffx = abs(currentax.x - lastax.x);
    ax.diffy = abs(currentax.y - lastax.y);
	return ax;
}

axis JoyStick::getPositionAveFilter(int a) {
	axis ax;
	int sumx, sumy;
	for (int i = 0; i < a; i++) {
		axis tmp = read();
		sumx += tmp.x;
		sumy += tmp.y;
	}
	ax.x = sumx / a;
	ax.y = sumy / a;
	return ax;
}

axis JoyStick::getPositionFilter(){
    axis ax;
    int sumx, sumy, ave;
    ave = 100;
    for (int i = 0; i < ave; i++) {
        axis tmp = getPositionRCFilter(0.99);;
        sumx = (sumx + tmp.x) / 2;
        sumy = (sumy + tmp.y) / 2;
    }
    
    //ax.x = map(sumx, 0, 1023, 3500, 11500);
    //ax.y = map(sumy, 0, 1023, 3500, 11500);
    ax.x = sumx;
    ax.y = sumy;
    
    return ax;    
}

