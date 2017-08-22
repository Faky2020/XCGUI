/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup toolBarButton ��������ť(ToolBarButton)
/// @ingroup groupElements
/// @{

/// @brief ������������ťԪ��.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param pTitle �ı�����
/// @return Ԫ�ؾ��.
HELE WINAPI XToolBarBtn_Create(int cx, int cy,wchar_t *pTitle)
{
	toolBarBtn_ *pObj=(toolBarBtn_*)malloc(sizeof(toolBarBtn_));
	memset(pObj,0,sizeof(toolBarBtn_));
	if(pObj)
	{
		ToolBarBtn_Init((HELE)pObj,0,0,cx,cy,XC_TOOLBAR_BUTTON,pTitle,NULL);
		return (HELE)pObj;
	}

	return NULL;
}

void  ToolBarBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent)
{
	Btn_Init(hEle,x,y,cx,cy,eleType,pTitle,hParent);

	AddTypeDebug(hEle,XC_TOOLBAR_BUTTON);

	XEle_EnableFocus(hEle,FALSE);
	XEle_SetBkTransparent(hEle,TRUE);
	XEle_RegisterMessage(hEle,XM_PAINT,ToolBarBtn_OnDraw);
	XEle_RegisterEvent(hEle,XE_DESTROY,ToolBarBtn_OnEventDestroy);
}


/// @brief ��������ťԪ��,����������ťԪ����ӵ���������֮��,���ø÷���XToolBarBtn_Adjust(),�����Զ����������ʴ�С.
///        ע��:����������ťԪ����ӵ���������֮��ſɵ���XToolBarBtn_Adjust().
/// @param hEle Ԫ�ؾ��.
void WINAPI XToolBarBtn_Adjust(HELE hEle)  //���������ʴ�С
{
	IsToolBarBtnDebug(hEle,__FUNCTION__);

	toolBarBtn_ *pObj=(toolBarBtn_*)hEle;
	HELE hParent=XEle_GetParentEle(hEle);

	if(NULL==hParent) return ;

	SIZE sizeIco={0};
	SIZE sizeText={0};

	wchar_t *pText=XBtn_GetText(hEle);
	if(pText)
	{
		SIZE size;  
		//�ַ�����
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc, XFont_GetHFONT(((ele_*)hEle)->hFontX) );
		GetTextExtentPoint32(hdc,pText,wcslen(pText),&size);
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);
		sizeText=size;
	}

	if(BUTTON(hEle)->hImage_icon)
	{
		sizeIco.cx=XImage_GetWidth(BUTTON(hEle)->hImage_icon); //pObj->hImage_small);
		sizeIco.cy=XImage_GetHeight(BUTTON(hEle)->hImage_icon);//pObj->hImage_small);
	}
	
	RECT rect;
	XEle_GetClientRect(hParent,&rect);

	if(XC_ICON_ALIGN_LEFT==BUTTON(hEle)->iconAlign || XC_ICON_ALIGN_RIGHT==BUTTON(hEle)->iconAlign)
	{
		rect.left=3;
		rect.right=3;
		if(sizeText.cx>0)
		{
			rect.right+=(sizeText.cx+3);
		}
		if(sizeIco.cx>0)
		{
			rect.right+=(sizeIco.cx+3);
		}

		rect.right+=3;
		rect.bottom-=4;
	}else if(XC_ICON_ALIGN_TOP==BUTTON(hEle)->iconAlign || XC_ICON_ALIGN_BOTTOM==BUTTON(hEle)->iconAlign)
	{
		if(sizeText.cx>sizeIco.cx)
		{
			rect.right=sizeText.cx+6;
		}else
		{
			rect.right=sizeIco.cx+6;
		}

		rect.bottom-=4;
	}else if(BUTTON(hEle)->hImage_icon)
	{
		rect.right=sizeIco.cx+6;
	}else if(pText)
	{
		rect.right=sizeText.cx+6;
	}
	XEle_SetRect(hEle,&rect);
}
///@}

BOOL CALLBACK ToolBarBtn_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	button_ *pObj=BUTTON(hEle);

	if(FALSE==((ele_*)hEle)->bEnable) //����
	{
		if(pObj->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw,pObj->hImage_disable,&rect);
		}
	}else if(BUTTON(hEle)->bCheck && pObj->hImage_check) //ѡ�� ��ͼƬ
	{
		if(pObj->hImage_check)
		{
			XDraw_HImageSuper_(hDraw,pObj->hImage_check,&rect);
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,3,3);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(180,180,180));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);
		}
	}else if(STATE_LEAVE==BUTTON(hEle)->state)
	{
		if(pObj->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw,pObj->hImage_leave,&rect);
		}
	}else if(STATE_STAY==BUTTON(hEle)->state)
	{
		if(pObj->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw,pObj->hImage_stay,&rect);
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,3,3);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(180,180,180));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
	//		DeleteObject(hBrush);
			XDraw_SelectClipRgn_(hDraw,NULL);
	//		DeleteObject(hRgn);
		}
	}else if(STATE_DOWN==BUTTON(hEle)->state || BUTTON(hEle)->bCheck)
	{
		if(pObj->hImage_down)
		{
			XDraw_HImageSuper_(hDraw,pObj->hImage_down,&rect);
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,3,3);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(180,180,180));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);
		}
	}

	Btn_DrawIconAndText(hEle,hDraw,rect);

	if(((ele_*)hEle)->bDrawFocus && hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		RECT rcFocus={2,2,rect.right-2,rect.bottom-2};
		XDraw_FocusRect_(hDraw,&rcFocus);
	}

	return TRUE;
}

void CALLBACK ToolBarBtn_OnEventDestroy(HELE hEle)
{

}

///////////////////////////////////////////////////////////////////////////////////
/// @defgroup toolBar ������(ToolBar)
/// @ingroup groupElements
/// @{

/// @brief ����������Ԫ��;���ָ���˸�Ϊ����,Ĭ�ϵ���XWnd_AddToolBar()����,����������ӵ����ڷǿͻ���.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XToolBar_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	toolBar_ *pObj=(toolBar_*)malloc(sizeof(toolBar_));
	if (pObj)
	{
		memset(pObj,0,sizeof(toolBar_));
		ToolBar_Init((HELE)pObj,x,y,cx,cy,XC_TOOLBAR,hParent);
	}
	return (HELE)pObj;
}

void ToolBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	if(hParent && XC_WINDOW==((object_*)hParent)->type)
	{
		Ele_Init(hEle,x,y,cx,cy,eleType,NULL);
		AddTypeDebug(hEle,XC_TOOLBAR);
		XWnd_AddToolBar((HWINDOW)hParent,hEle);
	}else
	{
		Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
		AddTypeDebug(hEle,XC_TOOLBAR);
	}

	TOOLBAR(hEle)->bAdjust=FALSE;
	TOOLBAR(hEle)->hArrayEle=XArray_Create();
	TOOLBAR(hEle)->indent=0;
	TOOLBAR(hEle)->hLeftButton=XBtn_Create(0,0,10,10,L"",hEle);
	TOOLBAR(hEle)->hRightButton=XBtn_Create(0,0,10,10,L"",hEle);
	XEle_EnableFocus(TOOLBAR(hEle)->hLeftButton,FALSE);
	XEle_EnableFocus(TOOLBAR(hEle)->hRightButton,FALSE);
	XEle_ShowEle(TOOLBAR(hEle)->hLeftButton,FALSE);
	XEle_ShowEle(TOOLBAR(hEle)->hRightButton,FALSE);
	XEle_SetBkTransparent(TOOLBAR(hEle)->hLeftButton,TRUE);
	XEle_SetBkTransparent(TOOLBAR(hEle)->hRightButton,TRUE);
	XEle_RegisterMessage(hEle,XM_PAINT,ToolBar_OnDraw);
	XEle_RegisterEvent(hEle,XE_DESTROY,ToolBar_OnDestroy);
	XEle_RegisterEvent(hEle,XE_SIZE,ToolBar_OnEventSize);

	XEle_RegisterEvent(TOOLBAR(hEle)->hLeftButton,XE_BNCLICK,ToolBar_OnEventBtnClickLeft);
	XEle_RegisterEvent(TOOLBAR(hEle)->hRightButton,XE_BNCLICK,ToolBar_OnEventBtnClickRight);

	XEle_RegisterMessage(TOOLBAR(hEle)->hLeftButton,XM_PAINT,ToolBar_OnDrawScrollButtonLeft);
	XEle_RegisterMessage(TOOLBAR(hEle)->hRightButton,XM_PAINT,ToolBar_OnDrawScrollButtonRight);
}

/// @brief ��ȡ�������Ϲ�����ť���,ָ��������������ť������Ǹ���ť;
///        ������ť�����������������ϵ�һ��Ԫ��,ֻ���������Ԫ����ʾ�ռ䲻��ʱ�ų���,�Ա������ܿ������ڵ���Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @return ������ť����Ǹ��ľ��.
HELE WINAPI XToolBar_GetButtonLeft(HELE hEle)   //��ȡ�������������ť
{
	IsToolBarDebug(hEle,__FUNCTION__);
	return TOOLBAR(hEle)->hLeftButton;
}

/// @brief ��ȡ�������Ϲ�����ť���,ָ��������������ť���ұ߱��Ǹ���ť;
///        ������ť�����������������ϵ�һ��Ԫ��,ֻ���������Ԫ����ʾ�ռ䲻��ʱ�ų���,�Ա������ܿ������ڵ���Ԫ��.
/// @param hEle Ԫ�ؾ��.
/// @return �ұߵ��Ǹ�������ť���.
HELE WINAPI XToolBar_GetButtonRight(HELE hEle)  //��ȡ�������ҹ�����ť
{
	IsToolBarDebug(hEle,__FUNCTION__);
	return TOOLBAR(hEle)->hRightButton;
}

/// @brief ���ù�����������ͼ.
/// @param hEle Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XToolBar_SetImage(HELE hEle,HIMAGE hImage)
{
	IsToolBarDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(TOOLBAR(hEle)->hImage_bk,hImage);
}

/// @brief ����һ��Ԫ�ص���������.
/// @param hEle Ԫ�ؾ��.
/// @param hNewEle Ҫ�����Ԫ�ؾ��.
/// @param index ����λ������,���-1���뵽ĩβ.
/// @return ����Ԫ�ص�λ������.
int WINAPI XToolBar_InsertEle(HELE hEle,HELE hNewEle,int index) //���Ԫ�ص�������
{
	IsToolBarDebug(hEle,__FUNCTION__);
	IsEleDebug(hNewEle,__FUNCTION__);

	XEle_AddEle(hEle,hNewEle);

	toolBar_  *pObj=TOOLBAR(hEle);

	if(-1==index) //��ӵ�ĩβ
	{
		XArray_Add(pObj->hArrayEle,hNewEle);

		pObj->bAdjust=TRUE;
		return XArray_GetCount(pObj->hArrayEle)-1;
	}else
	{
		if(FALSE==XArray_insert(pObj->hArrayEle,hNewEle,index))
			return -1;

		pObj->bAdjust=TRUE;
		return index;
	}

	return -1;
}

/// @brief �ڹ�����Ԫ����,����һ���ָ�����ָ������λ��.
/// @param hEle Ԫ�ؾ��.
/// @param index ����ָ���λ������.
/// @return ����λ�õ�����.
int WINAPI XToolBar_InsertSeparator(HELE hEle,int index)
{
	IsToolBarDebug(hEle,__FUNCTION__);

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	HELE hNewEle=XEle_Create(0,0,1,rect.bottom-6,hEle);
	XEle_SetBkColor(hNewEle,RGB(128,128,128));

	toolBar_  *pObj=TOOLBAR(hEle);

	if(-1==index) //��ӵ�ĩβ
	{
		XArray_Add(pObj->hArrayEle,hNewEle);

		pObj->bAdjust=TRUE;
		return XArray_GetCount(pObj->hArrayEle)-1;
	}else
	{
		if(FALSE==XArray_insert(pObj->hArrayEle,hNewEle,index))
		{
			XEle_Destroy(hNewEle);
			return -1;
		}
		pObj->bAdjust=TRUE;
		return index;
	}
	return -1;
}

/// @brief ������Ԫ��,��������.
/// @param hEle Ԫ�ؾ��.
void WINAPI XToolBar_Adjust(HELE hEle)
{
	toolBar_  *pToolBar=TOOLBAR(hEle);
	pToolBar->bAdjust=FALSE;

	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	RECT rcToolBar=rect;
	int height=rect.bottom;
	int posx=5;
	BOOL  bShowButton=FALSE;

	int count=XArray_GetCount(pToolBar->hArrayEle);
	for(int i=0;i<pToolBar->indent;i++)
	{
		ele_ *pToolEle=(ele_*)XArray_GetAt(pToolBar->hArrayEle,i);
		XEle_ShowEle((HELE)pToolEle,FALSE);
		bShowButton=TRUE;
	}

	for(int i=pToolBar->indent;i<count;i++)
	{
		ele_ *pToolEle=(ele_*)XArray_GetAt(pToolBar->hArrayEle,i);

		XEle_GetRect((HELE)pToolEle,&rect);
		int cx=rect.right-rect.left;
		int cy=rect.bottom-rect.top;

		rect.top= height/2-cy/2;
		rect.bottom=rect.top+cy;

		rect.left=posx;
		rect.right=rect.left+cx;
		XEle_SetRect((HELE)pToolEle,&rect);
		if(rect.right< (rcToolBar.right-TOOLBAR_BUTTONS_WIDTH))
		{
			XEle_ShowEle((HELE)pToolEle,TRUE);
		}else
		{
			XEle_ShowEle((HELE)pToolEle,FALSE);
			bShowButton=TRUE;
		}

		posx+=cx;
		posx++;
	}

	XEle_ShowEle(pToolBar->hLeftButton,bShowButton);
	XEle_ShowEle(pToolBar->hRightButton,bShowButton);

	rect.top=height/2-10;
	rect.bottom=rect.top+20;
	rect.right=rcToolBar.right-5;
	rect.left=rect.right-20;
	XEle_SetRect(pToolBar->hRightButton,&rect);

	rect.right=rect.left;
	rect.left=rect.right-20;
	XEle_SetRect(pToolBar->hLeftButton,&rect);
}

BOOL CALLBACK ToolBar_OnDraw(HELE hEle,HDRAW hDraw)
{
	if(TOOLBAR(hEle)->bAdjust)
	{
		XToolBar_Adjust(hEle);
	}

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	XDraw_GradientFill2_(hDraw,RGB(230,230,230),RGB(200,200,200),&rect,1);
	if(TOOLBAR(hEle)->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,TOOLBAR(hEle)->hImage_bk,&rect);
	}else
	{
		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(180,180,180));
		HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
		XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
		XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
		//SelectObject(hdc,hOld);
		//DeleteObject(hPen);
	}

	return TRUE;
}

void CALLBACK ToolBar_OnDestroy(HELE hEle)  //����
{
	XArray_Destroy(TOOLBAR(hEle)->hArrayEle);
}

/// @brief ��ȡ��������ָ������Ԫ�صľ��.
/// @param hEle Ԫ�ؾ��.
/// @param index ��Ҫ��ȡ��Ԫ��λ������.
/// @return ����λ�ö�Ӧ��Ԫ�ؾ��.
HELE WINAPI XToolBar_GetHEle(HELE hEle,int index) //��ȡ�������ϰ�ť
{
	IsToolBarDebug(hEle,__FUNCTION__);
	if(index>=0 && index<XArray_GetCount(TOOLBAR(hEle)->hArrayEle))
		return (HELE)XArray_GetAt(TOOLBAR(hEle)->hArrayEle,index);
	else
		return NULL;
}

/// @brief �ӹ��������Ƴ�һ����ť,���Զ�������.
/// @param hEle Ԫ�ؾ��.
/// @param index Ԫ���ڹ������ϵ�����.
void WINAPI XToolBar_DeleteEle(HELE hEle,int index) //�Ƴ���ť
{
	IsToolBarDebug(hEle,__FUNCTION__);
	if(index>=0 && index<XArray_GetCount(TOOLBAR(hEle)->hArrayEle))
	{
		HELE hDel=(HELE)XArray_GetAt(TOOLBAR(hEle)->hArrayEle,index);
		XArray_DeleteIndex(TOOLBAR(hEle)->hArrayEle,index); //��ť�б��Ƴ�
		XEle_Destroy(hDel); //����
	}
}

BOOL CALLBACK ToolBar_OnEventBtnClickLeft(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	toolBar_ *pToolBar=(toolBar_*)XEle_GetParentEle(hEle);
	if(pToolBar->indent>0)
	{
		pToolBar->indent--;
		XToolBar_Adjust((HELE)pToolBar);
		XEle_RedrawEle((HELE)pToolBar);
	}
	return FALSE;
}

BOOL CALLBACK ToolBar_OnEventBtnClickRight(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	toolBar_ *pToolBar =(toolBar_*)XEle_GetParentEle(hEle);
	int count=XArray_GetCount(pToolBar->hArrayEle);
	if(count>0 && FALSE==XEle_IsShowEle((HELE)XArray_GetAt(pToolBar->hArrayEle,count-1)))
	{
		if(pToolBar->indent<(count-1))
		{
			pToolBar->indent++;
			XToolBar_Adjust((HELE)pToolBar);
			XEle_RedrawEle((HELE)pToolBar);
		}
	}
	return FALSE;
}

BOOL CALLBACK ToolBar_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
		XToolBar_Adjust(hEle);
	return FALSE;
}

///@}


/////////////////////////////////////////////
BOOL CALLBACK ToolBar_OnDrawScrollButtonLeft(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	RECT rcText=rect;

	button_ *pObj=BUTTON(hEle);
	wchar_t *pText=XStr_GetBuffer(pObj->hString);
	if(FALSE==((ele_*)hEle)->bEnable) //����
	{
		if(pObj->hImage_disable)
		{
			//XDraw_GraphicsDrawImage(hdc,pObj->pImage_disable,0,0);
			return FALSE;
		}else
		{
			//���û�������
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);

			//�������
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);

			//�����ڱ���
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(240,240,240));
			HRGN hRgn2=XDraw_CreateRoundRectRgn_(hDraw,1,0,rect.right,rect.bottom,0,0);
			XDraw_FrameRgn_(hDraw,hRgn2,hBrush,1,1);
			//DeleteObject(hRgn2);
			//DeleteObject(hBrush);

			//���������
			hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hBrush);
			//DeleteObject(hRgn);
		}
		//���ƽ���״̬��ť
		if(pText)
		{
			COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			XDraw_SetTextColor_(hDraw,color);
		}
		return TRUE;
	}

	if(STATE_LEAVE==BUTTON(hEle)->state)
	{
		if(pObj->hImage_leave)
		{
		//	int ww=pObj->pImage_leave->GetWidth();
		//	int hh=pObj->pImage_leave->GetHeight();
		//	XDraw_GraphicsDrawImage(hdc,pObj->pImage_leave,0,0);
			return FALSE;
		}
	}else if(STATE_STAY==BUTTON(hEle)->state)
	{
		if(pObj->hImage_stay)
		{
		//	XDraw_GraphicsDrawImage(hdc,pObj->pImage_stay,0,0);
			return FALSE;
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);

			hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(252,194,71));
			hRgn=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom,0,0);
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hRgn);
			//DeleteObject(hBrush);
		}
	}else if(STATE_DOWN==BUTTON(hEle)->state)
	{
		if(pObj->hImage_down)
		{
			//XDraw_GraphicsDrawImage(hdc,pObj->pImage_down,0,0);
			return FALSE;
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);

			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(240,240,240));
			HRGN hRgn2=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom+1,0,0);
			XDraw_FrameRgn_(hDraw,hRgn2,hBrush,1,1);
			//DeleteObject(hRgn2);
			//DeleteObject(hBrush);

			HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush2,1,1);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);
			//DeleteObject(hBrush2);

			rcText.left+=2;
			rcText.top+=2;
		}
	}
	if(pText)
		XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	if(((ele_*)hEle)->bDrawFocus && hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		RECT rcFocus={2,2,rect.right-2,rect.bottom-2};
		XDraw_FocusRect_(hDraw,&rcFocus);
	}

	int left=(rect.right-rect.left)/2+3;
	int top=(rect.bottom-rect.top)/2;

	POINT  pt[3];
	pt[0].x=left-3;
	pt[0].y=top;
	pt[1].x=left+2;
	pt[1].y=top+5;
	pt[2].x=left+2;
	pt[2].y=top-5;

	HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
	HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(0,0,0));
	XDraw_FillRgn_(hDraw,hRgn,hBrush2);
	//DeleteObject(hRgn);
	//DeleteObject(hBrush2);

	XDraw_MoveToEx_(hDraw,left-4,3,NULL);
	XDraw_LineTo_(hDraw,left-4,rect.bottom-3);
	
	return TRUE;
}

BOOL CALLBACK ToolBar_OnDrawScrollButtonRight(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	RECT rcText=rect;

	button_ *pObj=BUTTON(hEle);
	wchar_t *pText=XStr_GetBuffer(pObj->hString);
	if(FALSE==((ele_*)hEle)->bEnable) //����
	{
		if(pObj->hImage_disable)
		{
			return FALSE;
		}else
		{
			//���û�������
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);

			//�������
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);

			//�����ڱ���
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(240,240,240));
			HRGN hRgn2=XDraw_CreateRoundRectRgn_(hDraw,1,0,rect.right,rect.bottom,0,0);
			XDraw_FrameRgn_(hDraw,hRgn2,hBrush,1,1);
			//DeleteObject(hRgn2);
			//DeleteObject(hBrush);

			//���������
			hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hBrush);
			//DeleteObject(hRgn);
		}
		//���ƽ���״̬��ť
		if(pText)
		{
			COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,DT_VCENTER | DT_SINGLELINE | DT_CENTER);
			XDraw_SetTextColor_(hDraw,color);
		}
		return TRUE;
	}

	if(STATE_LEAVE==BUTTON(hEle)->state)
	{
		if(pObj->hImage_leave)
		{
		//	int ww=pObj->pImage_leave->GetWidth();
		//	int hh=pObj->pImage_leave->GetHeight();
		//	XDraw_GraphicsDrawImage(hdc,pObj->pImage_leave,0,0);
			return FALSE;
		}
	}else if(STATE_STAY==BUTTON(hEle)->state)
	{
		if(pObj->hImage_stay)
		{
			//XDraw_GraphicsDrawImage(hdc,pObj->pImage_stay,0,0);
			return FALSE;
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);

			hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(252,194,71));
			hRgn=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom,0,0);
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hRgn);
			//DeleteObject(hBrush);
		}
	}else if(STATE_DOWN==BUTTON(hEle)->state)
	{
		if(pObj->hImage_down)
		{
			//XDraw_GraphicsDrawImage(hdc,pObj->pImage_down,0,0);
			return FALSE;
		}else
		{
			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,0,0);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);

			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(240,240,240));
			HRGN hRgn2=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom+1,0,0);
			XDraw_FrameRgn_(hDraw,hRgn2,hBrush,1,1);
			//DeleteObject(hRgn2);
			//DeleteObject(hBrush);

			HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush2,1,1);
			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);
			//DeleteObject(hBrush2);

			rcText.left+=2;
			rcText.top+=2;
		}
	}
	if(pText)
		XDraw_DrawText_(hDraw,pText,XStr_GetLength(pObj->hString),&rcText,DT_VCENTER | DT_SINGLELINE | DT_CENTER);

	if(((ele_*)hEle)->bDrawFocus && hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		RECT rcFocus={2,2,rect.right-2,rect.bottom-2};
		XDraw_FocusRect_(hDraw,&rcFocus);
	}

	int left=(rect.right-rect.left)/2-3;
	int top=(rect.bottom-rect.top)/2;

	POINT  pt[3];
	pt[0].x=left+3;
	pt[0].y=top;
	pt[1].x=left-2;
	pt[1].y=top+5;
	pt[2].x=left-2;
	pt[2].y=top-5;

	HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
	HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(0,0,0));
	XDraw_FillRgn_(hDraw,hRgn,hBrush2);
	//DeleteObject(hRgn);
	//DeleteObject(hBrush2);

	XDraw_MoveToEx_(hDraw,left+3,3,NULL);
	XDraw_LineTo_(hDraw,left+3,rect.bottom-3);

	return TRUE;
}