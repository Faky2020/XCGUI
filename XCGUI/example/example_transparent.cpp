/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

#if 0

//����͸������
HWINDOW hWindow=NULL;
BOOL CALLBACK OnButtonClick1(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHAPED);//����͸������
	return TRUE;
}
BOOL CALLBACK OnButtonClick2(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_NO); //�ر�͸������
	return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(""); //��ʼ�������
// FD8I-32NR-82N4-1HF81  934
	hWindow=XWnd_CreateWindow(0,0,282,250,L"�Ųʽ����-����");
	XWnd_SetImageNC(hWindow,XImage_LoadFile(L"image\\bk.png")); //���ô��ڱ���ͼƬ
	//XWnd_EnableImageNCStretch(hWindow,TRUE);
	XWnd_SetTransparentAlpha(hWindow,255); //����͸����

	HELE hButton1=XBtn_Create(20,20,80,22,L"����͸��",hWindow); //������ť
	XEle_SetBkTransparent(hButton1,TRUE);
	XEle_RegisterEvent(hButton1,XE_BNCLICK,OnButtonClick1);

	HELE hButton2=XBtn_Create(20,50,80,22,L"�ر�͸��",hWindow); //������ť
	XEle_SetBkTransparent(hButton2,TRUE);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,OnButtonClick2);

	XEdit_Create(20,80,100,20,hWindow); //�����༭��


	HELE hTT=XBtn_Create(250,100,200,200,L"tt",hWindow);
//	XBtn_SetImageLeave(hTT,XImage_LoadFile(L"image\\ico_dsmain.png"));
//	XBtn_SetImageLeave(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
//	XBtn_SetImageStay(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
//	XBtn_SetImageDown(hTT,XImage_LoadFile(L"image\\tt2.jpg"));
	XEle_SetBkTransparent(hTT,TRUE);
	XEle_EnableTransparentChannel(hTT,TRUE);

	//XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHAPED);//����͸������

	XWnd_ShowWindow(hWindow,SW_SHOW); //��ʾ����


	XRunXCGUI(); //����

	return 0;
}
#endif 

/*
//����͸����Ӱ����
HWINDOW hWindow=NULL;
BOOL CALLBACK OnButtonClick1(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHADOW);//����͸������,�߿���Ӱ
	return FALSE;
}
BOOL CALLBACK OnButtonClick2(HELE hEle,HELE hEventEle)
{
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_NO); //�ر�͸������
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI(); //��ʼ�������

	hWindow=XWnd_CreateWindow(0,0,300,300,L"�Ųʽ����-����");
	XWnd_SetTransparentAlpha(hWindow,180); //����͸����

	HELE hButton1=XBtn_Create(20,20,80,22,L"����͸��",hWindow); //������ť
	XEle_SetBkTransparent(hButton1,TRUE);
	XEle_RegisterEvent(hButton1,XE_BNCLICK,OnButtonClick1);

	HELE hButton2=XBtn_Create(20,50,80,22,L"�ر�͸��",hWindow); //������ť
	XEle_SetBkTransparent(hButton2,TRUE);
	XEle_RegisterEvent(hButton2,XE_BNCLICK,OnButtonClick2);

	XEdit_Create(20,80,100,20,hWindow); //�����༭��

	XWnd_ShowWindow(hWindow,SW_SHOW);  //��ʾ����
	XRunXCGUI(); //����

	return 0;
}
*/