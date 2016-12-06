//飛行機を上から見たとき、進行方向に対して左右を定義する
//例：左翼エレボンのD部左側のサーボ，左翼エレボンのD部の翼端側についているサーボ

#ifndef _INC_WING
#define _INC_WING

#include "arduino.h"
#include "ics3_servo.h"

#define DEADBAND 10

#define ELEBONCENTER 7180 //エレボン中央位置
#define ELEBONRANGE 650  //エレボン可動範囲
#define SPOILERCENTER 7250 //スポイラー初期位置
#define SPOILERMAX 11500 //スポイラー可動最大値

//片翼のサーボIDの定義
typedef struct wingservo {
	int spoiler;	//スポイラー
	int elebon_el;	//エレボンのE部左側
	int elebon_er;	//エレボンのE部右側
	int elebon_dl;	//エレボンのD部左側
	int elebon_dr;	//エレボンのD部右側
};

//片翼のサーボ位置の定義
typedef struct wingposition {
	int spoiler;	//スポイラー
	int elebon_e;	//エレボンのE部
	int elebon_d;	//エレボンのD部
};

class HimeturuWing {
private:

	IcsServo ics;
	wingservo winglsv;
	wingservo wingrsv;
	wingposition winglpos;
	wingposition wingrpos;

public:

	HimeturuWing(wingservo l, wingservo r);

	void wakeup();
	void setSpoiler(axis ax);
	void setElebon(axis ax);

};

#endif
