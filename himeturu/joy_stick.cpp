#include "joy_stick.h"
/// �C���X�^���X�������ɌĂ΂��
JoyStick::JoyStick(int x, int y) {
	xpin = x;
	ypin = y;
	pinMode(xpin, INPUT);
	pinMode(ypin, INPUT);
	for (int i = AXHISTORYNUM - 1; i >= 0; i--) {
		axhistory[i].x = 0;
		axhistory[i].y = 0;
	}
}
/// �A�i���O�l���擾����
axis JoyStick::read(boolean all) {
	if (all == true) {
		for (int i = AXHISTORYNUM - 1; i >= 0; i--) {
			axhistory[i].x = analogRead(xpin);
			axhistory[i].y = analogRead(ypin);
		}
	}
	else {
		for (int i = AXHISTORYNUM - 1; i > 0; i--) {
			axhistory[i] = axhistory[i - 1];
		}
	}
	axhistory[0].x = analogRead(xpin);
	axhistory[0].y = analogRead(ypin);
	return axhistory[0];
}
/// ���݂̃X�e�B�b�N�ʒu���擾����
axis JoyStick::getPosition() {
	axis ax;
	ax = read(false);
	ax = joymap(ax);
	return ax;
}
/// RC�t�B���^�����������݂̃X�e�B�b�N�ʒu���擾����
axis JoyStick::getPositionRCFilter(double a) {
	axis ax;
	read(false);
	ax.x = (a * axhistory[1].x) + ((1 - a) * axhistory[0].x);
	ax.y = (a * axhistory[1].y) + ((1 - a) * axhistory[0].y);
	ax = joymap(ax);
	return ax;
}
/// �ړ����σt�B���^�����������݂̃X�e�B�b�N�ʒu���擾����
axis JoyStick::getPositionAveFilter() {
	axis ax;
	long sumx, sumy;
	sumx = sumy = 0;
	read(false);
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
/// �֐����s���̃X�e�B�b�N��Ԃ𒆉��l�Ƃ��C�ő�l�C�ŏ��l���v�Z����
mapxy JoyStick::setCenterPosition() {
	axis ax;
	read(true);
	long sumx, sumy;
	sumx = sumy = 0;
	for (int i = 0; i < AXHISTORYNUM; i++) {
		axis tmp = axhistory[i];
		sumx += tmp.x;
		sumy += tmp.y;
	}
	ax.x = sumx / AXHISTORYNUM;
	ax.y = sumy / AXHISTORYNUM;
	posmap.x.center = ax.x;
	posmap.y.center = ax.y;

	int lowdiff = posmap.x.center - 1;
	int highdiff = 1023 - posmap.x.center;
	if (lowdiff == highdiff) {
		posmap.x.min = 1;
		posmap.x.max = 1023;
	}
	else if (lowdiff < highdiff) {
		posmap.x.min = 1;
		posmap.x.max = posmap.x.center + (posmap.x.center - 1);
	}
	else if (lowdiff > highdiff) {
		posmap.x.min = posmap.x.center - (1023 - posmap.x.center);
		posmap.x.max = 1023;
	}

	lowdiff = posmap.y.center - 1;
	highdiff = 1023 - posmap.y.center;
	if (lowdiff == highdiff) {
		posmap.y.min = 1;
		posmap.y.max = 1023;
	}
	else if (lowdiff < highdiff) {
		posmap.y.min = 1;
		posmap.y.max = posmap.y.center + (posmap.y.center - 1);
	}
	else if (lowdiff > highdiff) {
		posmap.y.min = posmap.y.center - (1023 - posmap.y.center);
		posmap.y.max = 1023;
	}

	return posmap;
}
/// setCenterPosition�̌v�Z���ʂ����Ƃ�-100�`100�͈̔͂ɕϊ�����
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
