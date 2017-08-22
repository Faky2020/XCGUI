/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//���ִ���

struct layoutCell_;

struct layoutPane_
{
	ele_  ele; //�̳�
	//----------------------------------
	layoutCell_  *pCell;          //����󶨵ĵ�Ԫ��
	pane_state_  state;           //����1 ͣ��2 ����3 �ر�4
	int          captionHeight;   //�������߶�
	HSTRING      hTitle;          //����

	BOOL         bDownCaption;    //��갴�ڴ����������
	POINT        downPt;          //����ڱ������ϵ�����

	int          bFixedSize;      //����̶���С,���Ϊ-1�ǹ̶���С
	BOOL         bActivate;     //�����Ƿ񼤻� WA_ACTIVE

	BOOL         bInFrame; //�����Ƿ��ڿ����ͼ

	HELE hBtnClose;  //�رհ�ť
	HELE hAutoHide;  //�Զ�����
	HELE hBtnMenu;   //�˵���ť

	align_type_  dockAlign;  //�������ĸ���ͷ��

	HELE  hView;    //�ͻ�������ͼԪ��
	HELE  hToolBar; //������
	HELE  hMenuBar; //�˵���

	int left,top,right,bottom; //��ͼ�߿���
};

//ÿ�����񸽴�һ�����ֵ�Ԫ��


//API:
XC_API HELE WINAPI XPane_Create(wchar_t *pTitle=NULL,HWINDOW hFrameWnd=NULL);  //������ť
XC_API wchar_t* WINAPI XPane_GetTitle(HELE hEle);
XC_API void WINAPI XPane_Hide(HELE hEle);      //���ش���
XC_API void WINAPI XPane_Dock(HELE hEle);      //ͣ������,�Զ�����
XC_API void WINAPI XPane_Lock(HELE hEle);      //��������
XC_API void WINAPI XPane_popup(HELE hEle);     //��������,������ͷ��
XC_API void WINAPI XPane_Show(HELE hEle);     //����-��ʾ��������

XC_API HPANE_GROUP WINAPI XPane_GetGroup(HELE hEle); //��ȡ����������,���û���鷵�ؿ�

//��ʾ����,���Լ�����������صĴ���

XC_API BOOL WINAPI XPane_Destroy(HELE hEle); //���ٴ��� 


XC_API pane_state_ WINAPI XPane_GetState(HELE hEle);  //��ȡ״̬

XC_API void WINAPI XPane_DragPane(HELE hEle,POINT *pPtDown); //�϶�����
XC_API void WINAPI XPane_DragGroup(HELE hEle,POINT *pPtDown);//�϶�������
XC_API void WINAPI XPane_FloatPane(HELE hEle); //��������


XC_API void WINAPI XPane_SetView(HELE hEle,HELE hView);
XC_API void WINAPI XPane_SetToolBar(HELE hEle,HELE hToolBar); //���ù�����
XC_API void WINAPI XPane_SetMenuBar(HELE hEle,HELE hMenuBar); //���ò˵���

//���ñ߿���
XC_API void WINAPI XPane_SetSpacing(HELE hEle,int left, int top, int right, int bottom);

XC_API void WINAPI XPane_SetFixedSize(HELE hEle,BOOL bFixedSize); //���ô���̶���С,���ΪFALSE�ǹ̶���С
XC_API void WINAPI XPane_SetTitle(HELE hEle,wchar_t *pTitle);

XC_API void WINAPI XPane_SetActivate(HELE hEle,BOOL bActivate); //�����
XC_API BOOL WINAPI XPane_IsActivate(HELE hEle); //�жϴ����Ƿ񼤻�,�������ڿ������Ч

XC_API void WINAPI XPane_SetCaptionHeight(HELE hEle,int height);//���ñ������߶�
XC_API int  WINAPI XPane_GetCaptionHeight(HELE hEle);//��ȡ�������߶�

XC_API HELE WINAPI XPane_GetButtonClose(HELE hEle); //��ȡ�رհ�ť
XC_API HELE WINAPI XPane_GetButtonLock(HELE hEle); //��ȡ������ť
XC_API HELE WINAPI XPane_GetButtonMenu(HELE hEle); //��ȡ�˵���ť


//���û���ô��񲼾�,���õĴ��񽫱���ܺ���,����ܵ���ʱ,����Խ��õĴ������
void Pane_EnableLayout(HELE hEle,BOOL bEnable);

//˽�з���:
void Pane_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);
void Pane_AdjustLayout(HELE hEle);
void Pane_AdjustLayout2(HELE hEle);

layoutCell_* Pane_GetCell(HELE hEle);

void Pane_Lock_group(HELE hEle);
void Pane_Lock_pane(HELE hEle);
int  Pane_Lock_scale(layoutPane_ *pPane,layoutCell_ *pCell); //�������

BOOL Pane_CellInFrame(layoutCell_ *pFrameCell,layoutCell_ *pCell); //��鵥Ԫ���Ƿ��ڿ�ܴ�����


//�ص�����
BOOL CALLBACK Pane_OnEleDraw(HELE hEle,HDRAW hDraw);
void CALLBACK Pane_OnEventDestroy(HELE hEle); 
BOOL CALLBACK Pane_OnEventMenuSelect(HELE hEle,HELE hEventEle,int id); 

BOOL CALLBACK Pane_OnEventShow(HELE hEle,HELE hEventEle,BOOL bShow); //Ԫ����ʾ�������¼�

BOOL CALLBACK Pane_EleLButtonDown(HELE hEle,UINT flags,POINT *pPt);//��갴��
BOOL CALLBACK Pane_EleLButtonUp(HELE hEle,UINT flags,POINT *pPt); //��굯��
BOOL CALLBACK Pane_EleMouseMove(HELE hEle,UINT flags,POINT *pPt);//����ƶ�
BOOL CALLBACK Pane_EventMouseLeave(HELE hEle,HELE hEventEle); 
BOOL CALLBACK Pane_OnSize(HELE hEle,HELE hEventEle); 

BOOL CALLBACK Pane_BtnClose_OnEleDraw(HELE hEle,HDRAW hDraw);//���ƹرհ�ť
BOOL CALLBACK Pane_BtnLock_OnEleDraw(HELE hEle,HDRAW hDraw); //�����Զ����ذ�ť
BOOL CALLBACK Pane_BtnMenu_OnEleDraw(HELE hEle,HDRAW hDraw); //���Ʋ˵���ť

BOOL CALLBACK Pane_Btn_Close(HELE hEle,HELE hEventEle);    //�رհ�ť
BOOL CALLBACK Pane_Btn_Lock(HELE hEle,HELE hEventEle);     //ͣ����ť
BOOL CALLBACK Pane_Btn_Menu(HELE hEle,HELE hEventEle);     //�˵���ť



/////////////////////////////////////////////////////////////////
//���񸡶�����

struct floatWindow_
{
	window_ window; //�̳�
	//------------------------
	layoutCell_  *pCell;  //���ֵ�Ԫ,��һ������Ϊ���,�������ڵĿͻ���
	HWINDOW      hFrameWnd; //��ܴ��ھ��
	POINT        downPt; //��갴��λ��

	BOOL        bLock;  //�Ƿ�������������ܴ�����
};



//API:
XC_API void WINAPI XFloatWnd_EnableLock(HWINDOW hWindow,BOOL bEnable); //���ùر���������,���ر��������ܺ�,�û��϶�������������������ܴ�����


//˽�з���:
HWINDOW FloatWnd_Create(int x,int y,int cx,int cy,wchar_t *pTitle,HWINDOW hFrameWnd,layoutCell_ *pCell);

void FloatWnd_DragWindow(HWINDOW hWindow,POINT *pPt); //�϶�����
BOOL FloatWnd_Init(HWINDOW hWindow,int x,int y,int cx,int cy,wchar_t *pTitle,HWINDOW hFrameWnd,layoutCell_ *pCell,int exType);

void FloatWnd_ExitDragWindow(); //�˳��϶�����

//�ص�����:
BOOL CALLBACK FloatWnd_OnWndDestroy(HWINDOW hWindow);
BOOL CALLBACK FloatWnd_OnWndSize(HWINDOW hWindow,UINT flags,SIZE *pSize); 
BOOL CALLBACK FloatWnd_OnWndClose(HWINDOW hWindow); 
BOOL CALLBACK FloatWnd_OnWndKillFocus(HWINDOW hWindow); 

LRESULT CALLBACK FloatWnd_LowLevelMouseProc(int nCode,WPARAM wParam,LPARAM lParam);


//��������,TabBar�л��¼�
BOOL CALLBACK FloatWnd_OnEventTabBarSelect(HELE hEle,HELE hEventEle,int index);
