/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

struct outlook_Item_
{
	HELE  hButton; //��ť���
	HELE  hView;   //�󶨵���ͼ
};

struct outlook_
{
	ele_  ele;
	//--------------------------
	HARRAY  hArrayItem;    //outlook_Item_*
	int     index;         //��ǰ��ʾ����ͼ����
	int     buttonHeight;  //��ͼչ����ť�߶�
	BOOL    bAdjust;

};

//API:
XC_API HELE WINAPI XOutlook_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

XC_API void WINAPI XOutlook_AddView(HELE hEle,HELE hView,wchar_t *pTitle);

XC_API void WINAPI XOutlook_Adjust(HELE hEle);

XC_API void WINAPI XOutlook_Expand(HELE hEle,int index);  //չ��ָ����

XC_API int WINAPI XOutlook_GetExpand(HELE hEle); //��ȡ��ǰչ����������


//˽�з���:
void Outlook_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);

//�ص�����
void CALLBACK Outlook_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Outlook_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Outlook_OnDrawButton(HELE hEle,HDRAW hDraw);

BOOL CALLBACK Outlook_OnEventBtnClick(HELE hEle,HELE hEventEle);
BOOL CALLBACK Outlook_OnEventSize(HELE hEle,HELE hEventEle);