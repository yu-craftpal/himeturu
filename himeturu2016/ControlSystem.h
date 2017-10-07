#ifndef __CONTROL_SYSTEM_H__
#define __CONTROL_SYSTEM_H__

#include "Arduino.h"
#include "WingServo.h"

// コントローラー
namespace ControlSystem {

  /**************************************************
   * Class: ControlSystem::Controler
   **************************************************/
  class Controler {
    private:
      AnalogStick::Stick *stick;
      Wing::WingServo *servo;

    public:
      /* <引数>
       * *p_stick: スティック インスタンスへのポインタ
       * *p_servo: ベースサーボ インスタンスへのポインタ */
      Controler(AnalogStick::Stick *p_stick, Wing::WingServo *p_servo)
      : stick(p_stick), servo(p_servo) { }

      // 毎回のループでの割り込み処理
      void interrupt() {
        stick->interrupt();
        servo->interrupt(
          stick->posToStr(),
          stick->getValue(AnalogStick::X),
          stick->getValue(AnalogStick::Y)
        );
      }

	  void setStick(AnalogStick::Stick *s) {
		  stick = s;
	  }
  };

}

#endif
