#include "Arduino.h"
#include "debug.h"
// アナログスティック関係
namespace AnalogStick {
// スティック軸
typedef enum Direction { X, Y, Both };
// スティック方向
typedef enum Position { Top, Bottom, Left, Right, Medium, PosLen = 9 };

// スティッククラス
class Stick {
  private:
    int pos[2];                     // ポジション
    int pin[2];                     // ピン番号
    const bool reversed[2];         // 反転
    const bool refactor;            // リファクタリング
    const int threshold;            // 閾値
    const int minimum = 0;          // 最小値
    const int maximum = 1023;       // 最大値
    const int medium = maximum / 2; // 中央値
    // スティックからの入力値をセット
    void setPos() {
      if (!reversed[X]) pos[X] =  analogRead(pin[X]); // 0~1023
      else pos[X] =  maximum - analogRead(pin[X]);    // 1023~0
      if (!reversed[Y]) pos[Y] =  analogRead(pin[Y]); // 0~1023
      else pos[Y] =  maximum - analogRead(pin[Y]);    // 1023~0
      if (refactor) { // 値が範囲外に出た場合に範囲内に収める
        if (pos[X] < minimum) pos[X] = minimum;
        else if (pos[X] > maximum) pos[X] = maximum;
        if (pos[Y] < minimum) pos[Y] = minimum;
        else if (pos[Y] > maximum) pos[Y] = maximum;
      }
    }
    // スティックが指定軸(direc)に対して desired 付近の値かどうか
    bool checkPos(Direction direc, int desired) {
      if (direc == X || direc == Y) {
        return abs(pos[direc] - desired) < threshold / 2;
      } else if (direc == Both) {
        return checkPos(X, desired) && checkPos(Y, desired);
      } else {
        return false;  // Error
      }
    }
    bool checkPos(Direction direc, int start_value, int end_value) {
      if (direc == X || direc == Y) {
        return pos[direc] >= start_value && pos[direc] <= end_value;
      } else {
        return false;  // Error
      }
    }
    // 現在のスティック位置を返す(FlagBit)
    Position getPos() {
      int buff = 0;
      if (checkPos(Both, medium)) bitSet(buff, Medium);
      else {
        if (checkPos(X, minimum, medium - (threshold / 2))) bitSet(buff, Left);
        else if (checkPos(X, medium + (threshold / 2), maximum)) bitSet(buff, Right);
        if (checkPos(Y, minimum, medium - (threshold / 2))) bitSet(buff, Bottom);
        else if (checkPos(Y, medium + (threshold / 2), maximum)) bitSet(buff, Top);
      }
      return (Position)buff;
    }
  public:
    // <引数> : ピンX, ピンY, 閾値, X反転, Y反転, リファクタリング
    Stick(int pin_x, int pin_y, int threshold = 100
          , bool reverse_x = false, bool reverse_y = false, bool refactor = true)
      : threshold(threshold), refactor(refactor), pin{pin_x, pin_y}
      , reversed{reverse_x, reverse_y} {}
    // 割り込み処理
    virtual void interrupt() {
      // 初期化, スティックポジションをフィールドにセット
      setPos();
    }
    /* 中心からのスティックの値を返す (0~511-threshold/2)
     * Error: Return medium */
    virtual int getValue(Direction direc) {
      if (direc == X || direc == Y) {
        return map(
          abs(pos[direc] - medium) - threshold/2,
          0, 512 - threshold/2, 0, 512);
      } else {
        return medium;
      }
    }
    // 位置を文字列として返す
    virtual String posToStr(bool enableDebug = false) {
      String str;
      Position posi = getPos();
      if (enableDebug) {
        str += String(posi, BIN) + ": ";
      }
      if (bitRead(posi, Medium)) str += "Medium";
      if (bitRead(posi, Top)) str += "Top";
      if (bitRead(posi, Bottom)) str += "Bottom";
      if (bitRead(posi, Left)) str += "Left";
      if (bitRead(posi, Right)) str += "Right";
      DEBUG_LOG(toString()+": "+str + '.');
      return str + '.';
    }
    virtual String toString() { return "AnalogStick"; }
};
}
