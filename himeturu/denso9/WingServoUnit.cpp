#include "Arduino.h"
#include "WingServoUnit.h"
#include "ics3_servo.h"

namespace Wing {
  /**************************************************
   * Class: WingServoUnit
   **************************************************/
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
  
  /**************************************************
   * Class: WingServoUnit2
   **************************************************/
  void WingServoUnit2::moveServo(int pos) {
    sv[0]->moveServo(pos);
    sv[1]->moveServo(pos);
  }
}
