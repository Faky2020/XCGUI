/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



/////////////����Ԫ��/////////////////////////////////
/*
//����Ԫ���¼���Ӧ
BOOL CALLBACK MyEventMonthChange(HELE hEle,HELE hEventEle,BOOL bChenge,BOOL bDownDayNum)
{
	if(bDownDayNum)
		XTRACE("��һ��ͼ");

	if(bChenge)
		XTRACE("���ڸı�\n");
	else
		XTRACE("����δ�ı�\n");

	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	//��������Ԫ��
	HELE hMonth=XMonthCal_Create(10,10,220,200,hWindow);

	XEle_RegisterEvent(hMonth,XE_MONTHCAL_CHANGE,MyEventMonthChange);
	XRunXCGUI();
	return 0;
}*/


/*
//���ڸı��¼�
BOOL CALLBACK MyEventDateTimeChange(HELE hEle,HELE hEventEle)
{
	XTRACE("���ڸı�\n");
	return false;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//�������ڱ༭��Ԫ��
	HELE hMonth=XDateTime_Create(10,10,100,20,hWindow);
	//XEle_EnableBorder(hMonth,FALSE);

	XEle_RegisterEvent(hMonth,XE_DATETIME_CHANGE,MyEventDateTimeChange);
	XRunXCGUI();
	return 0;
}
*/