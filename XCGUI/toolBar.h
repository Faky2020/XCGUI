/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once



struct  toolBarBtn_
{
	button_  button;
	//--------------------------
	//int      style;       //��ʽ

	//СͼƬ:
//	HIMAGE   hImage_small;        //ͼ��
//	HIMAGE   hImage_small_disable; //����״̬ͼ��
};

//�����ť�����б���ͼƬ,��ôҪ���Ʊ���ͼƬ

//��������ť
XC_API HELE WINAPI XToolBarBtn_Create(int cx,int cy,wchar_t *pTitle);
XC_API void WINAPI XToolBarBtn_Adjust(HELE hEle);  //���������ʴ�С, ����ӵ���������֮��ſɵ���,��Ϊ��Ҫ֪����������С�����������


//˽�з���
void  ToolBarBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);


//�ص�����:
BOOL CALLBACK ToolBarBtn_OnDraw(HELE hEle,HDRAW hDraw);
void CALLBACK ToolBarBtn_OnEventDestroy(HELE hEle);


//////////////////////////////////////////////////////////////////////////////////

#define  TOOLBAR_BUTTONS_WIDTH   40 //������ť������
#define  TOOLBAR_BUTTONS_HEIGHT  20 //������ť����߶�

struct toolBar_
{
	ele_  ele; //�̳�
	//--------------------
	HARRAY  hArrayEle;  //Ԫ���б�

	int    indent;      //��ǰ�������  �������� +1, ����-1

	HELE  hLeftButton;  //��ť
	HELE  hRightButton; //�Ұ�ť
	BOOL  bAdjust;

	HIMAGE  hImage_bk;  //����ͼƬ
};

//API:
XC_API HELE WINAPI XToolBar_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

XC_API int WINAPI XToolBar_InsertEle(HELE hEle,HELE hNewEle,int index=-1); //���Ԫ�ص�������, -1���뵽ĩβ
XC_API int WINAPI XToolBar_InsertSeparator(HELE hEle,int index=-1); //��ӷָ���, -1���뵽ĩβ

XC_API HELE WINAPI XToolBar_GetHEle(HELE hEle,int index);  //��ȡ��������Ԫ�ؾ��
XC_API HELE WINAPI XToolBar_GetButtonLeft(HELE hEle);   //��ȡ�������������ťButton
XC_API HELE WINAPI XToolBar_GetButtonRight(HELE hEle);  //��ȡ�������ҹ�����ťButton

XC_API void WINAPI XToolBar_DeleteEle(HELE hEle,int index); //�Ƴ���������Ԫ�ز�����
XC_API void WINAPI XToolBar_Adjust(HELE hEle);          //��������


//��ͼ:
XC_API void WINAPI XToolBar_SetImage(HELE hEle,HIMAGE hImage);

//˽�з���:
void ToolBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent); //��ʼ��ע��


//�ص�����:
BOOL CALLBACK ToolBar_OnDraw(HELE hEle,HDRAW hDraw);
void CALLBACK ToolBar_OnDestroy(HELE hEle);  //����
BOOL CALLBACK ToolBar_OnEventBtnClickLeft(HELE hEle,HELE hEventEle);
BOOL CALLBACK ToolBar_OnEventBtnClickRight(HELE hEle,HELE hEventEle);
BOOL CALLBACK ToolBar_OnEventSize(HELE hEle,HELE hEventEle); 

//�������ϰ�ť����
BOOL CALLBACK ToolBar_OnDrawScrollButtonLeft(HELE hEle,HDRAW hDraw);
BOOL CALLBACK ToolBar_OnDrawScrollButtonRight(HELE hEle,HDRAW hDraw);

