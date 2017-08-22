/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup chooseColor ��ɫѡ��Ԫ��(ChooseColor)
/// @ingroup groupElements
/// @{

/// @brief ������ɫѡ��Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XCHColor_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	chooseColor_ *pObj=(chooseColor_*)malloc(sizeof(chooseColor_));
	memset(pObj,0,sizeof(chooseColor_));
	CHColor_Init((HELE)pObj,x,y,cx,cy,XC_CHOOSECOLOR,hParent);
	return (HELE)pObj;
}

void CHColor_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Edit_Init(hEle,x,y,cx,cy,eleType,hParent);

	AddTypeDebug(hEle,XC_CHOOSECOLOR);
	
	chooseColor_ *pObj=(chooseColor_*)hEle;
	//SCROLLVIEW(hEle)->left=22;

	pObj->color=RGB(255,0,0);
	wchar_t color16[10]={0};
	color16[0]='#';
	wsprintf(color16+1,L"%02X",GetRValue(pObj->color));
	wsprintf(color16+3,L"%02X",GetGValue(pObj->color));
	wsprintf(color16+5,L"%02X",GetBValue(pObj->color));
	XEdit_SetText(hEle,color16);

	XSView_SetSpacing(hEle,cy,2,2,2);

	XEle_RegisterMessage(hEle,XM_PAINT,CHColor_OnDraw);
	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,CHColor_OnLButtonDown);
	XEle_RegisterEvent(hEle,XE_KILLFOCUS,CHColor_OnEventKillFocus);
	XEle_RegisterEvent(hEle,XE_SIZE,CHColor_OnEventSize);
}

BOOL CALLBACK CHColor_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	XSView_SetSpacing(hEle,rect.bottom-rect.top,2,2,2);

	return FALSE;
}

/// @brief ��ɫѡ��༭��Ԫ��,��ȡ��ɫֵ.
/// @param hEle Ԫ�ؾ��.
/// @return ��ȡ��RGB��ɫ.
COLORREF WINAPI XCHColor_GetColor(HELE hEle) //��ȡ��ɫRGBֵ
{
	IsChooseColorDebug(hEle,__FUNCTION__);
	return ((chooseColor_*)hEle)->color;
}

/// @brief ��ɫѡ��Ԫ�ر༭��,������ɫ.
/// @param hEle Ԫ�ؾ��.
/// @param color RGB��ɫֵ.
void WINAPI XCHColor_SetColor(HELE hEle,COLORREF color) //������ɫ
{
	IsChooseColorDebug(hEle,__FUNCTION__);
	((chooseColor_*)hEle)->color=color;
	wchar_t  buf[8]={0};
	buf[0]='#';
	wsprintf(buf+1,L"%02X",GetRValue(color));
	wsprintf(buf+3,L"%02X",GetGValue(color));
	wsprintf(buf+5,L"%02X",GetBValue(color));

	XEdit_SetText(hEle,buf);
}

BOOL CALLBACK CHColor_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(EDIT(hEle)->bMouseStay || XEle_IsFocus(hEle))
	{
		if(EDIT(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw,EDIT(hEle)->hImage_stay,&rect);
		}
	}else
	{
		if(SCROLLVIEW(hEle)->hImage_bk)
		{
			XDraw_HImageSuper_(hDraw,SCROLLVIEW(hEle)->hImage_bk,&rect);
		}
	}

	int size=rect.bottom-rect.top;
	RECT rc={2,2,size-2,size-2};

	if(((ele_*)hEle)->bBorder)
	{
		COLORREF color=((ele_*)hEle)->borderColor;
		if(XEle_IsFocus(hEle) || EDIT(hEle)->bMouseStay)
		{
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(GetRValue(color)+80,GetGValue(color)+80,GetBValue(color)+80));
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
			if(SCROLLVIEW(hEle)->left>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,0,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->top>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,rect.right,0);
			}
			if(SCROLLVIEW(hEle)->right>0)
			{
				XDraw_MoveToEx_(hDraw,rect.right-1,0,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->bottom>0)
			{
				XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
				XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
			}
			//DeleteObject(hPen);

			HPEN hPen2=XDraw_CreatePen_(hDraw,PS_SOLID,1,color);
			XDraw_SelectObject_(hDraw,hPen2);
			if(SCROLLVIEW(hEle)->left>1)
			{
				XDraw_MoveToEx_(hDraw,1,1,NULL);
				XDraw_LineTo_(hDraw,1,rect.bottom-1);
				rc.left++;
			}
			if(SCROLLVIEW(hEle)->top>1)
			{
				XDraw_MoveToEx_(hDraw,1,1,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,1);
				rc.top++;
			}
			if(SCROLLVIEW(hEle)->right>1)
			{
				XDraw_MoveToEx_(hDraw,rect.right-2,1,NULL);
				XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);
			}
			if(SCROLLVIEW(hEle)->bottom>1)
			{
				XDraw_MoveToEx_(hDraw,1,rect.bottom-2,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom-2);
				rc.bottom--;
			}

			//SelectObject(hDraw,hOld);
			//DeleteObject(hPen2);
		}else
		{
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,color);
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
			if(SCROLLVIEW(hEle)->left>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,0,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->top>0)
			{
				XDraw_MoveToEx_(hDraw,0,0,NULL);
				XDraw_LineTo_(hDraw,rect.right,0);
			}
			if(SCROLLVIEW(hEle)->right>0)
			{
				XDraw_MoveToEx_(hDraw,rect.right-1,0,NULL);
				XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
			}
			if(SCROLLVIEW(hEle)->bottom>0)
			{
				XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
				XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
			}
			//SelectObject(hDraw,hOld);
			//DeleteObject(hPen);
		}
	}
	XDraw_FillSolidRect_(hDraw,&rc,((chooseColor_*)hEle)->color);

	HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(128,128,128));
	HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
	XDraw_MoveToEx_(hDraw,size-1,2,NULL);
	XDraw_LineTo_(hDraw,size-1,size-2);
	//SelectObject(hDraw,hOld);
	//DeleteObject(hPen);

	return TRUE;
}

BOOL CALLBACK CHColor_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	int size=((ele_*)(hEle))->rect.bottom-((ele_*)(hEle))->rect.top-4;

	if(pPt->x<size)
	{
		CHOOSECOLOR cc;                 // common dialog box structure 
		static COLORREF acrCustClr[16]; // array of custom colors 
		// Initialize CHOOSECOLOR 
		ZeroMemory(&cc, sizeof(cc));
		cc.lStructSize = sizeof(cc);
		cc.hwndOwner = XEle_GetHWnd(hEle);
		cc.lpCustColors = (LPDWORD) acrCustClr;
		cc.rgbResult =((chooseColor_*)hEle)->color;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;

		if (ChooseColor(&cc)==TRUE)
		{
			((chooseColor_*)hEle)->color=cc.rgbResult;
			wchar_t  buf[8]={0};
			buf[0]='#';
			wsprintf(buf+1,L"%02X",GetRValue(cc.rgbResult));
			wsprintf(buf+3,L"%02X",GetGValue(cc.rgbResult));
			wsprintf(buf+5,L"%02X",GetBValue(cc.rgbResult));

			XEdit_SetText(hEle,buf);
		}
	}
	return FALSE;
}

BOOL CALLBACK CHColor_OnEventKillFocus(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	chooseColor_ *pObj=(chooseColor_*)hEle;
	int len=XEdit_GetTextLength(hEle);
	wchar_t text[8]={0};
	XEdit_GetText(hEle,text,7);

	if(('#'!=text[0]) || (7!=len))
	{
		wchar_t  buf[10]={0};
		buf[0]='#';
		wsprintf(buf+1,L"%02X",GetRValue(pObj->color));
		wsprintf(buf+3,L"%02X",GetGValue(pObj->color));
		wsprintf(buf+5,L"%02X",GetBValue(pObj->color));

		XEdit_SetText(hEle,buf);
		return FALSE;
	}
	if(isxdigit(text[1]) && isxdigit(text[2]) && isxdigit(text[3]) && isxdigit(text[4]) && isxdigit(text[5]) && isxdigit(text[6]) )
	{
		wchar_t text2[7]={0};
		text2[0]=text[5];
		text2[1]=text[6];
		text2[2]=text[3];
		text2[3]=text[4];
		text2[4]=text[1];
		text2[5]=text[2];
		text2[6]=0;
		((chooseColor_*)hEle)->color=XC_HexToDec(text2);
	}else
	{
		wchar_t  buf[10]={0};

		wsprintf(buf,L"%02X",GetRValue(pObj->color));
		wsprintf(buf+2,L"%02X",GetGValue(pObj->color));
		wsprintf(buf+4,L"%02X",GetBValue(pObj->color));

		XEdit_SetText(hEle,buf);
	}
	return FALSE;
}

///@}
