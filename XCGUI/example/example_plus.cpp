/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "stdafx.h"

/*
class CButtonBase : public CXEventMsg
{
public:
BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent)
{
XTRACE("����� base \n");
return FALSE;
}
int  yy;
};*/

/*
class CButton : public CXEventMsg
{
public:
	HELE m_hButton;
	BOOL Create(HWINDOW hWindow)
	{
		m_hButton=XBtn_Create(10,10,100,25,L"��ʾ��ť",hWindow);

		XCGUI_RegEleEvent(m_hButton,XE_BNCLICK,&CButton::OnEventBtnClick);
		XCGUI_RegEleEvent(m_hButton,XE_KEYDOWN,&CButton::OnEventKeyDown);
		XCGUI_RegEleEvent(m_hButton,XE_DESTROY,&CButton::OnBtnDestroy);
		XCGUI_RegEleMessage(m_hButton,XM_LBUTTONUP,&CButton::EleLButtonUp);
		return TRUE;
	}
	BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent)
	{
		XTRACE("�����\n");
		return FALSE;
	}
	BOOL OnEventKeyDown(HELE hEle,HELE hEventEle,WPARAM wParam,LPARAM lParam)
	{
		XTRACE("��갴��\n");
		return FALSE;
	}
	void OnBtnDestroy(HELE hEle)  //����
	{
		XTRACE("��ť����\n");
	}
	BOOL EleLButtonUp(HELE hEle,UINT flags,POINT *pPt)
	{
		XTRACE("��ť EleLButtonUp\n");
		return FALSE;
	}
};

class CMyWnd : public CXEventMsg
{
public:
	HWINDOW m_hWindow;
	CButton  m_button;
	BOOL Create()
	{
		//��������
		m_hWindow=XWnd_CreateWindow(400,200,400,300,L"�Ųʽ����-����");
		XWnd_ShowWindow(m_hWindow,SW_SHOW);
		m_button.Create(m_hWindow);

		XCGUI_RegWndMessage(m_hWindow,WM_LBUTTONUP,&CMyWnd::OnWndLButtonUp);
		XCGUI_RegWndNCMessage(m_hWindow,XWM_NCLBUTTONUP,&CMyWnd::OnWndNCLButtonUp);
		return TRUE;
	}
	BOOL OnWndLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
	{
		XTRACE("���� OnWndLButtonUp\n");
		return FALSE;
	}
	BOOL OnWndNCLButtonUp(HWINDOW hWindow,UINT flags,POINT *pPt)
	{
		XTRACE("���� OnWndNCLButtonUp\n");
		return FALSE;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	//_CrtSetBreakAlloc(1874); 
	XInitXCGUI();

	CMyWnd  MyWnd;
	MyWnd.Create();

	XRunXCGUI();
	return 0;
}
*/


/*
//CXEventMsg:C++��Ϣ�¼��ӿ���
//CMyWnd:�ҵĴ�����
class CMyWnd : public CXEventMsg
{
public:
	HWINDOW m_hWindow; //���ھ��
	HELE    m_hButton; //��ť���
	
	BOOL Create() //�������ںͰ�ť
	{
		m_hWindow=XWnd_CreateWindow(0,0,400,300,L"�Ųʽ����-����"); //��������
		if(m_hWindow)
		{
			m_hButton =XBtn_Create(10,10,80,25,L"��ť",m_hWindow); //������ť
			XCGUI_RegEleEvent(m_hButton,XE_BNCLICK,&CMyWnd::OnEventBtnClick); //ע�ᰴť����¼�
			
			XWnd_ShowWindow(m_hWindow,SW_SHOW); //��ʾ����
			return TRUE;
		}
		return FALSE;
	}
	BOOL OnEventBtnClick(HELE hEle,HELE hEleEvent) //��ť����¼���Ӧ
	{
		//������Ϣ��
		XMessageBox(hEle,L"�����˰�ť",L"��ʾ",XMB_OK | XMB_CANCEL);
		return FALSE;
	}
};

int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	CMyWnd  MyWnd;
	if(MyWnd.Create())
	{
		XRunXCGUI();
	}
	return 0;
}
*/


/*
XCGUI_RegWndMessage(hWindow,type,memberFunction);//ע�ᴰ����Ϣ

XCGUI_RegWndNCMessage(hWindow,type,memberFunction);//ע�ᴰ���߼��ǿͻ�����Ϣ

XCGUI_RegWndMsgProc(hWindow,memberFunction);//ע�ᴰ����Ϣ�������

XCGUI_RegEleEvent(hEle,type,memberFunction);//ע��Ԫ���¼�

XCGUI_RegEleMessage(hEle,type,memberFunction);//ע��Ԫ����Ϣ

XCGUI_RegEleMsgProc(hEle,type,memberFunction);//ע��Ԫ����Ϣ�������

XCGUI_RegEleEventProc(hEle,type,memberFunction);//ע��Ԫ���¼��������

XCGUI_SView_SetDrawScrollView(hEle,memberFunction);//ע�������ͼ����

XCGUI_List_SetUserDrawItem(hEle,memberFunction);//ע���б������

XCGUI_List_SetUserDrawItemHeader(hEle,memberFunction);//�б�ͷ�����

XCGUI_Tree_SetUserDrawItem(hEle,memberFunction); //�������

XCGUI_ListBox_SetUserDrawItem(hEle,memberFunction); //�б�������
*/