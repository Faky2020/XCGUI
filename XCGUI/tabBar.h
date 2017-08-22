/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct tabBar_item_
{
	HELE   hButton; //button_*
	HELE   hPage;

	int    width; //�ַ�����ʾ���,����
};

//tab��Ԫ��
struct tabBar_
{
	ele_ ele; //����
	//--------------------
	HARRAY hArrayList;  //��ǩ�б� tabBar_item_*
	BOOL   bAdjust;     //TRUE:��Ҫ����
	int    indent;      //��ǰ�������  ��������1��TAB +1, ����-1
	int    height;      //��ǩ�߶�
	int    widthBtn;    //������ť������
	int    spacing;     //��ǩ��� 0û�м��
	BOOL   bTile;       //ƽ�̱�ǩ,ÿ����ǩ��ʾ��ͬ��С

	tabBar_item_  *pSelectItem; //��ǰѡ���ǩ
	HELE  hBtnUp;    //�ϰ�ť
	HELE  hBtnDown;  //�°�ť

	align_type_ align;  //��ʽ,��������
};



//API:
XC_API HELE WINAPI XTabBar_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);
XC_API int WINAPI XTabBar_AddLabel(HELE hEle,wchar_t *pName,HELE hPage=NULL); //���һ����ǩ
XC_API int WINAPI XTabBar_InsertLabel(HELE hEle,int index,wchar_t *pName,HELE hPage=NULL);

XC_API void WINAPI XTabBar_DeleteLabel(HELE hEle,int index,BOOL deletePage=FALSE);  //ɾ��
XC_API void WINAPI XTabBar_DeleteLabelAll(HELE hEle,BOOL deletePage=FALSE);  //ɾ������TAB

XC_API HELE WINAPI XTabBar_GetLabel(HELE hEle,int index);//��ȡ��ǩ��ťButton
XC_API HELE WINAPI XTabBar_GetLabelPage(HELE hEle,int index); //��ȡ��ǩ��Ӧ��ҳ
XC_API int  WINAPI XTabBar_GetPageIndex(HELE hEle,HELE hPage); //������ҳ��Ӧ��ǩ����
XC_API int  WINAPI XTabBar_GetSelect(HELE hEle);  //��ȡѡ��ı�ǩ
XC_API int  WINAPI XTabBar_GetLabelSpacing(HELE hEle); //��ȡ��ǩ���, 0û�м��
XC_API int  WINAPI XTabBar_GetLabelCount(HELE hEle); //��ȡ��ǩ������

XC_API void WINAPI XTabBar_SetLabelSpacing(HELE hEle,int spacing);//���ñ�ǩ���, 0û�м��
XC_API BOOL WINAPI XTabBar_SetBindEle(HELE hEle,int index,HELE hPage); //����ͼԪ�ص���ǩ
XC_API void WINAPI XTabBar_SetSelect(HELE hEle,int index,BOOL reDraw=TRUE);   //����ѡ���ǩ
XC_API void WINAPI XTabBar_SetAlign(HELE hEle,align_type_ align);

XC_API void WINAPI XTabBar_SetUp(HELE hEle);    //�����
XC_API void WINAPI XTabBar_SetDown(HELE hEle);  //�ҹ���

XC_API void WINAPI XTabBar_EnableTile(HELE hEle,BOOL bTile);  //ƽ�̱�ǩ,ÿ����ǩ��ʾ��ͬ��С


//˽�з���:
void TabBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
void TabBar_Adjust(HELE hEle);
tabBar_item_* TabBar_AddLabel(HELE hEle,wchar_t *pName,HELE hPage);


//�ص�����:
BOOL CALLBACK TabBar_OnDraw(HELE hEle,HDRAW hDraw);
void CALLBACK TabBar_OnDestroy(HELE hEle); //����
BOOL CALLBACK TabBar_OnEventSize(HELE hEle,HELE hEventEle);

BOOL CALLBACK TabBar_OnDraw_Up(HELE hEle,HDRAW hDraw);   //�����ϰ�ť
BOOL CALLBACK TabBar_OnDraw_Down(HELE hEle,HDRAW hDraw); //�����°�ť
BOOL CALLBACK TabBar_OnEventBtnClick_Up(HELE hEle,HELE hEventEle); //��ť�¼�
BOOL CALLBACK TabBar_OnEventBtnClick_Down(HELE hEle,HELE hEventEle); //��ť�¼�

BOOL CALLBACK TabBar_Btn_OnDrawLabel(HELE hEle,HDRAW hDraw);
BOOL TabBar_Btn_OnDrawLabel_Top(HELE hEle,HDRAW hDraw);
BOOL TabBar_Btn_OnDrawLabel_Bottom(HELE hEle,HDRAW hDraw);

BOOL CALLBACK TabBar_OnEventBtnClick(HELE hEle,HELE hEventEle); //��ǩѡ��
