/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"


#if 0

class CModalX : public CXEventMsg
{
public:
	void Reg(HWINDOW hModal)
	{
		XCGUI_RegWndMessage(hModal,500,&CModalX::OnWndOther);
	}

	BOOL OnWndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam)
	{
		return TRUE;
	}
};

//BOOL CALLBACK OnWndOther(HWINDOW hWindow,WPARAM wParam,LPARAM lParam)
//{
//	return TRUE;
//}

//ģ̬���ڹر� - ȷ����ť
BOOL CALLBACK My_EventBtnClick_OK(HELE hEle,HELE hEventEle)
{

	//PostMessage(XEle_GetHWnd(hEle),500,2,2);
	XModalWnd_DoOk(XEle_GetHWindow(hEle));
	return TRUE;
}

//ģ̬���ڹر� - ȡ����ť
BOOL CALLBACK My_EventBtnClick_Cancel(HELE hEle,HELE hEventEle)
{
	XModalWnd_DoCancel(XEle_GetHWindow(hEle));
	return TRUE;
}

//�¼���Ӧ
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	//����ģ̬����
	HWINDOW hModal=XModalWnd_CreateWindow(200,200,L"�Ųʽ����-ģ̬����",XEle_GetHWnd(hEle));
	XWnd_EnableDragBorder(hModal,FALSE);
//	XWnd_SetTransparentFlag(hModal,XC_WIND_TRANSPARENT_SHADOW);
//	XWnd_SetTransparentAlpha(hModal,180); //����͸����

	HELE hBtnOk=XBtn_Create(10,10,60,22,L"ȷ��",hModal);
	HELE hBtnCancel=XBtn_Create(100,10,60,22,L"ȡ��",hModal);
	//ע���¼�
	XEle_RegisterEvent(hBtnOk,XE_BNCLICK,My_EventBtnClick_OK);
	XEle_RegisterEvent(hBtnCancel,XE_BNCLICK,My_EventBtnClick_Cancel);

//	XWnd_RegisterMessage(hModal,500,&mm::OnWndOther);
	CModalX  mm;
	mm.Reg(hModal);

	//����ģ̬����
	int result=XModalWnd_DoModal(hModal);
	if(XMB_OK==result)
	{
		//ȷ����ť
	}else if(XMB_CANCEL==result)
	{
		//ȡ����ť
	}else if(0==result)
	{
		//������ʽ
	}

	return TRUE;
}
//ģ̬���ڲ���/////////////////////////////////
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"�Ųʽ����-ģ̬���ڲ���");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	
	XWnd_SetTransparentFlag(hWindow,XC_WIND_TRANSPARENT_SHADOW);
//	XWnd_SetTransparentAlpha(hWindow,220); //����͸����

	HELE hButton=XBtn_Create(10,10,100,25,L"����ģ̬����",hWindow);

	//ע���¼�
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);

	XRunXCGUI();

	return 0;
}

#endif


#if 0
//ģ̬���ڹر� - ȷ����ť
BOOL CALLBACK My_EventBtnClick_OK(HELE hEle,HELE hEventEle)
{

	XModalWnd_DoOk(XEle_GetHWindow(hEle));
	return TRUE;
}

//ģ̬���ڹر� - ȡ����ť
BOOL CALLBACK My_EventBtnClick_Cancel(HELE hEle,HELE hEventEle)
{
	XModalWnd_DoCancel(XEle_GetHWindow(hEle));
	return TRUE;
}

BOOL CALLBACK My_EventBtnClick2(HELE hEle,HELE hEventEle)
{

	//����ģ̬����
	HWINDOW hModal=XModalWnd_CreateWindow(200,200,L"�Ųʽ����-ģ̬����",XEle_GetHWnd(hEle));
	XWnd_EnableDragBorder(hModal,FALSE);
	//	XWnd_SetTransparentFlag(hModal,XC_WIND_TRANSPARENT_SHADOW);
	//	XWnd_SetTransparentAlpha(hModal,180); //����͸����

	HELE hBtnOk=XBtn_Create(10,10,60,22,L"ȷ��",hModal);
	HELE hBtnCancel=XBtn_Create(100,10,60,22,L"ȡ��",hModal);
	//ע���¼�
	XEle_RegisterEvent(hBtnOk,XE_BNCLICK,My_EventBtnClick_OK);
	XEle_RegisterEvent(hBtnCancel,XE_BNCLICK,My_EventBtnClick_Cancel);

	//	XWnd_RegisterMessage(hModal,500,&mm::OnWndOther);
//	CModalX  mm;
//	mm.Reg(hModal);

	//����ģ̬����
	int result=XModalWnd_DoModal(hModal);
	if(XMB_OK==result)
	{
		//ȷ����ť
	}else if(XMB_CANCEL==result)
	{
		//ȡ����ť
	}else if(0==result)
	{
		//������ʽ
	}

	return TRUE;
}
HWINDOW hWindow=NULL;
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	HWND hWnd=XWnd_GetHWnd(hWindow);
	//��������
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,300,L"�Ųʽ����-ģ̬���ڲ���2",hWnd);
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hButton=XBtn_Create(10,10,100,25,L"����ģ̬����2",hWindow);

	//ע���¼�
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick2);

	return TRUE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();
	//��������
	hWindow=XWnd_CreateWindow(0,0,300,300,L"�Ųʽ����-ģ̬���ڲ���");
	XWnd_ShowWindow(hWindow,SW_SHOW);

	HELE hButton=XBtn_Create(10,10,100,25,L"����ģ̬����",hWindow);

	//ע���¼�
	XEle_RegisterEvent(hButton,XE_BNCLICK,My_EventBtnClick);

	XRunXCGUI();

	return 0;
}
#endif

