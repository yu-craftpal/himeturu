#ifndef __WING_SERVO_H__
#define __WING_SERVO_H__
#include "Arduino.h"
#include "WingServoUnit.h"

namespace Wing {
  // 翼側
  enum Side { Left, Right, Both };

  /**************************************************
   * Class: WingServo
   **************************************************/
  class WingServo {
    private:
      InterfaceServo *sv_left;
      InterfaceServo *sv_right;

    public:
      WingServo(InterfaceServo *sv_left, InterfaceServo *sv_right)
      {
        this->sv_left = sv_left;
        this->sv_right= sv_right;
      }
      void moveServo(int pos, enum Side side);
      virtual void interrupt(String str, int pos_x, int pos_y) = 0;
  };

}
#endif
