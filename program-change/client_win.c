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
	SDL_Surface *image;
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
	/* ウインドウのタイトルをセット */
	sprintf(title,"Battle of Soft Character %d",clientID);
	SDL_WM_SetCaption(title,NULL);
	
	/* 背景を白にする */
	SDL_FillRect(gMainWindow,NULL,0xffffff);

	/* ボタンの作成 */
///////////////////////////////////////////////////////////////////////////////////
        /*変更点 クライアントの数だけボタンが作成されるが、ここで3つしかボタンをつくらないことにする。
          （選択用のボタン３つと終了用のボタン１つ）
        */
	for(i=0;i<4;i++){
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
		if(i==3){
                    s=endButton;
		}else{
                    s=clientButton[i];
		}
		
		s = endButton;
		image = IMG_Load(s);
		SDL_BlitSurface(image,NULL,gMainWindow,&(gButtonRect[i]));
		SDL_FreeSurface(image);
	}
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
	SDL_Event event;
	SDL_MouseButtonEvent *mouse;
	int buttonNO;
	
    /* 引き数チェック */
    assert(0<num && num<=MAX_CLIENTS);

	if(SDL_PollEvent(&event)){
		printf("Event!\n");
		switch(event.type){
			case SDL_QUIT:
				SendEndCommand();
				break;
			/*case SDL_MOUSEBUTTONUP:
				mouse = (SDL_MouseButtonEvent*)&event;
				if(mouse->button == SDL_BUTTON_LEFT){
					buttonNO = CheckButtonNO(mouse->x,mouse->y,num);
#ifndef NDEBUG
					printf("#####\n");
					printf("WindowEvent()\n");
					printf("Button %d is pressed\n",buttonNO);
#endif
//////////////////////////////////////////////////////////////////////////////////////////////
/*変更点　いつでも３つのボタンがおされているかを見なければならないのでnumを変更している*/
					//if(0<=buttonNO && buttonNO<3){
/////////////////////////////////////////////////////////////////////////////////////////////
/*追加点　一回ボタンが押されたら結果が帰ってくるまで変更できない*/
					/*	if (buttonlock!=1){
							buttonlock = 1;
							if (buttonNO == 0){
								SendRockCommand();
							}else if (buttonNO ==1){
								SendScissorsCommand();
							}else
								SendPaperCommand();

						/* 名前の書かれたボタンが押された */
						//SendCircleCommand(buttonNO);
						//	}
						//}
                                        /*
					else if(buttonNO==num){
						// 「All」と書かれたボタンが押された
						SendRectangleCommand();
                                        }
                                        */
////////////////////////////////////////////////////////////////////////////////////////////
/*変更点　終わらせるENDボタンも見なければいけないのでnumから変更している*/
					//else if(buttonNO==3){
					//	/* 「End」と書かれたボタンが押された */
					//	SendEndCommand();
					//}
				//}
				//break;
                case SDL_KEYDOWN:
                    printf("The pressed key is %s.\n",SDL_GetKeyName(event.key.keysym.sym));
                    switch(event.key.keysym.sym){
		    case SDLK_ESCAPE:
			SendEndCommand();
			break;
                    case SDLK_UP:
                        printf("UP!\n");
                        SendKeyCommand(UP_KEYBOARD);//上が押された時に情報を送る
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
関数名	: DrawCircle
機能	: メインウインドウに円を表示する
引数	: int		x		: 円の x 座標
		  int		y		: 円の y 座標
		  int		r		: 円の半径
出力	: なし
*****************************************************************/
void DrawCircle(int x,int y,int r)
{
#ifndef NDEBUG
    printf("#####\n");
    printf("DrawCircle()\n");
    printf("x=%d,y=%d,tyokkei=%d\n",x,y,r);
#endif

    circleColor(gMainWindow,x,y,r,0x000000ff);
	SDL_Flip(gMainWindow);
}

/*****************************************************************
関数名	: DrawDiamond
機能	: メインウインドウに菱形を表示する
引数	: int		x		: 左上の x 座標
		  int		y		: 左上の y 座標
		  int		height		: 高さ
出力	: なし
*****************************************************************/
void DrawDiamond(int x,int y,int height)
{
	Sint16	vx[5],vy[5];
	int	i;

#ifndef NDEBUG
    printf("#####\n");
    printf("DrawDiamond()\n");
    printf("x=%d,y=%d,height=%d\n",x,y,height);
#endif

    for(i=0;i<4;i++){
        vx[i] = x + height*((1-i)%2)/2;
        vy[i] = y + height*((2-i)%2);
    }
    vx[4]=vx[0];
    vy[4]=vy[0];
	
	polygonColor(gMainWindow, vx, vy, 5 , 0x000000ff);
	SDL_Flip(gMainWindow);
}
/////////////////////////////////////////////////////////////////////////////////
/*追加
関数名  :DrawResult
機能    :クライアントが受け取った結果を画面に出力する
引数    :char command   :じゃんけんの結果
*/
//void DrawResult(char command){
  //  SDL_Surface *image;
   // SDL_Rect resultrect;
//////////////////////////////////////////////////////////////////////////////////////
/*追加　新しい配列を作って画像を参照する*/
/*    char winprint[]="win.png";
    char loseprint[]="lose.png";
    char tieprint[]="tie.png";
    char *s;
    
    switch (command){
    case WIN_COMMAND:
        s = winprint;
        break;
    case LOSE_COMMAND:
        s = loseprint;
        break;
    case TIE_COMMAND:
        s = tieprint;
        break;
    }
    image = IMG_Load(s);
    resultrect.x = 150;
    resultrect.y = 175;
    resultrect.w = 150;
    resultrect.h = 100;
    
    SDL_BlitSurface(image,NULL,gMainWindow,&resultrect);
    SDL_FreeSurface(image);
    
    SDL_Flip(gMainWindow);
    
    
}
/*****
static
*****/
/*****************************************************************
関数名	: CheckButtonNO
機能	: クリックされたボタンの番号を返す
引数	: int	   x		: マウスの押された x 座標
		  int	   y		: マウスの押された y 座標
		  char	   num		: 全クライアント数
出力	: 押されたボタンの番号を返す
		  ボタンが押されていない時は-1を返す
*****************************************************************/
static int CheckButtonNO(int x,int y,int num)
{
	int i;

 	for(i=0;i<num+2;i++){
		if(gButtonRect[i].x < x &&
			gButtonRect[i].y < y &&
      		gButtonRect[i].x + gButtonRect[i].w > x &&
			gButtonRect[i].y + gButtonRect[i].h > y){
			return i;
		}
	}
 	return -1;
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


