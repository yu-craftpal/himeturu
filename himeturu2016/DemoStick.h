#pragma once

#include "Arduino.h"
#include "debug.h"
#include "Stick.h"

#include <vector>

using std::vector;

// アナログスティック関係
namespace DemoStick {

	// デモスティッククラス
	class DemoStick : public AnalogStick::Stick {
	private:
		vector<int> schListX;
		vector<int> schListY;
		size_t sdl_count_x = 0;
		size_t sdl_count_y = 0;
		int sdl_current_x = 0;
		int sdl_current_y = 0;

		int analogRead(int p) {
			static unsigned long lastTime = millis();
			
			using namespace AnalogStick;
			
			if (millis() - lastTime > 2000) {
				lastTime = millis();
				sdl_current_x = (sdl_current_x + 1) % sdl_count_x;
				sdl_current_y = (sdl_current_y + 1) % sdl_count_y;
			}

			if (p == pin[Y]) {
				return schListY[sdl_current_y];
			}
			else if (p == pin[X]) {
				return schListX[sdl_current_x];
			}
			// 例外ピンの指定対策
			else return medium;
		}
		void setPos() {
			using namespace AnalogStick;
			if (!reversed[X]) pos[X] = analogRead(pin[X]); // 0~1023
			else pos[X] = maximum - analogRead(pin[X]);    // 1023~0
			if (!reversed[Y]) pos[Y] = analogRead(pin[Y]); // 0~1023
			else pos[Y] = maximum - analogRead(pin[Y]);    // 1023~0
			if (refactor) { // 値が範囲外に出た場合に範囲内に収める
				if (pos[X] < minimum) pos[X] = minimum;
				else if (pos[X] > maximum) pos[X] = maximum;
				if (pos[Y] < minimum) pos[Y] = minimum;
				else if (pos[Y] > maximum) pos[Y] = maximum;
			}
		}
		// スケジュール初期化
		void initialization() {
			schListX.push_back(medium);
			schListX.push_back(maximum);
			schListX.push_back(medium);
			schListX.push_back(minimum);
			schListX.push_back(medium);
			schListX.push_back(medium);
			sdl_count_x = schListX.size();

			schListY.push_back(medium);
			schListY.push_back(medium);
			schListY.push_back(medium);
			schListY.push_back(medium);
			schListY.push_back(medium);
			schListY.push_back(minimum);
			sdl_count_y = schListY.size();
		}
	public:
		DemoStick(int pin_x, int pin_y, int threshold = 100
			, bool reverse_x = false, bool reverse_y = false, bool refactor = true)
			: Stick(pin_x, pin_y, threshold, reverse_x, reverse_y, refactor)
		{
			initialization();
		}
		// 割り込み処理
		void interrupt() {
			// 初期化, スティックポジションをフィールドにセット
			setPos();
		}
		String toString() { return "DemoStick"; }
	};
}
