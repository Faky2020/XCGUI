/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once

struct static_
{
	ele_  ele; //�̳�
	//--------------------
	HSTRING hString;
	int    textFlag; //�ı�����
};


//API:
XC_API HELE WINAPI XStatic_Create(int x, int y, int cx, int cy,wchar_t *pTitle=NULL,HXCGUI hParent=NULL);
XC_API void WINAPI XStatic_SetText(HELE hEle,wchar_t *pText);
XC_API wchar_t* WINAPI XStatic_GetText(HELE hEle);
XC_API void WINAPI XStatic_AdjustSize(HELE hEle);  //�����ı�����,����Ԫ�ش�С


/// @brief �����ı�����.
/// @param hEle Ԫ�ؾ��.
/// @param flag ��ʶ,��μ�MSDN  DrawText().
XC_API void WINAPI XStatic_SetTextAlign(HELE hEle,int flag); //�����ı�����


//˽�з���:
void Static_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent);


//�ص�����:
void CALLBACK Static_OnDestroy(HELE hEle);  //����
BOOL CALLBACK Static_OnDraw(HELE hEle,HDRAW hDraw);
BOOL CALLBACK Static_OnEventSetFocus(HELE hEle,HELE hEventEle); //��ý���
BOOL CALLBACK Static_OnEventKillFocus(HELE hEle,HELE hEventEle); //ʧȥ����
