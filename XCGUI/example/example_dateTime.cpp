/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


/////����Ԫ��//////////////////////////////
/*
BOOL CALLBACK MyEventDateTimePopupMonthCal(HELE hEle,HELE hEventEle)
{
	XTRACE("popup \n");
	return FALSE;
}

BOOL CALLBACK MyEventDateTimeExitMonthCal(HELE hEle,HELE hEventEle)
{
	XTRACE("exit \n");
	return FALSE;
}

//���ڸı��¼�
BOOL CALLBACK MyEventDateTimeChange(HELE hEle,HELE hEventEle)
{
	XTRACE("���ڸı�\n");
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//�������ڱ༭��Ԫ��
	HELE hMonth=XDateTime_Create(10,10,100,20,hWindow);

	//XDateTime_SetImage(hMonth,XImage_LoadFile(L"image/123.jpg"));

	XEle_RegisterEvent(hMonth,XE_DATETIME_CHANGE,MyEventDateTimeChange);

	XEle_RegisterEvent(hMonth,XE_DATETIME_POPUP_MONTHCAL,MyEventDateTimePopupMonthCal);
	XEle_RegisterEvent(hMonth,XE_DATETIME_EXIT_MONTHCAL,MyEventDateTimeExitMonthCal);

	XRunXCGUI();
	return 0;
}
*/