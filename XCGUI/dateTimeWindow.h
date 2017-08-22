/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//��������ѡ�񴰿�
struct dateTimeWindow_
{
	window_ window; //�̳�
	//-------------------------
	HELE hDateTime; //�¼�����
	HELE hMonthCal; //����Ԫ��
};

//����API:
HWINDOW DateTimeWnd_CreateWindow(int x,int y,int cx,int cy,HWND hWndParent);


//˽�з���:
BOOL DateTimeWnd_Init(HWINDOW hWindow,int x,int y,int cx,int cy,HWND hWndParent,int exType);
void DateTimeWnd_SetDate(HWINDOW hWindow,int year,int month,int day);
int  DateTimeWnd_GetYear(HWINDOW hWindow);
int  DateTimeWnd_GetMonth(HWINDOW hWindow);
int  DateTimeWnd_GetDay(HWINDOW hWindow);

//�ص�����
BOOL CALLBACK DateTimeWnd_OnDrawWindow(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK DateTimeWnd_OnNCLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt);
BOOL CALLBACK DateTimeWnd_OnKillFocus(HWINDOW hWindow); //����ʧȥ����

BOOL CALLBACK DateTimeWnd_OnEventMonthSelect(HELE hEle,HELE hEventEle,BOOL bChange,BOOL bDownDayNum);
