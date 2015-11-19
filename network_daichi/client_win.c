/*****************************************************************
  ファイル名	: client_win.c
  機能		: クライアントのユーザーインターフェース処理
 *****************************************************************/

#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include<SDL/SDL_gfxPrimitives.h>
#include"common.h"
#include"client_func.h"

static SDL_Surface *gMainWindow;
static SDL_Rect gButtonRect[MAX_CLIENTS+2];

static int CheckButtonNO(int x,int y,int num);
extern int buttonlock;

dataSendtoServer data;


/*****************************************************************
  関数名	: InitWindows
  機能	: メインウインドウの表示，設定を行う
  引数	: int	clientID		: クライアント番号
  int	num				: 全クライアント数
  出力	: 正常に設定できたとき0，失敗したとき-1
 *****************************************************************/
int InitWindows(int clientID,int num,char name[][MAX_NAME_SIZE])
{
    int i;
    //SDL_Surface *image;
    //////////////////////////////////////////////////////////////////////////////////////
    /*変更点　画像のファイル名を変更してグー、チョキ、パーが表示できるようにした*/
    char clientButton[4][6]={"0.jpg","1.jpg","2.jpg"};
    char endButton[]="END.jpg";
    char allButton[]="ALL.jpg";


    char *s,title[10];

    /* 引き数チェック */
    assert(0<num && num<=MAX_CLIENTS);
    SDL_EnableKeyRepeat(0,1);
    /* SDLの初期化 */
    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("failed to initialize SDL.\n");
        return -1;
    }

    /* メインのウインドウを作成する */
    if((gMainWindow = SDL_SetVideoMode(600,400, 32, SDL_SWSURFACE)) == NULL) {
        printf("failed to initialize videomode.\n");
        return -1;
    }
    SDL_FillRect(gMainWindow, NULL, 0x000000ff); //to blue
    stringColor(gMainWindow, 0, 0, "Press buttons 1 and 2 on the wiimote now to connect.\n", 0xffffffff);

    SDL_Flip(gMainWindow);
    /* ウインドウのタイトルをセット */
    sprintf(title,"Battle of Soft Character %d",clientID);
    SDL_WM_SetCaption(title,NULL);

    // ***** Wiiリモコン処理 *****
    wiimote_t wiimote = WIIMOTE_INIT;
    data.wiimote=wiimote;
    wiimote_report_t report = WIIMOTE_REPORT_INIT;

    // Wiiリモコンの接続（１つのみ）
    if(strcmp(wiiName,"key") !=0){
        if (wiimote_connect(&data.wiimote, wiiName) < 0) {   // コマンド引数に指定したWiiリモコン識別情報を渡して接続
            printf("unable to open wiimote: %s\n", wiimote_get_error());
            exit(1);
        }
    }
    //Wiiリモコンのレポートタイプを指定する
    if (wiimote_report(&data.wiimote, &report, sizeof(report.status)) < 0) {
        wiimote_disconnect(&data.wiimote);
    }
    data.wiimote.led.one  = 1;   
    data.wiimote.mode.acc = 1;//加速度センサをオンにする
    /* 背景を白にする */
    SDL_FillRect(gMainWindow,NULL,0xffffff);

    /* ボタンの作成 */
    ///////////////////////////////////////////////////////////////////////////////////
    /*変更点 クライアントの数だけボタンが作成されるが、ここで3つしかボタンをつくらないことにする。
      （選択用のボタン３つと終了用のボタン１つ）
     */
    //   for(i=0;i<4;i++){
    /* if (i < 3){
       /gButtonRect[i].x=20+150*i;
       gButtonRect[i].y=10;
       gButtonRect[i].w=135;
       gButtonRect[i].h=135;/
       gButtonRect[i].x=20+150*i;
       gButtonRect[i].y=10;
       gButtonRect[i].w=135;
       gButtonRect[i].h=135;
       }else{
       gButtonRect[i].x=400;
       gButtonRect[i].y=260;
       gButtonRect[i].w=70;
       gButtonRect[i].h=20;
       }*/
    /*if(i==3){
      s=endButton;
      }else{
      s=clientButton[i];
      }

      s = endButton;
      image = IMG_Load(s);
      SDL_BlitSurface(image,NULL,gMainWindow,&(gButtonRect[i]));
      SDL_FreeSurface(image);
     */
    // }
    SDL_Flip(gMainWindow);

    return 0;
}

/*****************************************************************
  関数名	: DestroyWindow
  機能	: SDLを終了する
  引数	: なし
  出力	: なし
 *****************************************************************/
void DestroyWindow(void)
{
    SDL_Quit();
}

/*****************************************************************
  関数名	: WindowEvent
  機能	: メインウインドウに対するイベント処理を行う
  引数	: int		num		: 全クライアント数
  出力	: なし
 *****************************************************************/
void WindowEvent(int num)
{
    if(wiimote_is_open(&data.wiimote)){ //wiiリモコンの入力の場合
        //wiiリモコンの状態を取得・更新する 
        if(wiimote_update(&data.wiimote) < 0){
            wiimote_disconnect(&data.wiimote);
            return;
        }

        //-------wiiのキーごとに処理--------------------------------
        //HOMEボタンが押された時
        if(data.wiimote.keys.home){
            wiimote_speaker_free(&data.wiimote);
            wiimote_disconnect(&data.wiimote);
            SendEndCommand(data);
        }else{
		data.command = WII_COMMAND;
		SendWiimoteCommand(data);
	}
	/*
        //左に移動(十字キーの上ボタン)
        if(data.wiimote.keys.up==1){ //押された時
            printf("UP!\n");
            SendKeyCommand(LEFT_KEYBOARD);
        }
        //右に移動(十字キーの下ボタン）
        if(data.wiimote.keys.down==1){
            printf("DOWN!\n");
            SendKeyCommand(RIGHT_KEYBOARD);
        }
        //上に移動(十字キーの右ボタン）
        if(data.wiimote.keys.right==1){
            printf("LEFT!\n");
            SendKeyCommand(UP_KEYBOARD);
        }
        //下に移動(十字キーの左ボタン）
        if(data.wiimote.keys.left==1){
            printf("RIGHT!\n");
            SendKeyCommand(DOWN_KEYBOARD);
        }
	*/

        //else { //十字キーをどれも押してない時
        //  jhat_stts=0; //(0:押してない,1:左,2:右)
        // }
    }
    else{ //キーボード入力の場合
        SDL_Event event;
        SDL_MouseButtonEvent *mouse;
        int buttonNO;

        /* 引き数チェック */
        assert(0<num && num<=MAX_CLIENTS);
        //キーボードのイベントチェック
        if(SDL_PollEvent(&event)){
            //printf("Event!\n");
            switch(event.type){
                case SDL_QUIT:
                    SendEndCommand(data);
                    break;
                case SDL_KEYDOWN:
                    printf("The pressed key is %s.\n",SDL_GetKeyName(event.key.keysym.sym));//どのキーが押されたか表示する
                    switch(event.key.keysym.sym){//方向キーの時データを送る　またはエスケープキーの時終わらせる
                        case SDLK_ESCAPE:
                            SendEndCommand(data);
                            break;
                        case SDLK_UP:
                            printf("UP!\n");
                            SendKeyCommand(UP_KEYBOARD);
                            break;
                        case SDLK_DOWN:
                            printf("DOWN!\n");
                            SendKeyCommand(DOWN_KEYBOARD);
                            break;
                        case SDLK_LEFT:
                            printf("LEFT!\n");
                            SendKeyCommand(LEFT_KEYBOARD);
                            break;
                        case SDLK_RIGHT:
                            printf("RIGHT!\n");
                            SendKeyCommand(RIGHT_KEYBOARD);
                            break;
                    }
                    break;		
            }
        }
    }

}

/*****************************************************************
  関数名	: DrawRectangle
  機能	: メインウインドウに四角を表示する
  引数	: int		x			: 四角の左上の x 座標
  int		y			: 四角の左上の y 座標
  int		width		: 四角の横幅
  int		height		: 四角の高さ
  出力	: なし
 *****************************************************************/
void DrawRectangle(int x,int y,int width,int height)
{
#ifndef NDEBUG
    printf("#####\n");
    printf("DrawRectangle()\n");
    printf("x=%d,y=%d,width=%d,height=%d\n",x,y,width,height);
#endif

    rectangleColor(gMainWindow,x,y,x+width,y+height,0x000000ff);
    SDL_Flip(gMainWindow);
}


/*****************************************************************
  関数名	: WhiteoutWindow
  機能	: ウィンドウを新しくする
  引数	: なし
  出力	: なし
 *****************************************************************/
void WhiteoutWindow(void){
    SDL_FillRect(gMainWindow,NULL,0xffffff);
    SDL_Flip(gMainWindow);
}


