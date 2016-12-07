#include "Arduino.h"
#include "WingServo.h"

namespace Wing {

  /**************************************************
   * Class: WingServo
   **************************************************/
   
  void WingServo::moveServo(int pos, enum Side side) {
    switch (side) {
      case Left:
        sv_left->moveServo(pos);
        break;
      case Right:
        sv_right->moveServo(pos);
        break;
      case Both:
        moveServo(pos, Left); moveServo(pos, Right);
        break;
    }
  }

}
