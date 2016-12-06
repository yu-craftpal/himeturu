#include "Arduino.h"
#include "WingServoUnit.h"
#include "ics3_servo.h"

namespace Wing {
  /**************************************************
   * Class: WingServoUnit
   **************************************************/
  WingServoUnit::WingServoUnit(unsigned char servo_id, int pos_center, int area_max, int area_min)
  : servo_id(servo_id)
  , pos_center(pos_center)
  , area_max(area_max)
  , area_min(area_min)
  , IcsServo()
  {
    IcsServo::begin();
  }
  void WingServoUnit::moveServo(int pos)
  {
    IcsServo::position(servo_id, toSafe(pos));
  }

  int WingServoUnit::toSafe(int pos)
  {
    if (pos < area_min) return area_min;
    if (pos > area_max) return area_max;
    return pos;
  }
}
