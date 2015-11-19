/*****************************************************************
ファイル名	: server_command.c
機能		: サーバーのコマンド処理
*****************************************************************/

#include"server_common.h"
#include"server_func.h"

extern unsigned char clientsRPS[MAX_CLIENTS]; //クライアントそれぞれの手を記憶する

int count = 0; //届いたクライアントの数をカウントして判定する

static void SetIntData2DataBlock(void *data,int intData,int *dataSize);
static void SetCharData2DataBlock(void *data,char charData,int *dataSize);
static int GetRandomInt(int n);
int gClientNum;
dataSendtoClient dataStruct;
void AjustButton(int pos,char command);
void Wii_Button(int pos);
/*****************************************************************
関数名	: ExecuteCommand
機能	: クライアントから送られてきたコマンドを元に，
		  引き数を受信し，実行する
引数	: char	command		: コマンド
		  int	pos			: コマンドを送ったクライアント番号
出力	: プログラム終了コマンドが送られてきた時には0を返す．
		  それ以外は1を返す
*****************************************************************/
int ExecuteCommand(char command,int pos)
{
    unsigned char	data[MAX_DATA];
    int			dataSize,intData;
    int			endFlag = 1;

    /* 引き数チェック */
    assert(0<=pos && pos<MAX_CLIENTS);
/*
#ifndef NDEBUG
    printf("#####\n");
    printf("ExecuteCommand()2\n");
    printf("Get command %c\n",command);
#endif
*/
    switch(command){
	    case END_COMMAND:
			dataSize = 0;
			/* コマンドのセット */
			SetCharData2DataBlock(data,command,&dataSize);

			/* 全ユーザーに送る */
			SendData(ALL_CLIENTS,data,dataSize);
			endFlag = 0;
			break;
	    
	case UP_KEYBOARD:
	case DOWN_KEYBOARD:
	case LEFT_KEYBOARD:
	case RIGHT_KEYBOARD:
		AjustButton(pos,command);
		break;
	case WII_COMMAND:
		Wii_Button(pos);
		break;
    	default:
			/* 未知のコマンドが送られてきた */
			fprintf(stderr,"0x%02x is not command!\n",command);
    }
    return endFlag;
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

    /* int 型のデータを送信用データの最後にコピーする */
    *(char *)(data + (*dataSize)) = charData;
    /* データサイズを増やす */
    (*dataSize) += sizeof(char);
}

/********************************************************************
関数名 : SetStructData2DataBlock
機能   : クライアントに送信するための構造体を送信用データの最後にコピーする
引数   : void *data :送信用データ
         dataSendtoClient structData
         int *dataSize
*********************************************************************/

static void SetStructData2DataBlock(void *data,dataSendtoClient structData,int *dataSize)
{
	unsigned int tmp;

	assert(data!=NULL);
	assert(0<=(*dataSize));
	/*
	tmp = htonl(structData);

	memcpy(data + (*dataSize),&tmp,sizeof(dataSendtoClient));
	(*dataSize) += sizeof(dataSendtoClient);
	*/

	memcpy(data + (*dataSize),&structData,sizeof(dataSendtoClient));
	(*dataSize) += sizeof(dataSendtoClient);



	//printf("--size = %d--\n",dataSize);
}



/*****************************************************************
関数名	: GetRandomInt
機能	: 整数の乱数を得る
引数	: int		n	: 乱数の最大値
出力	: 乱数値
*****************************************************************/
static int GetRandomInt(int n)
{
    return rand()%n;
}

///////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************
関数名   :AjustButton
機能     :サーバーに送られてきたキーボードの状態から対応したボタンを動かす
引数     :int pos   :送信してきたクライアントの番号
          char command   :どのキーを押したか
戻り値   : なし
 ****************************************************************/
void AjustButton(int pos,char command)
{
	int x=0,y=0;
	//printf("pos = %d\n",pos);
	switch (command){
		case UP_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.y-=1;
			}else{
				dataStruct.chara2.y-=1;
			}
			break;
		case DOWN_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.y+=1;
			}else{
				dataStruct.chara2.y+=1;
			}
			break;
		case LEFT_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.x-=1;
			}else{
				dataStruct.chara2.x-=1;
			}
			break;
		case RIGHT_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.x+=1;
			}else{
				dataStruct.chara2.x+=1;
			}
			break;
	}

	unsigned char data[MAX_DATA];
	int           dataSize;
/*
#ifndef NDEBUG
    printf("#####\n");
    printf("AjustButton\n");
#endif
*/
    dataSize = 0;
    
    // コマンドのセット /
    //SetCharData2DataBlock(data,BUTTON_COMMAND,&dataSize);
    //dataStruct.command = BUTTON_COMMAND;
    /*　クライアントの番号に応じて動かすボタンを指定する/
    SetIntData2DataBlock(data,pos,&dataSize);
    // ボタンの x 座標 /
    SetIntData2DataBlock(data,x,&dataSize);
    // ボタンの y 座標 /
    SetIntData2DataBlock(data,y,&dataSize);
                                           */
    //構造体をデータに格納する
    //SetStructData2DataBlock(data,dataStruct,&dataSize);

/*確認用
    printf("dataSize = %d\n",dataSize);
    printf("chara1 x=%d,y=%d\n",dataStruct.chara1.x,dataStruct.chara1.y);
    printf("chara2 x=%d,y=%d\n",dataStruct.chara2.x,dataStruct.chara2.y);
/*/   
    /* クライアントに送る */
    //SendData(ALL_CLIENTS,data,dataSize);	
}

///////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************
関数名   :Wii_Button
機能     :サーバーに送られてきたwiiリモコン構造体の状態から対応したボタンを動かす
引数     :int pos   :送信してきたクライアントの番号
戻り値   : なし
 ****************************************************************/
void Wii_Button(int pos)
{
	int x=0,y=0;
	//printf("pos = %d\n",pos);
	if(dataServer.wiimote.keys.up==1){ //押された時
		if (pos==0){
			dataStruct.chara1.x-=1;
		}else{
			dataStruct.chara2.x-=1;
		}		
        }
        //右に移動(十字キーの下ボタン）
        if(dataServer.wiimote.keys.down==1){
		if (pos==0){
			dataStruct.chara1.x+=1;
		}else{
			dataStruct.chara2.x+=1;
		}

        }
        //上に移動(十字キーの右ボタン）
        if(dataServer.wiimote.keys.right==1){
		if (pos==0){
			dataStruct.chara1.y-=1;
		}else{
			dataStruct.chara2.y-=1;
		}
        }
        //下に移動(十字キーの左ボタン）
        if(dataServer.wiimote.keys.left==1){
		if (pos==0){
			dataStruct.chara1.y+=1;
		}else{
			dataStruct.chara2.y+=1;
		}
        }

}
/*****************************************************************
関数名   : SendCurrentState
機能     : 現在の状態をクライアントに送信する
引数     : なし
戻り値   : なし
 ****************************************************************/

void SendCurrentState(void)
{
	unsigned char data[MAX_DATA];
	int           dataSize;
/*	
#ifndef NDEBUG
    printf("#####\n");
    printf("SendCurrentState\n");
#endif
*/
	dataSize = 0;//きちんとデータサイズの初期化をしておかないとデータが不完全なものになる
	
	
	//送信するときのコマンド設定
	dataStruct.command = BUTTON_COMMAND;
	printf("command = %c\n",dataStruct.command);
	//データ構造体をセット
	SetStructData2DataBlock(data,dataStruct,&dataSize);
    	
	SendData(ALL_CLIENTS,data,dataSize);

}






