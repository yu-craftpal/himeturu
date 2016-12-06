#ifndef __WING_SERVO_UNIT_H__
#define __WING_SERVO_UNIT_H__
#include "Arduino.h"
#include "ics3_servo.h"

namespace Wing {

  /**************************************************
   * Class: WingServoUnit
   **************************************************/
  class WingServoUnit : private IcsServo {
    private:
      int toSafe(int pos);

    public:
      const unsigned char servo_id;
      const int pos_center;
      const int area_max;
      const int area_min;

      WingServoUnit(unsigned char servo_id, int pos_center, int area_max, int area_min);
      void moveServo(int pos);
  };
}
#endif
