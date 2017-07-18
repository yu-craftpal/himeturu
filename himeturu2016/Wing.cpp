#include "Wing.h"

// 翼関係
namespace Wing {

  /**************************************************
   * Class: Wing::Elevon
   **************************************************/
  /* PRIVATE */
  // 範囲外に数値が飛び出ないようにする
  int Elevon::refactorValue(int value) {
    if (value < pos_down) return pos_down; else if (value > pos_up) return pos_up;
    return value;
  }
  // (スティックの値)抵抗値を角度に変換
  int Elevon::getPosUp(int value, int fromLow, int fromHigh) {
    return refactorValue(map(value, fromLow, fromHigh, pos_center, pos_up));
  }
  int Elevon::getPosDown(int value, int fromLow, int fromHigh) {
    return refactorValue(map(value, fromLow, fromHigh, pos_center, pos_down));
  }

  /* PUBLIC */
  // エレボンを初期値に戻す
  void Elevon::center(enum Side side) {
    moveServo(pos_center, side);
  }
  // エレボンを上げる
  void Elevon::up(enum Side side, int value) {
    moveServo(getPosUp(value), side);
  }
  // エレボンを下げる
  void Elevon::down(enum Side side, int value) {
    moveServo(getPosDown(value), side);
  }
  void Elevon::interrupt(String str, int pos_x, int pos_y) {
    // 翼制御
    // ダミーなので後で書き直す必要あり
    if (str.indexOf("Top.") == 0) {
      down(Both, pos_y);
    } else if (str.indexOf("Bottom.") == 0) {
      up(Both, pos_y);
    } else if (str.indexOf("Left.") == 0) {
      up(Left, pos_x);
      down(Right, pos_x);
    } else if (str.indexOf("Right.") == 0) {
      up(Right, pos_x);
      down(Left, pos_x);
    } else {
      center(Both);
    }
  }
  String Elevon::toString() { return "ElevonServo"; }


  /**************************************************
   * Class: Wing::Spoiler
   **************************************************/
  /* PRIVATE */
  // 範囲外に数値が飛び出ないようにする
  int Spoiler::refactorValue(int value) {
    if (value < 0) return 0; else if (value > pos_max) return pos_max;
    return value;
  }
  // 抵抗値を角度に変換
  int Spoiler::getPosOpen(int value, int fromLow, int fromHigh) {
    return refactorValue(map(value, fromLow, fromHigh, pos_center, pos_max));
  }

  /* PUBLIC */
  // スポイラを初期値に戻す
  void Spoiler::close(enum Side side) {
    moveServo(pos_center, side);
  }
  // スポイラを上げる
  void Spoiler::open(enum Side side, int value) {
    moveServo(getPosOpen(value), side);
  }
  /* 左右のスポイラを比率を考え上げる
   * <引数>
   * side : 比率を指定する翼側
   * raito: 比率 0~1000 */
  void Spoiler::open(enum Side side, int value, int raito) {
    //open(side, value); //?
    if (side == Left) open(Right, value * (1.0 - (float)raito / 1000));
    if (side == Right) open(Left, value * (1.0 - (float)raito / 1000));
  }
  void Spoiler::interrupt(String str, int pos_x, int pos_y) {
    // 翼制御
    if (str.indexOf("Top.") == 0) {
      open(Both, pos_y);
    } else if (str.indexOf("Left.") == 0) {
      open(Left, pos_y, map(pos_x, 0, 512, 0, 1000));
    } else if (str.indexOf("Right.") == 0) {
      open(Right, pos_y, map(pos_x, 0, 512, 0, 1000));
    } else {
      close(Both);
    }
  }
  String Spoiler::toString() { return "SpoilerServo"; }
}
