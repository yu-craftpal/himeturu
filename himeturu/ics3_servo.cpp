#include "ics3_servo.h"

/****************** 通信処理 ******************/
///シリアル通信の開始
void IcsServo::begin(){
    SERVO_SERIAL.begin(115200,SERIAL_8E1);
}

///シリアル通信の終了
void IcsServo::end() {
	SERVO_SERIAL.end();
}

///バイト数を指定してデータを送受信する
int IcsServo::sendCommand(byte *senddata, int sendbyte, byte *revdata, int revbyte){
    unsigned long timeout = 10;
    unsigned long time1;
    int s, r;
    int flag = 0;
	//バッファクリア
    while(SERVO_SERIAL.available() > 0) SERVO_SERIAL.read();
    //コマンドの送信（エコーバックを受信する）
	for (s = 0; s < sendbyte; s++){
        time1 = millis();
        SERVO_SERIAL.write(senddata[s]);
        while(1){
            if((millis() - time1) > timeout){
                break;
            }
            if(SERVO_SERIAL.available() > 0){
                SERVO_SERIAL.read();
                break;
            }
        }
        
    }
	//コマンドの受信（10ms以内に返事がない場合はERROR終了）
    for (r = 0; r < revbyte; r++){
        time1 = millis();
        while(1){
            if((millis() - time1) > timeout){
                return -1;
            }
            if(SERVO_SERIAL.available() > 0){
                revdata[r] = SERVO_SERIAL.read();
                break;
            }
        }        
    }
    return 1;
}

/****************** サーボポジション ******************/
///サーボのポジションを設定，取得する
int IcsServo::position(unsigned char id, unsigned int pos) {
	int res = 0;
	byte cmd_h = GenCmdHead(CMD_POS, id);
	byte pos_h = (pos & 0x3F80) >> 7;
	byte pos_l = (pos & 0x007F);
	byte sd[3] = { cmd_h, pos_h, pos_l };
	byte rev[3];
	if (sendCommand(sd, 3, rev, 3) == 1) {
		byte r_cmd, tch_h, tch_l;
		r_cmd = rev[0];
		tch_h = rev[1];
		tch_l = rev[2];
		res = (tch_h << 7) | tch_l;
	}
	else {
		res = -1;
	}
	return res;
}
///サーボをフリーにする（現在の角度を取得する）
int IcsServo::positionFree(unsigned char id) {
    return position(id, 0);
}

/****************** 各種パラメータ ******************/
///サーボのストレッチを取得する
int IcsServo::getStretch(unsigned char id) {
	byte sd[2] = { GenCmdHead(CMD_READ, id), SC_STRC };
	byte rev[3];
	int strc;
	if (sendCommand(sd, 2, rev, 3) == 1) {
		strc = rev[2];
	}
	else {
		strc = -1;
	}
	return strc;
}
///サーボのストレッチを設定する
int IcsServo::setStretch(unsigned char id, unsigned char strc) {
	byte sd[3] = { GenCmdHead(CMD_WRITE, id), SC_STRC, byte(strc) };
	byte rev[3];
	int revint;
	if (sendCommand(sd, 3, rev, 3) == 1) {
		revint = rev[2];
	}
	else {
		revint = -1;
	}
	return revint;
}
///サーボのスピードを取得する
int IcsServo::getSpeed(unsigned char id) {
	byte sd[2] = { GenCmdHead(CMD_READ, id), SC_SPD };
	byte rev[3];
	int spd;
	if (sendCommand(sd, 2, rev, 3) == 1) {
		spd = rev[2];
	}
	else {
		spd = -1;
	}
	return spd;
}
///サーボのスピードを設定する
int IcsServo::setSpeed(unsigned char id, unsigned char spd) {
	byte sd[3] = { GenCmdHead(CMD_WRITE, id), SC_SPD, byte(spd) };
	byte rev[3];
	int revint;
	if (sendCommand(sd, 3, rev, 3) == 1) {
		revint = rev[2];
	}
	else {
		revint = -1;
	}
	return revint;
}
///サーボの電流値を取得する
int IcsServo::getCurrent(unsigned char id) {
	byte sd[2] = { GenCmdHead(CMD_READ, id), SC_CUR };
	byte rev[3];
	int cur;
	if (sendCommand(sd, 2, rev, 3) == 1) {
		cur = rev[2];
	}
	else {
		cur = -1;
	}
	return cur;
}
///サーボの電流制限値を設定する
int IcsServo::setCurrent(unsigned char id, unsigned char cur) {
	byte sd[3] = { GenCmdHead(CMD_WRITE, id), SC_CUR, byte(cur) };
	byte rev[3];
	int revint;
	if (sendCommand(sd, 3, rev, 3) == 1) {
		revint = rev[2];
	}
	else {
		revint = -1;
	}
	return revint;
}

///サーボの温度を取得する
int IcsServo::getTemperature(unsigned char id){
    byte sd[2] = {GenCmdHead(CMD_READ, id), SC_TMP};
    byte rev[3];
    int tmp;
    if (sendCommand(sd, 2, rev, 3) == 1){
        tmp = rev[2];
    }
    else{
        tmp = -1;
    }
    return tmp;
}
///サーボの温度制限値を設定する
int IcsServo::setTemperature(unsigned char id, unsigned char tmp){
    byte sd[3] = {GenCmdHead(CMD_WRITE, id), SC_TMP, byte(tmp)};
    byte rev[3];
    int revtmp;
    if (sendCommand(sd, 3, rev, 3) == 1){
        revtmp = rev[2];
    }
    else{
        revtmp = -1;
    }
    return revtmp;
}

/****************** サーボID ******************/
///サーボのIDを取得する（1台のみで実行すること）
int IcsServo::getID(){
    byte sd[4] = {0xFF, 0x00, 0x00, 0x00};
    byte rev[1];
    int id;
    if (sendCommand(sd, 4, rev, 1) == 1){
        id = rev[0] & 0b00011111;
    }
    else{
        id = -1;
    }
    return id;
}
///サーボのIDを設定する（1台のみで実行すること）
int IcsServo::setID(unsigned char id){
    byte sd[4] = {GenCmdHead(CMD_ID, id), 0x01, 0x01, 0x01};
    byte rev[1];
    int revid;
    if (sendCommand(sd, 4, rev, 1) == 1){
        revid = rev[0] & 0b00011111;
    }
    else{
        revid = -1;
    }
    return revid;
}
