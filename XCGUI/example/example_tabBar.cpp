/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/*
HELE hTabBar=NULL;//Ԫ�ؾ��
BOOL CALLBACK OnButtonClick(HELE hEle,HELE hEventEle) //��ť�¼�
{
	XTabBar_SetSelect(hTabBar,1); //ѡ��TabBar��ǩ
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"�Ųʽ����-����");

	HELE hButton1=XBtn_Create(10,50,100,20,L"111",hWindow);
	HELE hButton2=XBtn_Create(10,80,100,20,L"222",hWindow);
	HELE hButton3=XBtn_Create(10,110,100,20,L"333",hWindow);
	XEle_ShowEle(hButton2,FALSE);
	XEle_ShowEle(hButton3,FALSE);

	hTabBar=XTabBar_Create(10,10,180,25,hWindow);
	XTabBar_AddLabel(hTabBar,L"aaaaaaa",hButton1);
	XTabBar_AddLabel(hTabBar,L"bbbbbb",hButton2);
	XTabBar_AddLabel(hTabBar,L"ccccccc",hButton3);
	XTabBar_AddLabel(hTabBar,L"dddddd");
	XTabBar_AddLabel(hTabBar,L"eeeeee");

//	XTabBar_SetAlign(hTabBar,align_bottom);
//	XTabBar_EnableTile(hTabBar,TRUE);

	HELE hButton=XBtn_Create(230,10,80,20,L"ѡ�� b",hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,OnButtonClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}*/