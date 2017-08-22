/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup picture ͼƬԪ��(Picture)
/// @ingroup groupElements
/// @{

/// @brief ����ͼƬԪ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XPic_Create(int x, int y, int cx, int cy,HXCGUI hParent)  //������ť
{
	picture_ *pObj=(picture_*)malloc(sizeof(picture_));
	memset(pObj,0,sizeof(picture_));
	Pic_Init((HELE)pObj,x,y,cx,cy,XC_PICTURE,hParent);
	return (HELE)pObj;
}

void Pic_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_PICTURE);

	((ele_*)hEle)->bBorder=FALSE;
	XEle_RegisterMessage(hEle,XM_PAINT,Pic_OnDraw);
	XEle_RegisterEvent(hEle,XE_DESTROY,Pic_OnDestroy);
}

/// @brief ����ͼƬ.
/// @param hEle Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XPic_SetImage(HELE hEle,HIMAGE hImage)
{
	IsPictureDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(PICTURE(hEle)->hImage_bk,hImage);
}

BOOL CALLBACK Pic_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(PICTURE(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,PICTURE(hEle)->hImage_bk,&rect);
	}

	if(((ele_*)hEle)->bBorder)
	{
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw,&rect,hBrush);
		//DeleteObject(hBrush);
	}
	return TRUE;
}

void CALLBACK Pic_OnDestroy(HELE hEle)  //����
{
	if(PICTURE(hEle)->hImage_bk) XImage_Destroy(PICTURE(hEle)->hImage_bk);
}

///@}
