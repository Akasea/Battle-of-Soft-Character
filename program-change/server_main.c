/*****************************************************************
ファイル名	: server_main.c
機能		: サーバーのメインルーチン
*****************************************************************/

#include<SDL/SDL.h>
#include"server_common.h"

static Uint32 SignalHandler(Uint32 interval, void *param);

extern dataSendtoClient dataStruct; //データ送信用の構造体　キャラクター二体分の情報が入っている

int main(int argc,char *argv[])
{
	int	num;
	int	endFlag = 1;
        //構造体の初期化
	//
	unsigned int i = 0;
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
	
	/* メインイベントループ */
	while(endFlag){
		SendCurrentState();
		endFlag = SendRecvManager();
		i++;
		printf("------loop %dlaps------\n",i);
		printf("------- %lffps------\n",i)
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
