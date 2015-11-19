/*****************************************************************
ファイル名	: client_command.c
機能		: クライアントのコマンド処理
*****************************************************************/

#include"common.h"
#include"client_func.h"

static void SetIntData2DataBlock(void *data,int intData,int *dataSize);
static void SetCharData2DataBlock(void *data,char charData,int *dataSize);
static void SetStructData2DataBlock(void *data,dataSendtoServer dataS,int *dataSize);
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
void SendEndCommand(dataSendtoServer dataS)
{
    unsigned char	data[MAX_DATA];
    int			dataSize= 0;

#ifndef NDEBUG
    printf("#####\n");
    printf("SendEndCommand()\n");
#endif
    dataS.command = END_COMMAND;
    SetStructData2DataBlock(data,dataS,&dataSize);
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

/********************************************************************
関数名 : SetStructData2DataBlock
機能   : クライアントに送信するための構造体を送信用データの最後にコピーする
引数   : void *data :送信用データ
         wiimote structData
         int *dataSize
*********************************************************************/

static void SetStructData2DataBlock(void *data,dataSendtoServer dataS,int *dataSize)
{
	unsigned int tmp;

	assert(data!=NULL);
	assert(0<=(*dataSize));
	/*
	tmp = htonl(structData);

	memcpy(data + (*dataSize),&tmp,sizeof(dataSendtoClient));
	(*dataSize) += sizeof(dataSendtoClient);
	*/
	
	memcpy(data + (*dataSize),&dataS,sizeof(dataSendtoServer));
	(*dataSize) += sizeof(dataSendtoServer);


	//printf("--size = %d--\n",dataSize);
}


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

/**********************************************************************/
//追加
/*
関数名  : SendWiimoteCommand
機能    : リモコンの情報を送信する(構造体を送信)
引数    : wiimote_t wiimote
出力    : なし
//////////////////////////////////////////////////////////////////////*/
void SendWiimoteCommand(dataSendtoServer dataStruct)
{
    unsigned char	data[MAX_DATA];
    int			dataSize;
    dataSize = 0;
#ifndef NDEBUG
    printf("#####\n");
    printf("SendKeyCommand()\n");
    //printf("Send Paper Command to %d\n",pos);
#endif

    SetStructData2DataBlock(data,dataStruct,&dataSize);

    SendData(data,dataSize);
}



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



