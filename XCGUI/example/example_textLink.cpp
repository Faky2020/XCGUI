/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/*
BOOL CALLBACK OnLinkClick(HELE hEle,HELE hEventEle) //�¼���Ӧ
{
	XMessageBox(hEle,L"����վ:http://www.xcgui.com/",L"��ʾ",XMB_OK);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"�Ųʽ����-����");

	//�����ļ�����Ԫ��
	HELE hLink=XTextLink_Create(10,10,138,20,L"http://www.xcgui.com/",hWindow);

	XEle_RegisterEvent(hLink,XE_BNCLICK,OnLinkClick);//ע���¼�

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}*/



/*
BOOL CALLBACK OnLinkClick(HELE hEle,HELE hEventEle) //�¼���Ӧ
{
//	XMessageBox(hEle,L"����վ:http://www.xcgui.com/",L"��ʾ",XMB_OK);
	return FALSE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������:
	HWINDOW hWindow=XWnd_CreateWindow(0,0,300,200,L"�Ųʽ����-����");

	//�����ļ�����Ԫ��
	HELE hLink=XTextLink_Create(10,10,200,20,L"http://www.xcgui.com/",hWindow);
	XEle_SetBkColor(hLink,RGB(255,0,0));

	//XTextLink_ShowUnderline(hLink,TRUE,TRUE);

	XTextLink_AdjustSize(hLink);
	//XEle_RegisterEvent(hLink,XE_BNCLICK,OnLinkClick);//ע���¼�

	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}
*/