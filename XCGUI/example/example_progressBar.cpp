/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/*
////////////������//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����������
	HELE hProgBar1=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar1,0); //���ý���

	HELE hProgBar2=XProgBar_Create(10,50,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar2,30);

	HELE hProgBar3=XProgBar_Create(10,90,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar3,60);

	HELE hProgBar4=XProgBar_Create(10,130,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar4,100);

	HELE hProgBar5=XProgBar_Create(220,10,20,200,FALSE,hWindow);
	XProgBar_SetPos(hProgBar5,60);

	XRunXCGUI();
	return 0;
}
*/

/*
//�޸�ˮƽΪ��ֱ
int  bHorizon=TRUE;
HELE hProgBar=NULL;
BOOL CALLBACK MyEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(bHorizon)
	{
		bHorizon=FALSE;
		XProgBar_SetHorizon(hProgBar,FALSE);
	}else
	{
		bHorizon=TRUE;
		XProgBar_SetHorizon(hProgBar,TRUE);
	}
	XEle_RedrawEle(hProgBar);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,300,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//����������
	hProgBar=XProgBar_Create(10,10,100,100,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,30); //���ý���

	HELE hButton=XBtn_Create(120,10,100,22,L"�ı�",hWindow);
	XEle_RegisterEvent(hButton,XE_BNCLICK,MyEventBtnClick);

	XRunXCGUI();
	return 0;
}
*/

/*
//ˮƽ
////////////��������ͼ//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//XWnd_SetBorderSize(hWindow,8,8,8,30);
	//����������
	HELE hProgBar=XProgBar_Create(10,10,200,20,TRUE,hWindow);
//	HELE hProgBar=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,60); //���ý���

	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/sliderBar1.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/sliderBar2.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt2.jpg"));

	//XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/bkimageBar.jpg"));
	//XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/222.jpg"));
	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt.png"));

	XRunXCGUI();
	return 0;
}
*/

/*
//��ֱ
////////////��������ͼ//////////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	//XWnd_SetBorderSize(hWindow,8,8,8,30);
	//����������
	HELE hProgBar=XProgBar_Create(10,10,20,300,FALSE,hWindow);
//	HELE hProgBar=XProgBar_Create(10,10,200,20,TRUE,hWindow);
	XProgBar_SetPos(hProgBar,60); //���ý���

//	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/sliderBar1.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/sliderBar2.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt2.jpg"));

	XProgBar_SetImage(hProgBar,XImage_LoadFile(L"image/bkimageBar.jpg"));
	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/222.jpg"));
//	XProgBar_SetImage2(hProgBar,XImage_LoadFile(L"image/tt.png"));

	XRunXCGUI();
	return 0;
}
*/