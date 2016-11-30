#ifndef _INC_ICSSERVO
#define _INC_ICSSERVO

#include "arduino.h"

//コマンド定義
#define SERVO_SERIAL Serial1    //サーボと通信を行うクラス
#define CMD_POS      0x80       //サーボの角度を決めるコマンド
#define CMD_READ     0xA0       //サーボのパラメータを読み出すコマンド
#define CMD_WRITE    0xC0       //サーボのパラメータを書き込むコマンド
#define CMD_ID       0xE0       //サーボのID番号の読み出し＆書き込みコマンド
//コマンドヘッダ生成マクロ
#define GenCmdHead(cmd, id) ((unsigned char)(cmd)|(0x1F&(unsigned char)(id)))
//サブコマンド定義
#define SC_EEPROM    0x00       //サーボモータのROMに直接アクセスする
#define SC_STRC      0x01       //ストレッチデータを扱う
#define SC_SPD       0x02       //スピードデータを書き込む
#define SC_CUR       0x03       //電流地を読み出す，制限電流値を書き込む
#define SC_TMP       0x04       //サーボモータの温度値を読み出す，制限温度値を書き込む

class IcsServo {
private:

    
public:

	/****************** 通信処理 ******************/
	/// <summary>
	/// シリアル通信の開始
	/// </summary>
	void begin();

	/// <summary>
	/// シリアル通信の終了
	/// </summary>
	void end();

	/// <summary>
	/// バイト数を指定してデータを送受信する
	/// </summary>
	/// <param name="senddata">送信するデータの配列</param>
	/// <param name="sendbyte">送信するバイト数</param>
	/// <param name="revdata">受信した内容を格納する配列</param>
	/// <param name="revbyte">受信するバイト数（コールバックを含まず）</param>
	/// <returns>成功：1，失敗：-1</returns>
	int sendCommand(byte *senddata, int sendbyte, byte *revdata, int revbyte);

	/****************** サーボポジション ******************/
	/// <summary>
	/// サーボのポジションを設定，取得する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="pos">ポジション（3500～11500）</param>
	/// <returns>成功：関数実行時のサーボ位置，失敗：-1</returns>
	int position(unsigned char id, unsigned int pos);
	/// <summary>
	/// サーボをフリーにする（現在の角度を取得する）
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="pos">ポジション（3500～11500）</param>
	/// <returns>成功：現在のサーボ位置，失敗：-1</returns>
	int positionFree(unsigned char id);

	/****************** 各種パラメータ ******************/
	/// <summary>
	/// サーボのストレッチを取得する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <returns>成功：現在のサーボストレッチ（1～127），失敗：-1</returns>
	int getStretch(unsigned char id);
	/// <summary>
	/// サーボのストレッチを設定する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="strc">ストレッチ（1～127）</param>
	/// <returns>成功：現在のサーボストレッチ（1～127），失敗：-1</returns>
	int setStretch(unsigned char id, unsigned char strc);
	/// <summary>
	/// サーボのスピードを取得する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <returns>成功：現在のサーボスピード（1～127），失敗：-1</returns>
	int getSpeed(unsigned char id);
	/// <summary>
	/// サーボのスピードを設定する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="spd">スピード（1～127）</param>
	/// <returns>成功：現在のサーボスピード（1～127），失敗：-1</returns>
	int setSpeed(unsigned char id, unsigned char spd);
	/// <summary>
	/// サーボの電流値を取得する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <returns>成功：現在のサーボ温度（正転0～63_逆転64～127），失敗：-1</returns>
	int getCurrent(unsigned char id);
	/// <summary>
	/// サーボの電流制限値を設定する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="cur">電流値限値（1～127）</param>
	/// <returns>成功：現在のサーボ電流値限値（1～63），失敗：-1</returns>
	int setCurrent(unsigned char id, unsigned char cur);
	/// <summary>
	/// サーボの温度を取得する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <returns>成功：現在のサーボ温度（1～127），失敗：-1</returns>
    int getTemperature(unsigned char id);
	/// <summary>
	/// サーボの温度制限値を設定する
	/// </summary>
	/// <param name="id">サーボのID（0～31）</param>
	/// <param name="tmp">温度制限値（1～127）</param>
	/// <returns>成功：現在のサーボ温度制限値（1～127），失敗：-1</returns>
    int setTemperature(unsigned char id, unsigned char tmp);

	/****************** サーボID ******************/
	/// <summary>
	/// サーボのIDを取得する（1台のみで実行すること）
	/// </summary>
	/// <returns>成功：接続されているサーボのID，失敗：-1</returns>
    int getID();
	/// <summary>
	/// サーボのIDを設定する（1台のみで実行すること）
	/// </summary>
	/// <param name="id">新しいサーボのID（0～31）</param>
	/// <returns>成功：接続されているサーボのID，失敗：-1</returns>
    int setID(unsigned char id);

};

#endif
