#include "Arduino.h"
#include "WingServoUnit.h"
#include "ics3_servo.h"

namespace Wing {
  /**************************************************
   * Class: WingServoUnit
   **************************************************/
  int WingServoUnit::pidValue(int desired) {
    int lastPropValue = propValue;
    // 偏差 (目標値から離れるほど大きく)
    propValue = desired - currValue;
    // 積分 (目標値近くで操作量を抑制)
    inteValue = lastPropValue + propValue;
    // 微分 (目標値の変更時に操作量を大きく)
    diffValue = lastPropValue - propValue;
    // 操作量 (重み付けは適度変更)
    int manipulate = (propValue * 1 / 1000 + inteValue * 3 / 100 + diffValue * 1 / 1000);
    currValue += manipulate;
    return currValue;
  }
   
  void WingServoUnit::moveServo(int pos)
  {
    IcsServo::position(servo_id, toSafe(pidValue(pos)));
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
