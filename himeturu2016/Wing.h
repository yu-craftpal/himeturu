#ifndef __WING_H__
#define __WING_H__
#include "Arduino.h"
#include "debug.h"
#include "WingServo.h"

// 翼関係
namespace Wing {

  /**************************************************
   * Class: Wing::Elevon
   **************************************************/
  class Elevon : public WingServo {
    private:
      const int pos_center, pos_up, pos_down;
      int refactorValue(int value);
      int getPosUp(int value, int fromLow = 0, int fromHigh = 512);
      int getPosDown(int value, int fromLow = 0, int fromHigh = 512);

    public:
      Elevon(InterfaceServo *servo_left, InterfaceServo *servo_right, int pos_center, int area)
      : WingServo(servo_left, servo_right) //, pos_center, pos_center + area, pos_center - area)
      , pos_center(pos_center)
      , pos_up(pos_center + area)
      , pos_down(pos_center - area) { }

      // エレボンを初期値に戻す
      void center(enum Side side);

      // エレボンを上げる
      void up(enum Side side, int value);

      // エレボンを下げる
      void down(enum Side side, int value);

      void interrupt(String str, int pos_x, int pos_y);

      String toString();
  };

  /**************************************************
   * Class: Wing::Spoiler
   **************************************************/
  class Spoiler : public WingServo {
    private:
      const int pos_center, pos_max;
      int refactorValue(int value);
      int getPosOpen(int value, int fromLow = 0, int fromHigh = 512);

    public:
      Spoiler(InterfaceServo *servo_left, InterfaceServo *servo_right, int pos_center, int pos_max)
      : WingServo(servo_left, servo_right)
      , pos_center(pos_center)
      , pos_max(pos_max) { }

      // スポイラを初期値に戻す
      void close(enum Side side);
      
      // スポイラを上げる
      void open(enum Side side, int value);

      /* 左右のスポイラを比率を考え上げる
       * <引数>
       * side : 比率を指定する翼側
       * raito: 比率 0~1000 */
      void open(enum Side side, int value, int raito);

      void interrupt(String str, int pos_x, int pos_y);

      String toString();
  };

}
#endif
