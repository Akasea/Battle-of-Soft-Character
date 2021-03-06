/*****************************************************************
  ファイル名	: client_main.c
  機能		: クライアントのメインルーチン
 *****************************************************************/

#include"common.h"
#include"client_func.h"

int main(int argc,char *argv[])
{
    int		num;
    char	name[MAX_CLIENTS][MAX_NAME_SIZE];
    int		endFlag=1;
    char	localHostName[]="localhost";
    char	*serverName;
    int		clientID;
    /* 引き数チェック */
    if(argc == 1){
        wiiName = "key";
        serverName = localHostName;
    }
    else if(argc == 2){
        wiiName = argv[1];
        serverName = localHostName;
    }
    else if(argc == 3){
        wiiName = argv[1];
        serverName = argv[2];
    }
    else{
        fprintf(stderr, "Usage: %s, Cannot find a Server Name.\n", argv[0]);
        return -1;
    }

    /* サーバーとの接続 */
    if(SetUpClient(serverName,&clientID,&num,name)==-1){
        fprintf(stderr,"setup failed : SetUpClient\n");
        return -1;
    }

    /* ウインドウの初期化 */
    if(InitWindows(clientID,num,name)==-1){
        fprintf(stderr,"setup failed : InitWindows\n");
        return -1;
    }

/*    Uint32 interval = SDL_GetTicks() + 5;
    int time=0;
    Uint32 now;
*/
    /* メインイベントループ */
    while(endFlag){
/*      WindowEvent(num);
        now= SDL_GetTicks(); //現在の時間を取得
        if(now >= interval){
            endFlag = SendRecvManager();
            interval = now + 5; //0.01秒ごとに実行
        }
*/ 
       WindowEvent(num);
       endFlag = SendRecvManager();
    };

    /* 終了処理 */
    DestroyWindow();
    CloseSoc();

    return 0;
}
