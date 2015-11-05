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
//#define CIRCLE_COMMAND	'C'				/* 円表示コマンド */
//#define RECT_COMMAND	'R'				/* 四角表示コマンド */
//#define DIAMOND_COMMAND	'D'				/* 菱形表示コマンド */
//#define WIN_COMMAND     'W'                             /* 勝ち表示コマンド */
//#define LOSE_COMMAND    'L'                             /* 負け表示コマンド */
//#define TIE_COMMAND     'T'                             /* 引き分け表示コマンド */
//#define ROCK_COMMAND    'R'                             /* グー選択コマンド */
//#define PAPER_COMMAND   'P'                             /* パー選択コマンド */
//#define SCISSORS_COMMAND 'S'                            /* チョキ選択コマンド */

#define NOTHING_COMMAND 'N'                             /* クライアントからのデータが来ていない状態*/
//キーボードの状態
#define UP_KEYBOARD 'U'
#define DOWN_KEYBOARD 'D'
#define LEFT_KEYBOARD 'L'
#define RIGHT_KEYBOARD 'R'
#define BUTTON_COMMAND 'B'

#endif
