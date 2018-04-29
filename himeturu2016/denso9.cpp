#include "denso9.h"

#include <Servo.h>
#include "Stick.h"
#include "Wing.h"
#include "ControlSystem.h"
#include "WingServo.h"
#include "debug.h"

//3500-11500(270℃)：中央値7500
//腕木バージョン
//#define EC 7180 //エレボン中央位置
//#define ES 650  //エレボン可動範囲
//#define SC 7250 //スポイラー初期位置
//#define SM 10100//スポイラー可動最大値

//ギアバージョン（エレボン30:150,スポイラー90:270）
//
#define EC 7500 //エレボン中央位置
#define ES 2222  //エレボン可動範囲(片方向)
#define SC 3500 //スポイラー初期位置
#define SM 11500//スポイラー可動最大値

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
static Wing::WingServoUnit *sv_el_left_d;
static Wing::WingServoUnit *sv_el_left_e;
static Wing::WingServoUnit *sv_el_right_d;
static Wing::WingServoUnit *sv_el_right_e;
static Wing::InterfaceServo *sv_el_left;
static Wing::InterfaceServo *sv_el_right;
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
  sv_el_left_d  = new Wing::WingServoUnit(SERVO_ID::ELEVON::LEFT_D, EC, EC+ES, EC-ES);
  sv_el_left_e  = new Wing::WingServoUnit(SERVO_ID::ELEVON::LEFT_E, EC, EC+ES, EC-ES);
  sv_el_left_e  = new Wing::WingServoUnit(SERVO_ID::ELEVON::LEFT_E, EC, EC+ES, EC-ES);
  sv_el_right_d = new Wing::WingServoUnit(SERVO_ID::ELEVON::RIGHT_D, EC, EC+ES, EC-ES);
  sv_el_right_e = new Wing::WingServoUnit(SERVO_ID::ELEVON::RIGHT_E, EC, EC+ES, EC-ES);
  sv_el_left  = new Wing::WingServoUnit2(sv_el_left_d, sv_el_left_e);
  sv_el_right = new Wing::WingServoUnit2(sv_el_right_d, sv_el_right_e);

  sv_sp_left  = new Wing::WingServoUnit(SERVO_ID::SPOILER::LEFT, SC, SM, SC);
  sv_sp_right = new Wing::WingServoUnit(SERVO_ID::SPOILER::RIGHT, SC, SM, SC);

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
  static unsigned long last = millis();
  if ( last + 10UL < millis() ) {
    last = millis();
    DEBUG_LOG("---------- LOOP ----------");
    // コントローラの割り込み
    controlerSpoiler->interrupt();
    controlerElevon->interrupt();    
  }
}
