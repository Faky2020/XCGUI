/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


/*
/////////////////////////////////////////////////
//���Թ�����ͼ ScrollView////////////////////////

BOOL CALLBACK MyEventHScrollView(HELE hEle,HELE hEventEle,int pos)
{
	XTRACE("��ͼˮƽ����,λ��:%d\n",pos);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,400,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����������ͼ
	//HELE hScrollView=XSView_Create(10,10,200,200,hWindow);

	HELE hScrollView=XSView_Create(10,10,100,100,hWindow);
	RECT rect={10,10,300,300};
	XEle_SetRect(hScrollView,&rect);
	XSView_SetSize(hScrollView,500,500); //���ù�����ͼ���ݴ�С

	//XSView_SetBorderColor(hScrollView,RGB(255,0,0));

	//�ڹ�����ͼ���ݷ���һ����ť,�Ա㿴������Ч��
	HELE hView=XSView_GetView(hScrollView);
	HELE hButtn=XBtn_Create(10,150,100,100,L"button",hView);

	XEle_RegisterEvent(hScrollView,XE_HSCROLLVIEW,MyEventHScrollView);
	XRunXCGUI();

	return 0;
}
*/