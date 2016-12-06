#include "denso9.h"

#include <Servo.h>
#include "Stick.h"
#include "Wing.h"
#include "ControlSystem.h"
#include "WingServo.h"
#include "debug.h"

#define EC 1436 //エレボン中央位置
#define ES 250  //エレボン可動範囲
#define SC 1450 //スポイラー初期位置
#define SM 2300 //スポイラー可動最大値

// Elevon
#define AST1 A2 //アナログスティック１（右で０）X
#define AST2 A1 //アナログスティック２（下で０）Y
// Spoiler
#define AST3 A3 //アナログスティック３（左で０）X
#define AST4 A4 //アナログスティック４（上で０）Y

// Servo ID
namespace SERVO_ID {
  namespace ELEVON  {
    const unsigned char LEFT_D  = 3;
    const unsigned char LEFT_E  = 2;
    const unsigned char RIGHT_D = 13;
    const unsigned char RIGHT_E = 12;
  }
  namespace SPOILER {
    const unsigned char LEFT  = 1;
    const unsigned char RIGHT = 11;
  }
}

// Controler
static ControlSystem::Controler *controlerSpoiler;
static ControlSystem::Controler *controlerElevon;

// Servo Unit
static Wing::WingServoUnit *sv_el_left;
static Wing::WingServoUnit *sv_el_right;
static Wing::WingServoUnit *sv_sp_left;
static Wing::WingServoUnit *sv_sp_right;

// Servo
static Wing::WingServo *elevon;
static Wing::WingServo *spoiler;

// Stick
static AnalogStick::Stick *stickElevon;
static AnalogStick::Stick *stickSpoiler;

void setup() {
  DEBUG_SETUP();
  // Generate instance.
  // Servo Unit

  //WingServoUnit(servo_id, pos_center, area_max, area_min);
  int pos_center = 0; // test
  int area_max = 0;
  int area_min = 0;
  sv_el_left  = new Wing::WingServoUnit(SERVO_ID::ELEVON::LEFT, pos_center, area_max, area_min);
  sv_el_right = new Wing::WingServoUnit(SERVO_ID::ELEVON::RIGHT, pos_center, area_max, area_min);
  sv_sp_left  = new Wing::WingServoUnit(SERVO_ID::SPOILER::LEFT, pos_center, area_max, area_min);
  sv_sp_right = new Wing::WingServoUnit(SERVO_ID::SPOILER::RIGHT, pos_center, area_max, area_min);

  // Wing Class
  // WingServoUnit で指定した値に依存する
  elevon = new Wing::Elevon(sv_el_left, sv_el_right, EC, ES);
  spoiler = new Wing::Spoiler(sv_sp_left, sv_sp_right, SC, SM);
  // Stick
  stickElevon = new AnalogStick::Stick(AST1, AST2, 200, true, false);
  stickSpoiler = new AnalogStick::Stick(AST3, AST4, 200, false, true);

  // Initialize controlers.
  controlerSpoiler = new ControlSystem::Controler(stickSpoiler, spoiler);
  controlerElevon = new ControlSystem::Controler(stickElevon, elevon);
}

void loop() {
  DEBUG_LOG("---------- LOOP ----------");
  // コントローラの割り込み
  controlerSpoiler->interrupt();
  controlerElevon->interrupt();

  delay(60);
}
