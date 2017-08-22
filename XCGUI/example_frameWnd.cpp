/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


#if 0

HWINDOW hWindow=NULL;
HELE hPane1=NULL;
HELE hPane2=NULL;
HELE hPane3=NULL;
HELE hPane4=NULL;

//���²˵�״̬
void CALLBACK OnMenu_UpdateUI(HMENUX hMenu,int id)
{
	XTRACE("OnMenu_UpdateUI() id=%d \n",id);

	HELE hPaneCur=NULL;
	switch(id)
	{
	case 301: hPaneCur=hPane1; break;
	case 302: hPaneCur=hPane2; break;
	case 303: hPaneCur=hPane3;break;
	case 304: hPaneCur=hPane4; break;
	default: return ;
	}

	if(NULL==hPaneCur) return ;
	pane_state_ state=XPane_GetState(hPaneCur);
	switch(state)
	{
	case pane_state_lock:
		XMenu_SetItemCheck(hMenu,id,TRUE);
		break;
	case pane_state_dock:
		XMenu_SetItemCheck(hMenu,id,FALSE);
		break;
	case pane_state_hide:
		XMenu_SetItemCheck(hMenu,id,FALSE);
		break;
	case pane_state_float:
		{
			HWINDOW hFloatWnd=XEle_GetHWindow(hPaneCur);
			if(hFloatWnd && XC_FLOATWND==XC_GetObjectType(hFloatWnd))
			{
				if(IsWindowVisible(XEle_GetHWnd(hPaneCur)))
					XMenu_SetItemCheck(hMenu,id,TRUE);
				else
					XMenu_SetItemCheck(hMenu,id,FALSE);
			}
		}break;
	}
	return ;
}

//�˵�ѡ���¼�,��ʾ���ش���
BOOL CALLBACK OnEventMenuSelect(HELE hEle,HELE hEventEle,int id)
{
	if(hEle!=hEventEle)
		return FALSE;

	if(302==id)
	{
	//	XPane_SetTitle(hPane2,L"123");
	//	XPane_Destroy(hPane2);
	//	XFrameWnd_AdjustLayout(hWindow);
	//	XWnd_RedrawWnd(hWindow);
		return FALSE;
	}
	HELE hPaneCur=NULL;
	switch(id)
	{
	case 301: hPaneCur=hPane1; break;
	case 302: hPaneCur=hPane2; break;
	case 303: hPaneCur=hPane3;break;
	case 304: hPaneCur=hPane4; break;
	default: return FALSE;
	}
	if(NULL==hPaneCur) return FALSE;

	HMENUX hMenu=XMenuBar_GetMenu(hEle,2);

	pane_state_ state=XPane_GetState(hPaneCur);
	switch(state)
	{
	case pane_state_lock:
		XPane_Hide(hPaneCur);
		break;
	case pane_state_dock:
		XPane_popup(hPaneCur);
		break;
	case pane_state_hide:
		XPane_Show(hPaneCur);
		break;
	case pane_state_float:
		{
			HWINDOW hFloatWnd=XEle_GetHWindow(hPaneCur);
			if(hFloatWnd && XC_FLOATWND==XC_GetObjectType(hFloatWnd))
			{
				HWND hWnd=XEle_GetHWnd(hPaneCur);
				if(IsWindowVisible(hWnd))
					XWnd_ShowWindow(hFloatWnd,SW_HIDE);
				else
					XWnd_ShowWindow(hFloatWnd,SW_SHOW);
			}
		}break;
	}
	XFrameWnd_AdjustLayout(XEle_GetHWindow(hEle));
	XWnd_RedrawWnd(hWindow);

	return FALSE;
}

BOOL CALLBACK MyEventMouseStay(HELE hEle,HELE hEventEle)
{
	//XTRACE("stay \n");
	return TRUE;
}

BOOL CALLBACK MyEventMouseLeave(HELE hEle,HELE hEventEle)
{
	//XTRACE("leave \n");
	return TRUE;
}

BOOL CALLBACK MyEventPaneLock(HELE hEle,HELE hEventEle)
{
	XTRACE("lock \n");
	return TRUE;
}

BOOL CALLBACK MyEventPaneDock(HELE hEle,HELE hEventEle)
{
	XTRACE("dock \n");
	return TRUE;
}

BOOL CALLBACK MyEventPaneFloat(HELE hEle,HELE hEventEle)
{
	XTRACE("float \n");
	return TRUE;
}


int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
 	hWindow=XFrameWnd_CreateWindow(0,0,600,500,L"�Ųʽ����-��ܴ���");

	HELE hMenuBar=XMenuBar_Create(10,10,300,26,hWindow);
	XMenuBar_AddButton(hMenuBar,L"��ͼ");

	//��ӵ����˵���
	XMenuBar_AddMenuItem(hMenuBar,0,301,L"��ͼ-1");
	XMenuBar_AddMenuItem(hMenuBar,0,302,L"��ͼ-2");
	XMenuBar_AddMenuItem(hMenuBar,0,303,L"��ͼ-3");
	XMenuBar_AddMenuItem(hMenuBar,0,304,L"��ͼ-4");

	HMENUX hMenux=XMenuBar_GetMenu(hMenuBar,0);
	XMenu_SetUserUpdateUI(hMenux,OnMenu_UpdateUI); //���²˵�״̬

	//��������
	hPane1=XPane_Create(L"����1-----",hWindow);
	hPane2=XPane_Create(L"����2-----",hWindow);
	hPane3=XPane_Create(L"����3-----",hWindow);
 	hPane4=XPane_Create(L"����4-----",hWindow);

	XFrameWnd_AddPane(hWindow,NULL,hPane1,align_any);        //���Ӵ���hPane1����ܴ���
	XFrameWnd_AddPane(hWindow,hPane1,hPane4,align_right,50); //���Ӵ����Ҳ�

	HPANE_GROUP hGroup=XFrameWnd_MergePane(hWindow,hPane1,hPane2); //���´���hPane2�ϲ�Ϊ��
	XFrameWnd_MergePaneToGroup(hWindow,hGroup,hPane3);             //���´���hPane3�ϲ�����

/*
	HELE hEleView=XEle_Create(0,0,100,100,hPane1);
	XEle_SetBkColor(hEleView,RGB(255,0,0));
	XEle_EnableBorder(hEleView,FALSE);
	XPane_SetView(hPane1,hEleView); //Ϊ����hPane1����ͼ
*/
/*
	HELE hScrollView=XSView_Create(0,0,100,100,hPane1);
	XPane_SetView(hPane1,hScrollView);
	XSView_SetSize(hScrollView,500,800);
	HELE hView=XSView_GetView(hScrollView);
	XEle_SetBkColor(hView,RGB(255,0,0));

	//HELE hTree=XTree_Create(10,60,200,250,hView);
	HELE hTree=XSView_Create(10,60,200,250,hView);

	HELE hTreeView=XSView_GetView(hTree);
	XEle_SetBkColor(hTreeView,RGB(0,255,0));
*/
	XPane_SetFixedSize(hPane4,TRUE); //�̶�����4��С

	XEle_RegisterEvent(hMenuBar,XE_MENUSELECT,OnEventMenuSelect);
	XEle_RegisterEvent(hPane1,XE_MOUSESTAY,MyEventMouseStay);
	XEle_RegisterEvent(hPane1,XE_MOUSELEAVE,MyEventMouseLeave);

	XEle_RegisterEvent(hPane1,XE_PANE_LOACK,MyEventPaneLock);

	XEle_RegisterEvent(hPane1,XE_PANE_DOCK,MyEventPaneDock);
	XEle_RegisterEvent(hPane2,XE_PANE_DOCK,MyEventPaneDock);
	XEle_RegisterEvent(hPane3,XE_PANE_DOCK,MyEventPaneDock);
	XEle_RegisterEvent(hPane4,XE_PANE_DOCK,MyEventPaneDock);
	XEle_RegisterEvent(hPane1,XE_PANE_FLOAT,MyEventPaneFloat);

	//������������ť
	HELE hToolBtn1=XToolBarBtn_Create(2,2,L"����1");
	HELE hToolBtn2=XToolBarBtn_Create(2,2,L"����2");
	HELE hToolBtn3=XToolBarBtn_Create(2,2,L"����3");
	HELE hToolBtn4=XToolBarBtn_Create(2,2,L"����4");
	HELE hToolBtn5=XToolBarBtn_Create(2,2,L"�ı�5");

	HELE hToolBar=XToolBar_Create(0,0,20,26,hWindow);
	//��Ԫ����ӵ���������
	XToolBar_InsertEle(hToolBar,hToolBtn1);
	XToolBar_InsertEle(hToolBar,hToolBtn2);
	XToolBar_InsertEle(hToolBar,hToolBtn3);
	XToolBar_InsertEle(hToolBar,hToolBtn4);
	XToolBar_InsertEle(hToolBar,hToolBtn5);
	XToolBar_InsertSeparator(hToolBar,1);
	//����ָ��Ԫ��
	XEle_EnableEle(hToolBtn3,false);
	//�Զ�������������ť��С
	XToolBarBtn_Adjust(hToolBtn1);
	XToolBarBtn_Adjust(hToolBtn2);
	XToolBarBtn_Adjust(hToolBtn3);
	XToolBarBtn_Adjust(hToolBtn4);
	XToolBarBtn_Adjust(hToolBtn5);

	//XPane_SetToolBar(hPane1,hToolBar);
	

	//XFrameWnd_AdjustLayout(hWindow); //������ܴ��ڲ���
	XWnd_ShowWindow(hWindow,SW_SHOW);
	XRunXCGUI();
	return 0;
}

#endif

/*
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XFrameWnd_CreateWindow(0,0,600,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	
	//XToolBar_Create(0,0,100,26,hWindow);

	//����������
	HELE m_hToolBar=XToolBar_Create(0,0,10,32,hWindow);
	HELE hButtonMenu=XToolBarBtn_Create(20,20,L"���˵�");
	HELE hButton1=XToolBarBtn_Create(20,20,L"�½�");
	HELE hButton2=XToolBarBtn_Create(20,20,L"���");
	HELE hButton3=XToolBarBtn_Create(20,20,L"����(&S)");
	HELE hButton4=XToolBarBtn_Create(20,20,L"�ر�(&F4)");
	HELE hButton5=XToolBarBtn_Create(20,20,L"ִ��(&F5)");
	HELE hButton6=XToolBarBtn_Create(20,20,L"���");

	XBtn_SetIcon(hButtonMenu,XImage_LoadFile(L"image_ui/mainMenu.png"));
	XBtn_SetIcon(hButton1,XImage_LoadFile(L"image_ui/addFile.png"));
	XBtn_SetIcon(hButton2,XImage_LoadFile(L"image_ui/openFile.png"));
	XBtn_SetIcon(hButton3,XImage_LoadFile(L"image_ui/saveFile.png"));
	XBtn_SetIcon(hButton4,XImage_LoadFile(L"image_ui/closeFile.png"));
	XBtn_SetIcon(hButton5,XImage_LoadFile(L"image_ui/run.png"));
	XBtn_SetIcon(hButton6,XImage_LoadFile(L"image_ui/compress.png"));

	XToolBar_InsertEle(m_hToolBar,hButtonMenu);
	XToolBar_InsertSeparator(m_hToolBar);
	XToolBar_InsertEle(m_hToolBar,hButton1);
	XToolBar_InsertEle(m_hToolBar,hButton2);
	XToolBar_InsertEle(m_hToolBar,hButton3);
	XToolBar_InsertEle(m_hToolBar,hButton4);
	XToolBar_InsertEle(m_hToolBar,hButton5);
	XToolBar_InsertEle(m_hToolBar,hButton6);
	XToolBar_InsertSeparator(m_hToolBar);

	XToolBarBtn_Adjust(hButtonMenu);
	XToolBarBtn_Adjust(hButton1);
	XToolBarBtn_Adjust(hButton2);
	XToolBarBtn_Adjust(hButton3);
	XToolBarBtn_Adjust(hButton4);
	XToolBarBtn_Adjust(hButton5);
	XToolBarBtn_Adjust(hButton6);


	HELE hPane1=XPane_Create(10,10,100,100,L"����",hWindow);	//������ͼ
	HELE hPane2=XPane_Create(10,10,100,100,L"����",hWindow);	//������ͼ
	HELE hPane3=XPane_Create(10,10,100,100,L"������",hWindow);	//��������ͼ
	HELE hPane4=XPane_Create(10,10,100,100,L"��ʾ",hWindow);	//��ʾ��ͼ

	XFrameWnd_AddPane(hWindow,NULL,hPane1,align_any);
	XFrameWnd_AddPane(hWindow,hPane1,hPane2,align_right,70);
	XFrameWnd_AddPane(hWindow,hPane2,hPane3,align_right,35);
	XFrameWnd_AddPane(hWindow,NULL,hPane4,align_bottom,30);

	HELE hPane5=XPane_Create(10,10,100,100,L"�ļ�",hWindow); //�ļ���ͼ
	HELE hPane6=XPane_Create(10,10,100,100,L"��ϵ",hWindow); //��ϵ��ͼ

	HELE hPane7=XPane_Create(10,10,100,100,L"��ʽ",hWindow); //��ʽ
	HELE hPane8=XPane_Create(10,10,100,100,L"��Դ",hWindow); //��Դ

	XFrameWnd_MergePane(hWindow,hPane1,hPane5);
	XFrameWnd_MergePane(hWindow,hPane1,hPane6);

	XFrameWnd_MergePane(hWindow,hPane2,hPane7);
	XFrameWnd_MergePane(hWindow,hPane2,hPane8);

	layoutCell_ *pDest1=Pane_GetCell(hPane1);
	layoutCell_ *pDest2=Pane_GetCell(hPane2);
	layoutCell_ *pDest3=Pane_GetCell(hPane3);
	layoutCell_ *pDest4=Pane_GetCell(hPane4);
	layoutCell_ *pDest5=Pane_GetCell(hPane5);


	XFrameWnd_AdjustLayout(hWindow);

	XRunXCGUI();
	return 0;
}



/*
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XFrameWnd_CreateWindow(0,0,600,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	

	HELE hPane1=XPane_Create(10,10,100,100,L"����1",hWindow);	//������ͼ
	HELE hPane2=XPane_Create(10,10,100,100,L"����2",hWindow);	//������ͼ
	HELE hPane3=XPane_Create(10,10,100,100,L"����3",hWindow);	//������ͼ
	HELE hPane4=XPane_Create(10,10,100,100,L"����4",hWindow);	//������ͼ

	XFrameWnd_AddPane(hWindow,NULL,hPane1);

	XFrameWnd_AddPane(hWindow,hPane1,hPane3,align_left,50);
	XFrameWnd_AddPane(hWindow,hPane3,hPane4,align_right,50);

	XFrameWnd_MergePane(hWindow,hPane1,hPane2);

	//XFrameWnd_AddPane(hWindow,hPane1,hPane2,align_right);

//	XFrameWnd_AddPane(hWindow,hPane3,hPane4,align_right);

	//XFrameWnd_MergePane(hWindow,hPane2,hPane3);
	//XFrameWnd_MergePane(hWindow,hPane3,hPane4);

	//XPane_Hide(hPane1);
	//XPane_Hide(hPane2);
	//XPane_Hide(hPane3);
	XFrameWnd_AdjustLayout(hWindow);

	//XPane_SetFixedSize(hPane2,TRUE);

	//XEle_ShowEle(hPane2,FALSE);


	XRunXCGUI();
	return 0;
}*/


/*
int APIENTRY _tWinMain(HINSTANCE hInstance,  HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	XInitXCGUI();

	//��������
	HWINDOW hWindow=XFrameWnd_CreateWindow(0,0,600,500,L"�Ųʽ����-����");
	XWnd_ShowWindow(hWindow,SW_SHOW);
	

	HELE hPane1=XPane_Create(10,10,100,100,L"����1",hWindow);	//������ͼ
	HELE hPane2=XPane_Create(10,10,100,100,L"����2",hWindow);	//������ͼ
//	HELE hPane3=XPane_Create(10,10,100,100,L"����3",hWindow);	//������ͼ
//	HELE hPane4=XPane_Create(10,10,100,100,L"����4",hWindow);	//������ͼ

	XFrameWnd_AddPane(hWindow,NULL,hPane1,align_any);
	XFrameWnd_AddPane(hWindow,hPane1,hPane2,align_bottom,60);

	XFrameWnd_AdjustLayout(hWindow);

	//XEle_ShowEle(hPane2,FALSE);
	//XPane_Hide(hPane2);

	XRunXCGUI();
	return 0;
}
*/