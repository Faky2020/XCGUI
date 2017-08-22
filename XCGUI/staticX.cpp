/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


//API:

/// @defgroup static ��̬�ı�Ԫ��(Static)
/// @ingroup groupElements
/// @{

/// @brief ������̬�ı�Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param pTitle �ı�����.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XStatic_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent)
{
	static_ *pObj=(static_*)malloc(sizeof(static_));
	memset(pObj,0,sizeof(static_));
	Static_Init((HELE)pObj,x,y,cx,cy,XC_STATIC,pTitle,hParent);
	return (HELE)pObj;
}

//˽�з���:
void Static_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_STATIC);
	
	STATIC(hEle)->hString=XStr_Create();
	if(pTitle)
	{
		XStr_SetString(STATIC(hEle)->hString,pTitle);
	}
	STATIC(hEle)->textFlag=0;
	((ele_*)hEle)->bBorder=FALSE;
	XEle_RegisterMessage(hEle,XM_PAINT,Static_OnDraw);
	XEle_RegisterEvent(hEle,XE_DESTROY,Static_OnDestroy);
	XEle_RegisterEvent(hEle,XE_SETFOCUS,Static_OnEventSetFocus);
	XEle_RegisterEvent(hEle,XE_KILLFOCUS,Static_OnEventKillFocus);
}

void CALLBACK Static_OnDestroy(HELE hEle) //����
{
	if(STATIC(hEle)->hString)
		XStr_Destroy(STATIC(hEle)->hString);
}

BOOL CALLBACK Static_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(STATIC(hEle)->hString)
	{
		wchar_t *pText=XStr_GetBuffer(STATIC(hEle)->hString);
		if(pText)
		{
			RECT rcText=rect;
			rcText.left+=2;
			rcText.top+=2;
			rcText.right-=2;
			rcText.bottom-=2;
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(STATIC(hEle)->hString),&rcText,STATIC(hEle)->textFlag);
		}
	}

	if(((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw,&rect,hBrush);
		//DeleteObject(hBrush);
	}

	if(((ele_*)hEle)->bDrawFocus &&  hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		RECT rcFocus={2,2,rect.right-2,rect.bottom-2};
		XDraw_FocusRect_(hDraw,&rcFocus);
	}

	return TRUE;
}

/// @brief �����ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @param pText  �ı�����.
void WINAPI XStatic_SetText(HELE hEle,wchar_t *pText)
{
	IsStaticDebug(hEle,__FUNCTION__);
	XStr_SetString(STATIC(hEle)->hString,pText);
}

/// @brief ��ȡ�ı�����.
/// @param hEle  Ԫ�ؾ��.
/// @return  �ı�����.
wchar_t* WINAPI XStatic_GetText(HELE hEle)
{
	IsStaticDebug(hEle,__FUNCTION__);
	if(STATIC(hEle)->hString)
		return XStr_GetBuffer(STATIC(hEle)->hString);
	else
		return NULL;
}

/// @brief �����ı�����,����Ԫ�ص����ʴ�С.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XStatic_AdjustSize(HELE hEle)  //�����ı�����,����Ԫ�ش�С
{
	IsStaticDebug(hEle,__FUNCTION__);
	static_ *pObject=(static_*)hEle;
	wchar_t *pText=XStr_GetBuffer(pObject->hString);
	if(NULL==pText) return ;

	RECT rc={0,0,20,20};
	HDC hdc=GetDC(NULL);
	HGDIOBJ hOld=SelectObject(hdc,XFont_GetHFONT(((ele_*)hEle)->hFontX));
	if(0==DrawText(hdc,pText,XStr_GetLength(pObject->hString),&rc,pObject->textFlag | DT_CALCRECT))
	{
		SelectObject(hdc,hOld);
		ReleaseDC(NULL,hdc);
		return ;
	}
	SelectObject(hdc,hOld);
	ReleaseDC(NULL,hdc);

	rc.left+=((ele_*)hEle)->rect.left;
	rc.top+=((ele_*)hEle)->rect.top;
	rc.right+=((ele_*)hEle)->rect.left;
	rc.bottom+=((ele_*)hEle)->rect.top;
	rc.right+=4;
	rc.bottom+=4;
	XEle_SetRect(hEle,&rc);
}

/// @brief �����ı�����.
/// @param hEle Ԫ�ؾ��.
/// @param flag ��ʶ,��μ�MSDN  DrawText().
void WINAPI XStatic_SetTextAlign(HELE hEle,int flag) //�����ı�����
{
	IsStaticDebug(hEle,__FUNCTION__);
	STATIC(hEle)->textFlag=flag;
}

///@}

BOOL CALLBACK Static_OnEventSetFocus(HELE hEle,HELE hEventEle) //��ý���
{
	if(hEle==hEventEle)
	{
		if(((ele_*)hEle)->bDrawFocus)
			XEle_RedrawEle(hEle);
	}
	return FALSE;
}

BOOL CALLBACK Static_OnEventKillFocus(HELE hEle,HELE hEventEle) //ʧȥ����
{
	if(hEle==hEventEle)
	{
		if(((ele_*)hEle)->bDrawFocus)
			XEle_RedrawEle(hEle);
	}
	return FALSE;
}
