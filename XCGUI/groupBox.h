/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct groupBox_
{
	ele_ ele; //�̳�
	//--------------------
	HSTRING hString;
};


//API:
XC_API HELE WINAPI XGBox_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent=NULL); //����
XC_API wchar_t* WINAPI XGBox_GetText(HELE hEle);
XC_API void WINAPI XGBox_SetText(HELE hEle,wchar_t *pText);

//˽�з���:
void GBox_Init(HELE hEle,int x,int y,int cx,int cy,wchar_t *pTitle,int eleType,HXCGUI hParent); //��ʼ��ע��


//�ص�����:
void CALLBACK GBox_OnDestroy(HELE hEle);  //����
BOOL CALLBACK GBox_OnDraw(HELE hEle,HDRAW hDraw);