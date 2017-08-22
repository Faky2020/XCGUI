/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


//��̬�����ı�

struct textLink_
{
	button_  button; //�̳�
	//-------------------------------
	BOOL   bUnderline_leave; //����뿪 �»���
	BOOL   bUnderline_stay;  //���ͣ�� �»���
	COLORREF colorStay;//���ͣ��ʱ�ı���ɫ
};


//API:
XC_API HELE WINAPI XTextLink_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);


XC_API void WINAPI XTextLink_SetStayColor(HELE hEle,COLORREF color); //�������ͣ��ʱ�ı���ɫ
XC_API COLORREF WINAPI XTextLink_GetStayColor(HELE hEle);  //��ȡ���ͣ��ʱ�ı���ɫ
XC_API void WINAPI XTextLink_AdjustSize(HELE hEle);  //�����ı�����,����Ԫ�ش�С
XC_API void WINAPI XTextLink_ShowUnderline(HELE hEle,BOOL bLeave,BOOL bStay);  //��ʾ�»���

//˽�з���:
void TextLink_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);

//�ص�����
BOOL CALLBACK TextLink_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK TextLink_OnMouseMove(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK TextLink_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK TextLink_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt);

