#ifndef _INC_JOYSTICK
#define _INC_JOYSTICK

#include "arduino.h"

#define AXHISTORYNUM 10	//どれだけの履歴を残すか

//xy軸を表す
typedef struct axis{
    int x;
    int y;
};
//ジョイスティックの最小，中央，最大を表す
typedef struct axismap {
	int max;
	int center;
	int min;
};
//axismapをxy軸をセットにしたもの
typedef struct mapxy {
	axismap x;
	axismap y;
};

//ジョイスティックに関するクラス
class JoyStick {
private:

    int xpin, ypin;					//ジョイスティックの繋がっているピン番号
    axis axhistory[AXHISTORYNUM];	//ジョイスティックのアナログ値
	mapxy posmap;					//ジョイスティックの範囲

public:

	/// <summary>
	/// インスタンス生成時に呼ばれる
	/// </summary>
	/// <param name="x">X軸のピン番号</param>
	/// <param name="y">y軸のピン番号</param>
    JoyStick(int x, int y);
	/// <summary>
	/// アナログ値を取得する
	/// </summary>
	/// <param name="all">履歴をすべて更新するか</param>
	/// <returns>現在のアナログ値を返す</returns>
    axis read(boolean all);
	/// <summary>
	/// 現在のスティック位置を取得する
	/// </summary>
	/// <returns>-100～100の範囲（ジョイスティック中央で0）</returns>
    axis getPosition();
	/// <summary>
	/// RCフィルタをかけた現在のスティック位置を取得する
	/// </summary>
	/// <param name="a">RCフィルタの強度（0～0.99，推奨0.9）</param>
	/// <returns>-100～100の範囲（ジョイスティック中央で0）</returns>
    axis getPositionRCFilter(double a);
	/// <summary>
	/// 移動平均フィルタをかけた現在のスティック位置を取得する
	/// </summary>
	/// <returns>-100～100の範囲（ジョイスティック中央で0）</returns>
    axis getPositionAveFilter();
	/// <summary>
	/// 関数実行時のスティック状態を中央値とし，最大値，最小値を計算する
	/// </summary>
	/// <returns>中央値が400の場合，最小値１，最大値799となる（アナログ値が0～1023の場合）</returns>
	mapxy setCenterPosition();
	/// <summary>
	/// setCenterPositionの計算結果をもとに-100～100の範囲に変換する
	/// </summary>
	/// <param name="axin">アナログ値</param>
	/// <returns>-100～100の範囲（ジョイスティック中央で0）</returns>
	axis joymap(axis axin);

};

#endif
