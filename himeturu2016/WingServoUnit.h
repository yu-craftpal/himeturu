#ifndef __WING_SERVO_UNIT_H__
#define __WING_SERVO_UNIT_H__
#include "Arduino.h"
#include "ics3_servo.h"

namespace Wing {

  class InterfaceServo {
    public:
      virtual void moveServo(int pos) = 0;
  };

  /**************************************************
   * Class: WingServoUnit
   **************************************************/
  class WingServoUnit : private IcsServo, public InterfaceServo {
    private:
      int toSafe(int pos);

      int currValue;      // 現在の値
      int propValue;      // 偏差
      int inteValue;      // 積分値
      int diffValue;      // 微分値
      int pidValue(int desired);
      
    public:
      const unsigned char servo_id;
      const int pos_center;
      const int area_max;
      const int area_min;

      WingServoUnit(unsigned char servo_id, int pos_center, int area_max, int area_min)
      : servo_id(servo_id)
      , pos_center(pos_center)
      , area_max(area_max)
      , area_min(area_min)
      , IcsServo()
      {
        IcsServo::begin();
        // PID
        currValue = pos_center; // 初めの値は初期位置
        propValue = 0;          // 初めの偏差は0
      }
      void moveServo(int pos);
  };

  /**************************************************
   * Class: WingServoUnit2
   **************************************************/
  class WingServoUnit2 : public InterfaceServo {
    private:
      WingServoUnit *sv[2];
    public:
      WingServoUnit2(WingServoUnit *sv_0, WingServoUnit *sv_1)
      {
        sv[0] = sv_0;
        sv[1] = sv_1;
      }
      void moveServo(int pos);
  };

}
#endif
