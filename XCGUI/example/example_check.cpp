/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/*

//�¼���Ӧ
BOOL CALLBACK My_EventBtnClick(HELE hEle,HELE hEventEle)
{
	wchar_t *pText=XBtn_GetText(hEventEle);
	if(XBtn_IsCheck(hEventEle)) //��ǰ״̬
	{
		XTRACEW(L"%s FALSE\n",pText);
	}else
	{
		XTRACEW(L"%s TRUE\n",pText);
	}
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XWnd_CreateWindow(400,200,300,200,L"�Ųʽ����-����");

	//������ѡ��ť
	HELE hCheck1=XCheck_Create(10,10,60,20,L"check1",hWindow);
	HELE hCheck2=XCheck_Create(10,30,60,20,L"check2",hWindow);
	HELE hCheck3=XCheck_Create(10,50,60,20,L"check3",hWindow);
	HELE hCheck4=XCheck_Create(10,70,60,20,L"check4",hWindow);
	HELE hCheck5=XCheck_Create(10,90,60,20,L"check5",hWindow);
	XBtn_SetCheck(hCheck2,TRUE);
	XEle_EnableEle(hCheck2,FALSE);

	//ע���¼�
	XEle_RegisterEvent(hCheck1,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck2,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck3,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck4,XE_BNCLICK,My_EventBtnClick);
	XEle_RegisterEvent(hCheck5,XE_BNCLICK,My_EventBtnClick);

	XWnd_ShowWindow(hWindow,SW_SHOW);

	XRunXCGUI();
	return 0;
}
*/