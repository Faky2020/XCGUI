/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"



/////////////////////////////////////////////////
//���Թ�����ScrollBar////////////////////////////
/*

BOOL CALLBACK MyEventHScroll(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("��ǰλ��:%d\n",pos);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,280,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ˮƽ������
	HELE hHScrollBar=XSBar_Create(10,100,200,18,SY_HSCROLL,hWindow);
	XSBar_SetScrollRange(hHScrollBar,20); //���ù�����Χ
//	XSBar_ScrollPos(hHScrollBar,10); //������ָ��λ��

	//������ֱ������
//	HELE hVScrollBar=XSBar_Create(250,10,18,200,SY_VSCROLL,hWindow);

	//XSBar_SetImage(hHScrollBar,L"image/123.jpg");
	//XSBar_EnableImageStretch(hHScrollBar,TRUE);

	//XSBar_SetImageLeaveUp(hHScrollBar,L"image/123.jpg");

	//ע���¼�
	XEle_RegisterEvent(hHScrollBar,XE_VSCROLL,MyEventHScroll);
	XRunXCGUI();
	return 0;
}
*/



/*
//�޸�ˮƽ������Ϊ��ֱ������
int  bHorizon=TRUE;
HELE hHScrollBar=NULL;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bHorizon)
	{
		bHorizon=FALSE;
		XSBar_SetHorizon(hHScrollBar,FALSE);
	}else
	{
		bHorizon=TRUE;
		XSBar_SetHorizon(hHScrollBar,TRUE);
	}
	XEle_RedrawEle(hHScrollBar);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,280,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����ˮƽ������
	hHScrollBar=XSBar_Create(10,10,200,200,SY_HSCROLL,hWindow);
	XSBar_SetScrollRange(hHScrollBar,100); //���ù�����Χ
	XSBar_ScrollPos(hHScrollBar,10);   //������ָ��λ��

	HELE hButton=XBtn_Create(220,10,100,22,L"�ı�",hWindow);

	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XRunXCGUI();
	return 0;
}*/
