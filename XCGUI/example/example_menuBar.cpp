/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"
/*
HELE hMenuBar;

BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	//�˵�������
	//XMenuBar_DeleteButton(hMenuBar,1);
	//XMenuBar_InsertButton(hMenuBar,L"TSTS",1);
	//XMenuBar_AddMenuItem(hMenuBar,1,207,L"TT1");
	//XMenuBar_AddMenuItem(hMenuBar,1,208,L"TT2");
	//XMenuBar_AddMenuItem(hMenuBar,1,209,L"TT3");
	//XEle_RedrawEle(hMenuBar);

	//XMenuBar_InsertItem(hMenuBar,0,1001,L"1001",NULL,218);
	//XMenuBar_DeleteMenuItem(hMenuBar,0,202);
	XWnd_CloseWindow(XEle_GetHWindow(hEle));
	return FALSE;
}

//�˵���
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(2278);

	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//�����˵���
	hMenuBar=XMenuBar_Create(10,10,300,30,hWindow);
	
	//��Ӳ˵�����ť
	XMenuBar_AddButton(hMenuBar,L"�ļ�");
	XMenuBar_AddButton(hMenuBar,L"�༭");
	XMenuBar_AddButton(hMenuBar,L"��ͼ");

	//��ӵ����˵���
	XMenuBar_AddMenuItemImage(hMenuBar,0,201,L"111",XMENU_ROOT,NULL,XImage_LoadFile(L"image\\149.gif"));
	XMenuBar_AddMenuItemImage(hMenuBar,0,202,L"222",XMENU_ROOT,NULL,XImage_LoadFile(L"image\\150.gif"));
	XMenuBar_AddMenuItem(hMenuBar,0,-1,NULL,XMENU_ROOT,XM_SEPARATOR);
	XMenuBar_AddMenuItemImage(hMenuBar,0,203,L"333",XMENU_ROOT,NULL,XImage_LoadFile(L"image\\151.gif"));

	XMenuBar_AddMenuItem(hMenuBar,1,204,L"444");
	XMenuBar_AddMenuItem(hMenuBar,1,205,L"555");
	XMenuBar_AddMenuItem(hMenuBar,1,206,L"666");

	XMenuBar_AddMenuItem(hMenuBar,2,207,L"777");
	XMenuBar_AddMenuItem(hMenuBar,2,208,L"888");
	XMenuBar_AddMenuItem(hMenuBar,2,209,L"999");


	XMenuBar_AddMenuItem(hMenuBar,0,217,L"3-11",203);
	XMenuBar_AddMenuItem(hMenuBar,0,218,L"3-22",203);
	XMenuBar_AddMenuItem(hMenuBar,0,219,L"3-33",203);

	HELE hButton=XBtn_Create(10,10,60,20,L"��ť",hWindow);

	XEdit_Create(10,50,100,100,hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);

	XRunXCGUI();

	return 0;
}
*/
