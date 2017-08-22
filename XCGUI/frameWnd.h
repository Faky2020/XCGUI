/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once


//��ܴ���
struct frameWnd_
{
	window_ window;
	//---------------------------------------
	layoutCell_  *pCell;  //���ֵ�Ԫ,��һ������Ϊ���,�������ڵĿͻ���

	HWINDOW hFloatWnd; //��ǰ�϶��ĸ�������
	HELE    hPaneActivate;     //��ǰ����Ĵ���

	//ͣ����ʾ
	HWINDOW hDockPane;     //ͣ����ʾ ʮ��
	HWINDOW hDockLeft;     //ͣ����ʾ ���ڱ߿� left
	HWINDOW hDockTop;      //ͣ����ʾ ���ڱ߿� top
	HWINDOW hDockRight;    //ͣ����ʾ ���ڱ߿� right
	HWINDOW hDockBottom;   //ͣ����ʾ ���ڱ߿� bottom

	HWINDOW hDockPreview;  //ͣ��Ԥ��
	align_type_  dockAlign; //Ԥ�����ڷ��� left,top,right,bottom

	//������
	layoutCell_  *pCell_stay;  //��ǰ�����������ڴ���
	int   dockType;    //ͣ������, 1���,2�ϲ�,3�߿�

	//ͣ����ͷ
	HELE  hPierLeft;   //left
	HELE  hPierTop;    //top
	HELE  hPierRight;  //right
	HELE  hPierBottom; //bottom

	HELE hPaneExpand;//��ǰչ���Ĵ���

	//���Ա���϶�
	BOOL  bDown_TabBar; //����TabBar��ť��
	POINT ptDown_TabBar; 
};


/// @defgroup frameWindow  ��ܴ���
/// @ingroup groupWindows
/// ��ܴ��ڽӿ��б�


//����API:
XC_API HWINDOW WINAPI XFrameWnd_CreateWindow(int x,int y,int cx,int cy,wchar_t *pTitle,HWND hWndParent=NULL,int XCStyle=XC_SY_DEFAULT);

//���Ӵ��񵽿�ܴ���
XC_API BOOL WINAPI XFrameWnd_AddPane(HWINDOW hWindow,HELE hPaneDest,HELE hPaneNew,align_type_ align=align_any,int scale=50);


XC_API HPANE_GROUP WINAPI XFrameWnd_MergePane(HWINDOW hWindow,HELE hPaneDest,HELE hPaneNew,int proportion=50);
XC_API BOOL WINAPI XFrameWnd_MergePaneToGroup(HWINDOW hWindow,HPANE_GROUP hGroup,HELE hPaneNew,int proportion=50); //����ϲ�����


XC_API void WINAPI XFrameWnd_AdjustLayout(HWINDOW hWindow,BOOL bFixedSize=FALSE);
XC_API void WINAPI XFrameWnd_GetLayoutAreaRect(HWINDOW hWindow,out_ RECT *pRect); //��ȡ�ͻ���������������
XC_API HELE WINAPI XFrameWnd_GetActivatePane(HWINDOW hWindow);//��ȡ��ܴ����ڼ���Ĵ���,��������������

BOOL FrameWnd_RemoveCell(HWINDOW hWindow,layoutCell_ *pCell); //�Ƴ���Ԫ��,ֻ�ǴӲ��ֹ������Ƴ�
BOOL FrameWnd_RemoveCell_Pane(HWINDOW hWindow,layoutCell_ *pCell);
BOOL FrameWnd_RemoveCell_Group(HWINDOW hWindow,layoutCell_ *pCell);
BOOL FrameWnd_RemoveCell_GroupMenber(HWINDOW hWindow,layoutCell_ *pCell);

void FrameWnd_DragPane(HWINDOW hWindow,layoutCell_ *pCell,POINT *pPtDown); //�϶�����
void FrameWnd_DragGroup(HWINDOW hWindow,layoutCell_ *pCell,POINT *pPtDown); //�϶�������
void FrameWnd_FloatPane(HWINDOW hWindow,layoutCell_ *pCell); //��������
void FrameWnd_FloatGroup(HWINDOW hWindow,layoutCell_ *pGroupCell); //����������


//˽�з���:
BOOL FrameWnd_Init(HWINDOW hWindow,DWORD dwExStyle, wchar_t* lpClassName, wchar_t* lpWindowName,DWORD dwStyle,int x,int y,int cx,int cy,HWND hWndParent,int XCStyle,int exType);

//���
BOOL FrameWnd_AddT(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align=align_any,int scale=50);
BOOL FrameWnd_Add_Pane(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);
BOOL FrameWnd_Add_GroupToPane(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);
BOOL FrameWnd_Add_PaneToGroup(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);

//�ϲ�
BOOL FrameWnd_Add_MergeT(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align=align_any,int scale=50);
HPANE_GROUP FrameWnd_Add_Merge_Pane2(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);
BOOL FrameWnd_Add_Merge_Group2(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);
BOOL FrameWnd_Add_Merge_PaneToGroup(HWINDOW hWindow,layoutCell_ *pCellGroup,layoutCell_ *pCellPane/*,align_type_ align,int scale*/);
BOOL FrameWnd_Add_Merge_GroupToPane(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);

BOOL FrameWnd_AddPaneGroup(HWINDOW hWindow,layoutCell_ *pCellDest,layoutCell_ *pCellNew,align_type_ align,int scale);


void FrameWnd_AddPier(HWINDOW hWindow,layoutCell_ *pCell); //������ӵ���ͷ
void FrameWnd_AddPierGroup(HWINDOW hWindow,layoutCell_ *pGroupCell); //��������ӵ���ͷ
void FrameWnd_RemovePier(HWINDOW hWindow,HELE hPane); //����ͷ�Ƴ�����
void FrameWnd_RemovePierGroup(HWINDOW hWindow,HELE hPane); //����ͷ�Ƴ�������

BOOL FrameWnd_PierShrink(HWINDOW hWindow);  //����չ���Ĵ���

//����ͣ����ʾ��ͣ��λ��Ԥ������,��ʱ����
void FrameWnd_CreateTempWindow(HWINDOW hWindow);


//�ص�����:
BOOL CALLBACK FrameWnd_OnSize(HWINDOW hWindow,UINT type,SIZE *pSize);  //ON SIZE ���ڴ�С�ı�

BOOL CALLBACK FrameWnd_OnWndDestroy(HWINDOW hWindow);  
void FrameWnd_DestroyCell(layoutCell_ *pCell);
BOOL CALLBACK FrameWnd_OnLButtonDown(HWINDOW hWindow,UINT flags,POINT *pPt);

//TabBar�¼�,�϶��ӵ�Ԫ��
BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK FrameWnd_TabBar_Btn_OnEventMouseLeave(HELE hEle,HELE hEventEle);

BOOL FrameWnd_PierPopupPane(HWINDOW hWindow,HELE hPane); //��������,������ͷ��ʱ

//���������ƶ�
void FrameWnd_OnFloatWnd_Move(HWINDOW hWindow,POINT *pPt); //�������λ��,�жϸ����������ĸ����ָ���
BOOL FrameWnd_OnFloatWnd_Move2(HWINDOW hWindow,layoutCell_ *pCell,POINT *pPt,POINT *pPtWindow); //������Ԫ��

//����ڿ�ܴ�����
void FrameWnd_OnFloatWnd_Move_inFrame(HWINDOW hWindow,POINT *pPt);
BOOL FrameWnd_OnFloatWnd_CheckInDockPrompt(HWINDOW hWindow,POINT *pPt); //����Ƿ���ͣ����ʾ��
BOOL FrameWnd_OnFloatWnd_CeckInDockPrompt_border(HWINDOW hWindow,POINT *pPt); //�ж��Ƿ��ڿ�ܴ��ڱ߿�ͣ����ʾ��
void FrameWnd_OnFloatWnd_Exit(HWINDOW hWindow);

//������������������,pPt��Ļ����
//��������ƶ���������
void FrameWnd_OnFloatWnd_LButtonUp(HWINDOW hWindow);
void FrameWnd_OnFloatWnd_AddPane(HWINDOW hWindow,layoutCell_ *pCellNew);
void FrameWnd_OnFloatWnd_AddGroup(HWINDOW hWindow,layoutCell_ *pCellNew);

//���ƴ���ͣ����ʾ,ʮ��,�����ڲ�ͣ��
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockPane(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockLeft(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockTop(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockRight(HWINDOW hWindow,HDRAW hDraw);
BOOL CALLBACK FrameWnd_OnWndDrawWindow_dockBottom(HWINDOW hWindow,HDRAW hDraw);

