/*****************************************************************
ファイル名	: client_command.c
機能		: クライアントのコマンド処理
*****************************************************************/

#include"common.h"
#include"client_func.h"

static void SetIntData2DataBlock(void *data,int intData,int *dataSize);
static void SetCharData2DataBlock(void *data,char charData,int *dataSize);
static void RecvRectangleData(void);
static void RecvButtonData(void);
	int  buttonlock;
dataSendtoClient data;

/*****************************************************************
関数名	: ExecuteCommand
機能	: サーバーから送られてきたコマンドを元に，
		  引き数を受信し，実行する
引数	: char	command		: コマンド
出力	: プログラム終了コマンドがおくられてきた時には0を返す．
		  それ以外は1を返す
*****************************************************************/
int ExecuteCommand(char command)
{
    int	endFlag = 1;
#ifndef NDEBUG
    printf("#####\n");
    printf("ExecuteCommand()\n");
    printf("command = %c\n",command);
#endif
    switch(command){
      case END_COMMAND:
        endFlag = 0;
        break;
      case BUTTON_COMMAND:
	RecvButtonData();
	break;
    }
    return endFlag;
}



/*****************************************************************
関数名	: SendEndCommand
機能	: プログラムの終了を知らせるために，
		  サーバーにデータを送る
引数	: なし
出力	: なし
*****************************************************************/
void SendEndCommand(void)
{
    unsigned char	data[MAX_DATA];
    int			dataSize;

#ifndef NDEBUG
    printf("#####\n");
    printf("SendEndCommand()\n");
#endif
    dataSize = 0;
    /* コマンドのセット */
    SetCharData2DataBlock(data,END_COMMAND,&dataSize);

    /* データの送信 */
    SendData(data,dataSize);
}

/*****
static
*****/
/*****************************************************************
関数名	: SetIntData2DataBlock
機能	: int 型のデータを送信用データの最後にセットする
引数	: void		*data		: 送信用データ
		  int		intData		: セットするデータ
		  int		*dataSize	: 送信用データの現在のサイズ
出力	: なし
*****************************************************************/
static void SetIntData2DataBlock(void *data,int intData,int *dataSize)
{
    int tmp;

    /* 引き数チェック */
    assert(data!=NULL);
    assert(0<=(*dataSize));

    tmp = htonl(intData);

    /* int 型のデータを送信用データの最後にコピーする */
    memcpy(data + (*dataSize),&tmp,sizeof(int));
    /* データサイズを増やす */
    (*dataSize) += sizeof(int);
}

/*****************************************************************
関数名	: SetCharData2DataBlock
機能	: char 型のデータを送信用データの最後にセットする
引数	: void		*data		: 送信用データ
		  int		intData		: セットするデータ
		  int		*dataSize	: 送信用データの現在のサイズ
出力	: なし
*****************************************************************/
static void SetCharData2DataBlock(void *data,char charData,int *dataSize)
{
    /* 引き数チェック */
    assert(data!=NULL);
    assert(0<=(*dataSize));

    /* char 型のデータを送信用データの最後にコピーする */
    *(char *)(data + (*dataSize)) = charData;
    /* データサイズを増やす */
    (*dataSize) += sizeof(char);
}


/*****************************************************************
関数名	: RecvRectangleData
機能	: 四角を表示するためのデータを受信し，表示する
引数	: なし
出力	: なし
*****************************************************************/
static void RecvRectangleData(void)
{
    int	x,y,width,height;

    /* 四角コマンドに対する引き数を受信する */
    RecvIntData(&x);
    RecvIntData(&y);
    RecvIntData(&width);
    RecvIntData(&height);

    /* 四角を表示する */
    DrawRectangle(x,y,width,height);
}


////////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/****************************************************************
関数名   :SendRockCommand
機能     :じゃんけんにおいて自分がパーをだしたというデータを送信する
引数     :なし
出力     :なし
****************************************************************/
void SendRockCommand()
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    
    /* 引き数チェック */
    //assert(0<=pos && pos<MAX_CLIENTS);
    
#ifndef NDEBUG
    printf("#####\n");
    printf("SendRockCommand()\n");
    //printf("Send Rock Command to %d\n",pos);
#endif
    
    dataSize = 0;
    /* コマンドのセット */
    //SetCharData2DataBlock(data,ROCK_COMMAND,&dataSize);
    
    /* データの送信 */
    SendData(data,dataSize);
}
////////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/****************************************************************
関数名   :SendPaperCommand
機能     :じゃんけんにおいて自分がパーをだしたというデータを送信する
引数     :なし
出力     :なし
****************************************************************/
void SendPaperCommand()
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    
    /* 引き数チェック */
    //assert(0<=pos && pos<MAX_CLIENTS);
    
#ifndef NDEBUG
    printf("#####\n");
    printf("SendPaperCommand()\n");
    //printf("Send Paper Command to %d\n",pos);
#endif
    
    dataSize = 0;
    /* コマンドのセット */
    //SetCharData2DataBlock(data,PAPER_COMMAND,&dataSize);
    
    /* データの送信 */
    SendData(data,dataSize);
}
////////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/****************************************************************
関数名   :SendScissorsCommand
機能     :じゃんけんにおいて自分がパーをだしたというデータを送信する
引数     :なし
出力     :なし
****************************************************************/
void SendScissorsCommand()
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    
    /* 引き数チェック */
    //assert(0<=pos && pos<MAX_CLIENTS);
    
#ifndef NDEBUG
    printf("#####\n");
    printf("SendSCISSORSCommand()\n");
    //printf("Send SCISSORS Command to %d\n",pos);
#endif
    
    dataSize = 0;
    /* コマンドのセット */
    //SetCharData2DataBlock(data,SCISSORS_COMMAND,&dataSize);
    
    /* データの送信 */
    SendData(data,dataSize);
}
//////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/*****************************************************************
関数名	: RecvWinData
機能	: プレイヤーが勝ったときに結果を受け取り、表示する
引数	: なし
出力	: なし
*****************************************************************/
static void RecvWinData(void)
{
    int	x,y,width,height;
    //SDL_Surface *image;
		
	
    /* 四角コマンドに対する引き数を受信する */
    RecvIntData(&x);
    RecvIntData(&y);
    RecvIntData(&width);
    RecvIntData(&height);

    /* 四角を表示する */
    DrawRectangle(x,y,width,height);
}

//////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/*****************************************************************
関数名	: RecvLoseData
機能	: プレイヤーが勝ったときに結果を受け取り、表示する
引数	: なし
出力	: なし
*****************************************************************/
static void RecvLoseData(void)
{
    int	x,y,width,height;

    /* 四角コマンドに対する引き数を受信する */
    RecvIntData(&x);
    RecvIntData(&y);
    RecvIntData(&width);
    RecvIntData(&height);

    /* 四角を表示する */
    DrawRectangle(x,y,width,height);
}
//////////////////////////////////////////////////////////////////////////////////////////
/*追加関数*/
/*****************************************************************
関数名	: RecvTieData
機能	: プレイヤーが勝ったときに結果を受け取り、表示する
引数	: なし
出力	: なし
*****************************************************************/
static void RecvTieData(void)
{
    int	x,y,width,height;

    /* 四角コマンドに対する引き数を受信する */
    RecvIntData(&x);
    RecvIntData(&y);
    RecvIntData(&width);
    RecvIntData(&height);

    /* 四角を表示する */
    DrawRectangle(x,y,width,height);
}


//////////////////////////////////////////////////////////////////////////////////////////////

/**********************************************************************/
//追加
/*
関数名  : SendKeyCommand
機能    : キーボードが押されたキーを確認して送信する
引数    : char key 押された方向キー
出力    : なし
//////////////////////////////////////////////////////////////////////*/
void SendKeyCommand(char key)
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    dataSize = 0;
#ifndef NDEBUG
    printf("#####\n");
    printf("SendKeyCommand()\n");
    //printf("Send Paper Command to %d\n",pos);
#endif
    switch(key){
    case UP_KEYBOARD:
        SetCharData2DataBlock(data,UP_KEYBOARD,&dataSize);
        break;
    case DOWN_KEYBOARD:
        SetCharData2DataBlock(data,DOWN_KEYBOARD,&dataSize);
        break;
    case RIGHT_KEYBOARD:
        SetCharData2DataBlock(data,RIGHT_KEYBOARD,&dataSize);
        break;
    case LEFT_KEYBOARD:
        SetCharData2DataBlock(data,LEFT_KEYBOARD,&dataSize);
        break;
    }
    SendData(data,dataSize);
}



/*追加関数*/
/*****************************************************************
関数名	: RecvButtonData
機能	: ボタンの位置を受け取り描画する
引数	: なし
出力	: なし
*****************************************************************/
/*static void RecvButtonData(void)
{
    int	x,y,pos;

    / 四角コマンドに対する引き数を受信する /
    RecvIntData(&pos);
    RecvIntData(&x);
    RecvIntData(&y);
    
    / 四角を表示する /
    DrawRectangle(x,y,20,20);
}
*/


static void RecvButtonData(void)
{
	//データ確認表示(受け取った構造体)
	printf("chara1 x = %d,y = %d,w = %d,h = %d,vx = %d,vy = %d,dir = %d,stts = %d,client_id = %d\n",data.chara1.x,data.chara1.y,data.chara1.w,data.chara1.h,data.chara1.vx,data.chara1.vy,data.chara1.dir,data.chara1.stts,data.chara1.client_id);
printf("chara2 x = %d,y = %d,w = %d,h = %d,vx = %d,vy = %d,dir = %d,stts = %d,client_id = %d\n",data.chara2.x,data.chara2.y,data.chara2.w,data.chara2.h,data.chara2.vx,data.chara2.vy,data.chara2.dir,data.chara2.stts,data.chara2.client_id);

	WhiteoutWindow();//前回までの画面をリフレッシュする
        //受け取ったデータから描画
	DrawRectangle(data.chara1.x,data.chara1.y,data.chara1.w,data.chara1.h);
	DrawRectangle(data.chara2.x,data.chara2.y,data.chara2.w,data.chara2.h);

}



