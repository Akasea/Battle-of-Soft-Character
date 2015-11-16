/*****************************************************************
ファイル名	: common.h
機能		: サーバーとクライアントで使用する定数の宣言を行う
*****************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<assert.h>
#include<math.h>

#define PORT			(u_short)8888	/* ポート番号 */

#define MAX_CLIENTS		4				/* クライアント数の最大値 */
#define MAX_NAME_SIZE	10 				/* ユーザー名の最大値*/

#define MAX_DATA		200				/* 送受信するデータの最大値 */

#define END_COMMAND		'E'		  		/* プログラム終了コマンド */
#define NOTHING_COMMAND 'N'                             /* クライアントからのデータが来ていない状態*/
//キーボードの状態
#define UP_KEYBOARD 'U'
#define DOWN_KEYBOARD 'D'
#define LEFT_KEYBOARD 'L'
#define RIGHT_KEYBOARD 'R'
//描画命令
#define BUTTON_COMMAND 'B'
//キャラクターの構造体
typedef struct{ 
  int x;//x座標
  int y;//y座標
  int w;//幅
  int h;//高さ
  int vx;//x軸の速さ
  int vy;//y軸の速さ
  int dir;//アニメーション利用時のキャラの現在使っている素材
  int stts;//キャラの状態
  int client_id;//クライアントのID
}character;
//サーバーからクライアントへ送るキャラクターデータを格納した構造体
typedef struct{
 char command;//クライアントに送る命令データ　一文字で構成される
 character chara1;//クライアント１のキャラデータ
 character chara2;//クライアント２のキャラデータ
}dataSendtoClient;
/*
typedef struct{
  

}dataSendtoServer;
*/
#endif
