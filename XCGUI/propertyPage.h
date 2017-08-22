/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct propertyPage_item_
{
	HELE   hButton; //button_*
	HELE   hPage;

	int    width; //�ַ�����ʾ���,����
	int    widthUser;  //�û�ָ�����,���Ϊ0,��ʹ��
};

struct propertyPage_
{
	ele_  ele; //�̳�
	//--------------------
	HARRAY hArrayList;  //��ǩ�б� propertyPage_item_*
	BOOL   bAdjust;     //TRUE:��Ҫ����
	BOOL   bScrollButton;//�Ƿ���ʾ������ť
	int    indent;      //��ǰ�������  ��������1��TAB +1, ����-1
	int    height;      //��ǩ�߶�
	int    widthBtn;    //������ť������
	int    spacing;     //��ǩ��� 0û�м��

	propertyPage_item_  *pSelectItem; //��ǰѡ���ǩ
	HELE  hBtnUp;    //�ϰ�ť
	HELE  hBtnDown;  //�°�ť
};

//����ҳԪ��

//API:
XC_API HELE WINAPI XPPage_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);
XC_API int WINAPI XPPage_AddLabel(HELE hEle,wchar_t *pName,HELE hPage=NULL); //���һ����ǩ
XC_API int WINAPI XPPage_InsertLabel(HELE hEle,int index,wchar_t *pName,HELE hPage=NULL);

XC_API void WINAPI XPPage_Adjust(HELE hEle);
XC_API BOOL WINAPI XPPage_SetBindEle(HELE hEle,int index,HELE hPage); //����ͼԪ�ص���ǩ
XC_API void WINAPI XPPage_SetLabelHeight(HELE hEle,int height);  //���ñ�ǩ�߶�
XC_API void WINAPI XPPage_SetLabelWidth(HELE hEle,int index,int width);   //���ñ�ǩ���
XC_API void WINAPI XPPage_SetSelect(HELE hEle,int index,BOOL reDraw=TRUE);   //����ѡ���ǩ
XC_API void WINAPI XPPage_SetLabelText(HELE hEle,int index,wchar_t *pText);  //���ñ�ǩ�ı�
XC_API void WINAPI XPPage_SetLabelSpacing(HELE hEle,int spacing);//���ñ�ǩ���, 0û�м��
XC_API void WINAPI XPPage_SetUp(HELE hEle);    //�����
XC_API void WINAPI XPPage_SetDown(HELE hEle);  //�ҹ���

XC_API int  WINAPI XPPage_GetSelect(HELE hEle);  //��ȡѡ��ı�ǩ
XC_API int  WINAPI XPPage_GetLabelHeight(HELE hEle);  //��ȡ��ǩ�߶�
XC_API int  WINAPI XPPage_GetLabelWidth(HELE hEle,int index);  //��ȡ��ǩ���
XC_API int  WINAPI XPPage_GetLabelCount(HELE hEle); //��ȡ��ǩ������

XC_API wchar_t * WINAPI XPPage_GetLabelText(HELE hEle,int index);  //��ȡ�ı�
XC_API HELE WINAPI XPPage_GetLabel(HELE hEle,int index);//��ȡ��ǩ��ťButton
XC_API HELE WINAPI XPPage_GetLabelPage(HELE hEle,int index);//��ȡ��ǩ��Ӧ��ҳ
XC_API int WINAPI XPPage_GetPageIndex(HELE hEle,HELE hPage); //������ҳ��Ӧ��ǩ����
XC_API int WINAPI XPPage_GetLabelIndex(HELE hEle,HELE hLabel); //��ȡ����ҳ��ǩ��ťԪ��λ������ֵ
XC_API int WINAPI XPPage_GetLabelSpacing(HELE hEle);//��ȡ��ǩ���, 0û�м��

XC_API void WINAPI XPPage_DeleteLabel(HELE hEle,int index,BOOL deletePage=FALSE);  //ɾ��
XC_API void WINAPI XPPage_DeleteLabelAll(HELE hEle,BOOL deletePage=FALSE);  //ɾ������TAB

XC_API void WINAPI XPPage_EnableScrollButton(HELE hEle,BOOL bEnable); //�Ƿ���ʾ������ť



//��ͼ:

//��ǩ��ͼ,ͨ����ȡ��ǩ��ť����
//��ǩͼ��

//˽�з���:
void PPage_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
propertyPage_item_* PPage_AddLabel(HELE hEle,wchar_t *pName,HELE hPage);


//�ص�����:
void CALLBACK PPage_OnDestroy(HELE hEle);  //����
BOOL CALLBACK PPage_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK PPage_OnEventSize(HELE hEle,HELE hEventEle);
//ONSIZE

BOOL CALLBACK PPage_OnDraw_Up(HELE hEle,HDRAW hDraw);   //�����ϰ�ť
BOOL CALLBACK PPage_OnDraw_Down(HELE hEle,HDRAW hDraw); //�����°�ť
BOOL CALLBACK PPage_OnEventBtnClick_Up(HELE hEle,HELE hEventEle); //��ť�¼�
BOOL CALLBACK PPage_OnEventBtnClick_Down(HELE hEle,HELE hEventEle); //��ť�¼�

//���Ʊ�ǩ
BOOL CALLBACK PPage_OnEventBtnClick(HELE hEle,HELE hEventEle); //��ǩѡ��



///����ҳ��ǩ��ť//////////////////////////////////////////////////////
HELE XPPageBtn_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);  //������ť
void PPageBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);
BOOL CALLBACK PPageBtn_OnDrawLabel(HELE hEle,HDRAW hDraw);