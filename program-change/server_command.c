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

void SaveRPS(char command,int pos,int num);
int JudgeRPS(char command1,char command2);
void AjustButton(int pos,char command);
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

#ifndef NDEBUG
    printf("#####\n");
    printf("ExecuteCommand()2\n");
    printf("Get command %c\n",command);
#endif
    switch(command){
	    case END_COMMAND:
			dataSize = 0;
			/* コマンドのセット */
			SetCharData2DataBlock(data,command,&dataSize);

			/* 全ユーザーに送る */
			SendData(ALL_CLIENTS,data,dataSize);

			endFlag = 0;
			break;
	    /*case CIRCLE_COMMAND:
			/* 円を表示するクライアント番号を受信する */
		//	RecvIntData(pos,&intData);

		//	dataSize = 0;
			/* コマンドのセット */
		//	SetCharData2DataBlock(data,command,&dataSize);
			/* 左上の x 座標のセット */
		//	SetIntData2DataBlock(data,GetRandomInt(500),&dataSize);
			/* 左上の y 座標のセット */
		//	SetIntData2DataBlock(data,GetRandomInt(300),&dataSize);
			/* 直径のセット */
		//	SetIntData2DataBlock(data,GetRandomInt(100),&dataSize);

			/* 指定されたクライアントに送る */
		//	SendData(intData,data,dataSize);
		//	break;

         /*case RECT_COMMAND:
			dataSize = 0;
			/* コマンドのセット */
			//SetCharData2DataBlock(data,command,&dataSize);
			/* 四角の左上の x 座標 */
			//SetIntData2DataBlock(data,GetRandomInt(500),&dataSize);
			/* 四角の左上の y 座標 */
			//SetIntData2DataBlock(data,GetRandomInt(300),&dataSize);
			/* 四角の横幅 */
			//SetIntData2DataBlock(data,GetRandomInt(100),&dataSize);
			/* 四角の高さ */
			//SetIntData2DataBlock(data,GetRandomInt(100),&dataSize);
                        
			/* 全ユーザーに送る */
			//SendData(ALL_CLIENTS,data,dataSize);
			//break;*/
///////////////////////////////////////////////////////////////////////////////////////
/*変更点　ケース文の分岐を増やし、判定する関数にデータを送る*/
    	/*case ROCK_COMMAND:
    	case PAPER_COMMAND:
    	case SCISSORS_COMMAND:
        	SaveRPS(command,pos,gClientNum);
        	break;
	*/
	case UP_KEYBOARD:
	case DOWN_KEYBOARD:
	case LEFT_KEYBOARD:
	case RIGHT_KEYBOARD:
		AjustButton(pos,command);
		break;
    	default:
			/* 未知のコマンドが送られてきた */
			fprintf(stderr,"0x%02x is not command!\n",command);
    }
    return endFlag;
}

/*****************************************************************
関数名	: SendDiamondCommand
機能	: クライアントに菱形を表示させるためにデータを送る
引数	: なし
出力	: なし
*****************************************************************/
void SendDiamondCommand(void)
{
    unsigned char data[MAX_DATA];
    int           dataSize;

#ifndef NDEBUG
    printf("#####\n");
    printf("SendDiamondCommand\n");
#endif
    dataSize = 0;
    /* コマンドのセット */
    //SetCharData2DataBlock(data,DIAMOND_COMMAND,&dataSize);
    /* 菱形の左上の x 座標 */
    SetIntData2DataBlock(data,GetRandomInt(500),&dataSize);
    /* 菱形の左上の y 座標 */
    SetIntData2DataBlock(data,GetRandomInt(300),&dataSize);
    /* 菱形の高さ */
    SetIntData2DataBlock(data,GetRandomInt(100),&dataSize);

    /* クライアントに送る */
    SendData(ALL_CLIENTS,data,dataSize);
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
/*追加点　新しい関数を作る*/
/*****************************************************************
関数名   :SaveRPS
機能     :手を覚えておいて、クライアントの数だけ手が揃えばじゃんけんの判定、結果を送信する
引数     :char command  :コマンド
          int pos       :送ったクライアントのID
          int num       :接続しているクライアント数
出力     :なし
*****************************************************************/
/*void SaveRPS(char command,int pos,int num){
    /*じゃんけんの結果　勝ったクライアントのIDを示している　あいこは-1*/
/*    int result = -1;
    int tempresult = 0;
    int dataSize = 0;
    unsigned char data[MAX_DATA];

    int rpsList[3] = {0,0,0};
    clientsRPS[pos] = command;
    int i = 0;
    /*すべてのクライアントから手が送信されているか確かめる*/
/*    for (i = 0; i < num;i++){
        if (clientsRPS[i]==NOTHING_COMMAND){ //NOTHING_COMMANDはまだ手を送信していないことを示している
            break;
        }
    }
    if (i == num){//すべてのクライアントから手が送信されていれば
       /* for (i = 0;i<num-1;i++){
            if (i > 0){
                tempresult = JudgeRPS(clientsRPS[result],clientsRPS[i+1]);
		if (tempresult == 2){
			result = -1;
		}
       *///     }else

/*	if (num == 2){//クライアントの数が2台の時
                result = JudgeRPS(clientsRPS[0],clientsRPS[1]);
        	dataSize = 0;
		fprintf(stderr,"result = %d\n",result);
	
        	switch (result){
        	case -1:
            		command = TIE_COMMAND;
            		/* コマンドのセット 
            		SetCharData2DataBlock(data,command,&dataSize);
            		/* 全ユーザーに送る 
            		SendData(ALL_CLIENTS,data,dataSize);
            		break;
        	default:
	    		result = result - 1; //IDに合わせる
            		SetCharData2DataBlock(data,WIN_COMMAND,&dataSize);
            		SendData(result,data,dataSize);
            		for (i = 0;i<num;i++){
            		    if (i != result){
            		        SetCharData2DataBlock(data,LOSE_COMMAND,&dataSize);
            		        SendData(i,data,dataSize);
            		    }
            		}
        	}
	}else {
		fprintf(stderr,"num of clients is over 3!\n");
		dataSize = 0;
		//単純に3手に分ける　あいこの判定がしやすくなる
		for (i = 0;i<num;i++){
			if (clientsRPS[i] == ROCK_COMMAND)
				rpsList[0] = 1;
			else if (clientsRPS[i] == PAPER_COMMAND)
				rpsList[1] = 1;
			else
				rpsList[2] = 1;
		}
		//あいこの可能性を調べる
		//すべて一手ずつ出ていたらあいこ または一手しか出ていなかったらあいこ
		if ( (rpsList[0]==1 && rpsList[1]==1 && rpsList[2]==1) || (rpsList[0]==0 && rpsList[1]==0 ) || (rpsList[1]==0 && rpsList[2]==0) || (rpsList[0]==0 && rpsList[2]==0) ){
			result = -1;
		}else if ( rpsList[0] == 0 ){
			result = 1;
		}else if ( rpsList[1] == 0 ){
			result = 2;
		}else if ( rpsList[2] == 0 ){
			result = 3;
		}
		switch(result){
		case -1:
			command = TIE_COMMAND;
			SetCharData2DataBlock(data,command,&dataSize);
			SendData(ALL_CLIENTS,data,dataSize);
			break;
		case 1:
			for (i = 0;i<num;i++){
				if (clientsRPS[i]==PAPER_COMMAND){
					SetCharData2DataBlock(data,LOSE_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}else{
					SetCharData2DataBlock(data,WIN_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}
			}
			break;	
		case 2:
			for (i = 0;i<num;i++){
				if (clientsRPS[i]==SCISSORS_COMMAND){
					SetCharData2DataBlock(data,LOSE_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}else{
					SetCharData2DataBlock(data,WIN_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}
			}			
			break;	
		case 3:
			for (i = 0;i<num;i++){
				if (clientsRPS[i]==ROCK_COMMAND){
					SetCharData2DataBlock(data,LOSE_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}else{
					SetCharData2DataBlock(data,WIN_COMMAND,&dataSize);
					SendData(i,data,dataSize);
				}
			}			
			break;
		}
	}
	for (i = 0;i<MAX_CLIENTS;i++){
		clientsRPS[i] = NOTHING_COMMAND;
	}
	for (i = 0;i<3;i++){
		rpsList[i] = 0;
	}
    }
}
////////////////////////////////////////////////////////////////////////////////////////////
/*****************************************************************
関数名   :JudgeRPS
機能     :じゃんけんの判定をして結果を返す
引数     :char command1   :判定させたい手
          char command2   :判定させたい手２
戻り値   :int    :じゃんけんの結果　　-1:あいこ　 1:先頭が勝利　 2:後方が勝利 
 ****************************************************************/
/* int JudgeRPS(char command1,char command2){
    switch(command1){
    case ROCK_COMMAND:
        if (command2 == PAPER_COMMAND){
            return 2;
        }else if (command2 == SCISSORS_COMMAND){
            return 1;
        }
        else {
            return -1;
        }
        break;
    case PAPER_COMMAND:
        if (command2 == PAPER_COMMAND){
            return -1;
        }else if (command2 == SCISSORS_COMMAND){
            return 2;
        }else{
            return 1;
        }
        break;
    case SCISSORS_COMMAND:
        if (command2 == PAPER_COMMAND){
            return 1;
        }else if (command2 == SCISSORS_COMMAND){
            return -1;
        }else {
            return 2;
        }
        break;
    }
}
*/
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
	printf("pos = %d\n",pos);
	switch (command){
		case UP_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.y-=30;
			}else{
				dataStruct.chara2.y-=30;
			}
			break;
		case DOWN_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.y+=30;
			}else{
				dataStruct.chara2.y+=30;
			}
			break;
		case LEFT_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.x-=30;
			}else{
				dataStruct.chara2.x-=30;
			}
			break;
		case RIGHT_KEYBOARD:
			if (pos==0){
				dataStruct.chara1.x+=30;
			}else{
				dataStruct.chara2.x+=30;
			}
			break;
	}

	unsigned char data[MAX_DATA];
	int           dataSize;

#ifndef NDEBUG
    printf("#####\n");
    printf("SendDiamondCommand\n");
#endif
    dataSize = 0;
    
    // コマンドのセット /
    //SetCharData2DataBlock(data,BUTTON_COMMAND,&dataSize);
    dataStruct.command = BUTTON_COMMAND;
    /*　クライアントの番号に応じて動かすボタンを指定する/
    SetIntData2DataBlock(data,pos,&dataSize);
    // ボタンの x 座標 /
    SetIntData2DataBlock(data,x,&dataSize);
    // ボタンの y 座標 /
    SetIntData2DataBlock(data,y,&dataSize);
                                           */
    //構造体をデータに格納する
    SetStructData2DataBlock(data,dataStruct,&dataSize);

//*確認用
    printf("dataSize = %d\n",dataSize);
    printf("chara1 x=%d,y=%d\n",dataStruct.chara1.x,dataStruct.chara1.y);
    printf("chara2 x=%d,y=%d\n",dataStruct.chara2.x,dataStruct.chara2.y);
/*/   
    /* クライアントに送る */
    SendData(ALL_CLIENTS,data,dataSize);
	
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
	printf("send current data!\n");
	dataStruct.command = BUTTON_COMMAND;
	SetStructData2DataBlock(data,dataStruct,&dataSize);
    	SendData(ALL_CLIENTS,data,dataSize);

}
