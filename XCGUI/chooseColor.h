/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/

#pragma once

//��ɫѡ��Ԫ��

struct chooseColor_
{
	edit_  edit; //�̳�
	//---------------------
	COLORREF color; //��ǰ��ɫ
};


//API:
XC_API HELE WINAPI XCHColor_Create(int x, int y, int cx, int cy,HXCGUI hParent=NULL);

XC_API COLORREF WINAPI XCHColor_GetColor(HELE hEle); //��ȡ��ɫRGBֵ

XC_API void WINAPI XCHColor_SetColor(HELE hEle,COLORREF color);//������ɫ

//˽�з���:
void CHColor_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent);
BOOL CALLBACK CHColor_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK CHColor_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt);
BOOL CALLBACK CHColor_OnEventKillFocus(HELE hEle,HELE hEventEle);
BOOL CALLBACK CHColor_OnEventSize(HELE hEle,HELE hEventEle); 

