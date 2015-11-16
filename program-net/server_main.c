/*****************************************************************
ファイル名	: server_main.c
機能		: サーバーのメインルーチン
*****************************************************************/

#include<SDL/SDL.h>
#include<time.h>
#include<sys/time.h>
#include"server_common.h"

static Uint32 SignalHandler(Uint32 interval, void *param);

extern dataSendtoClient dataStruct; //データ送信用の構造体　キャラクター二体分の情報が入っている

int main(int argc,char *argv[])
{
	int	num;
	int	endFlag = 1;

	
	//時間計測用関数
	//unsigned int i = 0;//総フレーム数
	//unsigned int is = 0;//一秒ごとのフレーム数
	
	//構造体の初期化
	dataStruct.chara1.x = 150;
	dataStruct.chara1.y = 250;
	dataStruct.chara1.w = 40;
	dataStruct.chara1.h = 40;
	dataStruct.chara1.vx = 0;
	dataStruct.chara1.vy = 0;
	dataStruct.chara1.dir = 0;
	dataStruct.chara1.stts = 0;
	dataStruct.chara1.client_id = 0;

	dataStruct.chara2.x = 350;
	dataStruct.chara2.y = 250;
	dataStruct.chara2.w = 40;
	dataStruct.chara2.h = 40;
	dataStruct.chara2.vx = 0;
	dataStruct.chara2.vy = 0;
	dataStruct.chara2.dir = 0;
	dataStruct.chara2.stts = 0;
	dataStruct.chara2.client_id = 1;
	/*/

	memset(&dataStruct,0,sizeof(dataSendtoClient));
	/* 引き数チェック */
	if(argc != 2){
		fprintf(stderr,"Usage: number of clients\n");
		exit(-1);
	}
	if((num = atoi(argv[1])) < 0 ||  num > MAX_CLIENTS){
		fprintf(stderr,"clients limit = %d \n",MAX_CLIENTS);
		exit(-1);
	}
	
	/* SDLの初期化 */
	if(SDL_Init(SDL_INIT_TIMER) < 0) {
		printf("failed to initialize SDL.\n");
		exit(-1);
	}

	/* クライアントとの接続 */ 
	if(SetUpServer(num) == -1){
		fprintf(stderr,"Cannot setup server\n");
		exit(-1);
	}
////////////////////////////////////////////////////////////////////////////////
/*変更点　割り込み処理のセットをしない　今回は割り込み処理をしないため*/
	/* 割り込み処理のセット */
	//SDL_AddTimer(5000,SignalHandler,NULL);
	
	//時間計測のため測定

	//struct timeval t1,t2,t3;
	//t1はwhileループが始まった時の時間　t2は1秒ごとの始まりの時間　t3は今の時間
	//int flag = 0;
	//double sec; //秒計算用
	
	/* メインイベントループ */
	while(endFlag){

		//この二つがwhileループメイン
		SendCurrentState();
		endFlag = SendRecvManager();
		
		/* //時間計測してfpsなどを表示する
		if (flag == 0){
			gettimeofday(&t1,NULL);
			gettimeofday(&t2,NULL);
			flag = 1;
		}
		gettimeofday(&t3,NULL);
		sec = ((t3.tv_sec-t2.tv_sec)+(t3.tv_usec-t2.tv_usec)*1.0E-6);
		if (sec > 1){
			gettimeofday(&t2,NULL);
			is = 0;
		}
		i++;
		is++;
		printf("------loop %dlaps------\n",i);//ループ何回目か
		printf("------- %lffps------\n",is/sec); //(end-start)/CLOCKS_PER_SEC));//fps
		printf("------- %lfsec------\n",((t3.tv_sec-t1.tv_sec)+(t3.tv_usec-t1.tv_usec)*1.0E-6));//開始から何秒経過したか
	
		*/
	};

	/* 終了処理 */
	Ending();

	return 0;
}

/*****************************************************************
関数名  : SignalHandler
機能    : 割り込み用関数 
引数    : Uint32	interval	: タイマー
		  void		*param		: 割り込み処理の引数
出力    : タイマーの次の間隔
*****************************************************************/
static Uint32 SignalHandler(Uint32 interval, void *param)
{
/////////////////////////////////////////////////////////////////////////
/*変更点　シグナルハンドラ内のSendDiamondCommandはもう必要ないのでコメントアウトした
 一定時間ごとに菱形を画面に描画する関数だった*/
    //SendDiamondCommand();

	return interval;
}
