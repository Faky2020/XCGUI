/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


struct comboBoxWindow_
{
	window_ window; //�̳�
	//-------------------------------------
	HELE  hComboBox;

	HELE   hListBox; //�б��
};


//����API:
HWINDOW ComboBoxWnd_CreateWindow(int x,int y,int cx,int cy,HWND hWndParent,HELE hComboBox);


//˽�з���:
BOOL ComboBoxWnd_Init(HWINDOW hWindow,int x,int y,int cx,int cy,HWND hWndParent,int exType);

void ComboBoxWnd_SendEvent(comboBox_ *pComboBox,int index);

//�ص�����:
BOOL CALLBACK ComboBoxWnd_OnDrawWindow(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK ComboBoxWnd_OnKillFocus(HWINDOW hWindow); //����ʧȥ����

BOOL CALLBACK ComboBoxWnd_OnEventListBoxSelect(HELE hEle,HELE hEventEle,int index);