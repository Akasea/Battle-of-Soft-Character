/*****************************************************************
ファイル名	: client_func.h
機能		: クライアントの外部関数の定義
*****************************************************************/

#ifndef _CLIENT_FUNC_H_
#define _CLIENT_FUNC_H_

#include"common.h"

char *wiiName;//wiiAddress
/* client_main.c*/
extern void GameWindow(void); //横スクロールプレイ画面の処理を行う関数
/* client_net.c */
extern int SetUpClient(char* hostName,int *clientID,int *num,char clientName[][MAX_NAME_SIZE]);
extern void CloseSoc(void);
extern int RecvIntData(int *intData);
extern void SendData(void *data,int dataSize);
extern int SendRecvManager(void);

/* client_win.c */
extern int InitWindows(int clientID,int num,char name[][MAX_NAME_SIZE]);
extern void DestroyWindow(void);
extern void WindowEvent(int num);
extern void DrawRectangle(int x,int y,int width,int height);
extern void SendKeyCommand(char key);


/* client_command.c */
extern int ExecuteCommand(char command);
extern void SendRectangleCommand(void);
extern void SendCircleCommand(int pos);
extern void SendEndCommand(dataSendtoServer dataS);

#endif
