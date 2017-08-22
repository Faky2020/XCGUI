/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

HELE MenuBarBtn_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent)
{
	menuBarButon_ *pObj=(menuBarButon_*)malloc(sizeof(menuBarButon_));
	memset(pObj,0,sizeof(menuBarButon_));

	MenuBarBtn_Init((HELE)pObj,x,y,cx,cy,XC_MENUBAR_BUTTON,pTitle,hParent);
	return (HELE)pObj;
}

void MenuBarBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent)
{
	Btn_Init(hEle,x,y,cx,cy,eleType,pTitle,hParent);
	AddTypeDebug(hEle,XC_MENUBAR_BUTTON);

	MENUBARBUTTON(hEle)->hMenu=XMenu_Create();

	XMenu_SetAutoDestroy(MENUBARBUTTON(hEle)->hMenu,FALSE);

	XEle_SetBkTransparent(hEle,TRUE);

	XEle_RegisterMessage(hEle,XM_PAINT,MenuBarBtn_OnDraw);
	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,MenuBarBtn_OnLButtonDown);
	XEle_RegisterMessage(hEle,XM_LBUTTONUP,MenuBarBtn_OnLButtonUp);
	XEle_RegisterEvent(hEle,XE_MOUSESTAY,MenuBarBtn_OnEventMouseSay);
	XEle_RegisterEvent(hEle,XE_MOUSELEAVE,MenuBarBtn_OnEventMouseLeave);
	XEle_RegisterEvent(hEle,XE_DESTROY,MenuBarBtn_OnDestroy);
}

void CALLBACK MenuBarBtn_OnDestroy(HELE hEle)  //����
{
	XMenu_Destroy(MENUBARBUTTON(hEle)->hMenu);
}

void MenuBarBtn_AddMenuItem(HELE hEle,int id,wchar_t *pText,int parentId,int uFlags)
{
	XMenu_AddItem(((menuBarButon_*)hEle)->hMenu,id,pText,parentId,uFlags);
}

void MenuBarBtn_AddMenuItemImage(HELE hEle,int id,wchar_t *pText,int parentId,int uFlags,HIMAGE hImage) //���Ӳ˵���
{
	XMenu_AddItemImage(((menuBarButon_*)hEle)->hMenu, id, pText, parentId, uFlags, hImage);
}
/*
void MenuBarBtn_AddMenuItemRes(HELE hEle,int id,wchar_t *pText,int parentId,int uFlags,int resID,wchar_t *pResType)  //���Ӳ˵���
{
XMenu_AddItemImageRes(((menuBarButon_*)hEle)->hMenu, id, pText, parentId, uFlags, resID, pResType);
}
*/
void MenuBarBtn_InsertMenuItem(HELE hEle,int id,wchar_t *pText,int uFlags,int insertID)
{
	XMenu_InsertItem(((menuBarButon_*)hEle)->hMenu, id,pText,uFlags,insertID);
}
void MenuBarBtn_InsertMenuItemImage(HELE hEle,int id,wchar_t *pText,int uFlags,int insertID,HIMAGE hImage) //���Ӳ˵���
{
	XMenu_InsertItemImage(((menuBarButon_*)hEle)->hMenu,id,pText,uFlags,insertID,hImage);
}
/*
void MenuBarBtn_InsertMenuItemImageRes(HELE hEle,int id,wchar_t *pText,int uFlags,int resID,wchar_t *pResType,int insertID)  //���Ӳ˵���
{
XMenu_InsertItemImageRes(((menuBarButon_*)hEle)->hMenu, id,pText,uFlags,resID,pResType,insertID);
}*/

//ɾ���˵���
void MenuBarBtn_DeleteMenuItem(HELE hEle,int id)
{
	XMenu_DeleteItem(((menuBarButon_*)hEle)->hMenu,id);
}

void MenuBarBtn_PopupMenu(HELE hEle)
{
	menuBarButon_ *pObj=MENUBARBUTTON(hEle);

	((popupMenu_*)pObj->hMenu)->hMenuBar=XEle_GetParentEle(hEle);
	RECT rcScreen;
	GetWindowRect(((ele_*)hEle)->pWindow->hWnd,&rcScreen);
	POINT pt={0,((ele_*)hEle)->rect.bottom-((ele_*)hEle)->rect.top};
	XEle_PointToNCWnd(hEle,&pt);
	int x=rcScreen.left+pt.x;
	int y=rcScreen.top+pt.y;

	XMenu_Popup(pObj->hMenu,((ele_*)hEle)->pWindow->hWnd,x,y,(HELE)((ele_*)hEle)->pParentEle);
}

void MenuBarBtn_CloseMenu(HELE hEle)
{
	if(MENUBARBUTTON(hEle)->hMenu)
	{
		XMenu_CloseMenu(MENUBARBUTTON(hEle)->hMenu);
	}
}

BOOL CALLBACK MenuBarBtn_OnDraw(HELE hEle,HDRAW hDraw)
{
	button_ *pButton=BUTTON(hEle);
	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	if(STATE_LEAVE==pButton->state)
	{
		if(BUTTON(hEle)->hImage_leave)
		{
			return FALSE;
		}//else
		//			Ele_DrawTransparent(hEle,hdc,&rect);
	}else if(STATE_STAY==pButton->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(250,250,250),RGB(220,220,220),&rect,GRADIENT_FILL_RECT_V);
		if(BUTTON(hEle)->hImage_stay)
		{
			return FALSE;
		}else
		{
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			//	DeleteObject(hBrush);
		}
	}else if(STATE_DOWN==pButton->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(200,200,200),RGB(250,250,250),&rect,GRADIENT_FILL_RECT_V);
		if(BUTTON(hEle)->hImage_down)
		{
			return FALSE;
		}else
		{
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			//DeleteObject(hBrush);
		}
	}

	if(pButton->hString)
	{
		wchar_t *pText=XStr_GetBuffer(pButton->hString);
		if(pText)
			XDraw_DrawText_(hDraw,pText,XStr_GetLength(pButton->hString),&rect,DT_VCENTER | DT_CENTER | DT_SINGLELINE);
	}

	return TRUE;
}

BOOL CALLBACK MenuBarBtn_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	ele_ *pPar=((ele_*)hEle)->pParentEle;
	if(XC_MENUBAR==pPar->eleType)
	{
		menuBar_ *pMenuBar=(menuBar_*)pPar;
		if(FALSE==pMenuBar->bDown)
		{
			int menuItemCount=XMenu_GetItemCount(((menuBarButon_*)hEle)->hMenu);
			if(menuItemCount>0)
			{
				((button_*)hEle)->state=STATE_DOWN;
				XEle_RedrawEle(hEle);
				pMenuBar->pBtnTop=MENUBARBUTTON(hEle);
				pMenuBar->bDown=TRUE;
				XTRACE("�����˵� \n");
				MenuBarBtn_PopupMenu(hEle);
				return TRUE;
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK MenuBarBtn_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	return FALSE;
}

BOOL CALLBACK MenuBarBtn_OnEventMouseSay(HELE hEle,HELE hEventEle) //���ͣ��
{
	if(hEle!=hEventEle)
		return FALSE;

	menuBar_ *pMenuBar=(menuBar_*)((ele_*)hEle)->pParentEle;
	if(pMenuBar->bDown)
		return TRUE;
	else
		return FALSE;
}

BOOL CALLBACK MenuBarBtn_OnEventMouseLeave(HELE hEle,HELE hEventEle) //����뿪
{
	if(hEle!=hEventEle)
		return FALSE;

	menuBar_ *pMenuBar=(menuBar_*)((ele_*)hEle)->pParentEle;
	if(pMenuBar->bDown)
		return TRUE;
	else
		return FALSE;
}

/////////////////////////////////////////////////////////////////////////////
/// @defgroup menuBar �˵���(MenuBar)
/// @ingroup groupElements
/// @{

/// @brief �����˵���Ԫ��;���ָ���˸�Ϊ����,Ĭ�ϵ���XWnd_AddMenuBar()����,���˵�����ӵ����ڷǿͻ���.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����U IԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XMenuBar_Create(int x, int y, int cx, int cy,HXCGUI hParent)  //������ť
{
	menuBar_ *pObj=(menuBar_*)malloc(sizeof(menuBar_));
	memset(pObj,0,sizeof(menuBar_));
	if(pObj)
	{
		MenuBar_Init((HELE)pObj,x,y,cx,cy,XC_MENUBAR,hParent);
		return (HELE)pObj;
	}
	free(pObj);
	return NULL;
}

//˽�з���:
void MenuBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	if(hParent && XC_WINDOW==((object_*)hParent)->type)
	{
		Ele_Init(hEle,x,y,cx,cy,eleType,NULL);
		AddTypeDebug(hEle,XC_MENUBAR);
		XWnd_AddMenuBar((HWINDOW)hParent,hEle);
	}else
	{
		Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
		AddTypeDebug(hEle,XC_MENUBAR);
	}

	MENUBAR(hEle)->buttonHeight=20;
	((ele_*)hEle)->bkColor=RGB(230,230,230);

	XEle_RegisterMessage(hEle,XM_PAINT,MenuBar_OnDraw);
	//XEle_RegisterMessage(hEle,XM_MOUSEMOVE,MenuBar_OnMouseMove);
	//XEle_RegisterEvent(hEle,XE_MENUSELECT,MenuBar_OnEventMenuSelect);
	//XEle_RegisterEvent(hEle,XE_MENUEXIT,MenuBar_OnEventMenuExit);
	XEle_RegisterEvent(hEle,XE_DESTROY,MenuBar_OnDestroy);
}

/// @brief ��Ӳ˵����ϵĲ˵�������ť.
/// @param hEle Ԫ�ؾ��.
/// @param pText �ı�����.
/// @return ��ťλ������.
int WINAPI XMenuBar_AddButton(HELE hEle,wchar_t *pText)
{
	IsMenuBarDebug(hEle,__FUNCTION__);

	HDC hdc=GetDC(NULL);
	SIZE size;
	GetTextExtentPoint32(hdc,pText,wcslen(pText),&size);
	ReleaseDC(NULL,hdc);

	HELE hButton=MenuBarBtn_Create(0,0,size.cx+6,MENUBAR(hEle)->buttonHeight,pText);
	if(FALSE==XEle_AddEle(hEle,hButton))
		return -1;

	XEle_EnableFocus(hButton,FALSE);

	MENUBAR(hEle)->bAdjust=TRUE;
	return XArray_GetCount(((ele_*)hEle)->hArrayEle)-1;
}

/// @brief ���뵯���˵���ť.
/// @param hEle Ԫ�ؾ��.
/// @param pText �ı�����.
/// @param index ����λ������.
/// @return ��ťλ������.
int WINAPI XMenuBar_InsertButton(HELE hEle,wchar_t *pText,int index)    //���뵯���˵���ť
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HDC hdc=GetDC(NULL);
	SIZE size;
	GetTextExtentPoint32(hdc,pText,wcslen(pText),&size);
	ReleaseDC(NULL,hdc);

	HELE hButton=MenuBarBtn_Create(0,0,size.cx+6,MENUBAR(hEle)->buttonHeight,pText);
	if(FALSE==XEle_AddEle(hEle,hButton,XC_ADDELE_INDEX,NULL,index))
	{
		return -1;
	}

	MENUBAR(hEle)->bAdjust=TRUE;
	return index;
}

/// @brief ��Ӳ˵���.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵����ϰ�ť����.
/// @param id   �˵���ID.
/// @param pText �ı�����.
/// @param parentId �˵���ĸ���ID.
/// @param uFlags ��ʶ.
void WINAPI XMenuBar_AddMenuItem(HELE hEle,int index,int id,wchar_t *pText,int parentId,int uFlags)
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HELE  hMenuBarBtn=(HELE)Array_GetAtEle(((ele_*)hEle)->hArrayEle,index);
	if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		MenuBarBtn_AddMenuItem(hMenuBarBtn,id,pText,parentId,uFlags);
}

/// @brief ��Ӳ˵���,��ָ��ͼ��.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵����ϰ�ť����.
/// @param id   �˵���ID.
/// @param pText �ı�����.
/// @param parentId �˵���ĸ���ID.
/// @param uFlags ��ʶ.
/// @param hImage  ͼƬ���.
void WINAPI XMenuBar_AddMenuItemImage(HELE hEle,int index,int id,wchar_t *pText,int parentId,int uFlags,HIMAGE hImage) //���Ӳ˵���
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HELE  hMenuBarBtn=(HELE)Array_GetAtEle(((ele_*)hEle)->hArrayEle,index);
	if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		MenuBarBtn_AddMenuItemImage(hMenuBarBtn,id,pText,parentId,uFlags,hImage);
}

/// @brief ��Ӳ˵���,��ָ��ͼ��.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵����ϰ�ť����.
/// @param id   �˵���ID.
/// @param pText �ı�����.
/// @param uFlags ��ʶ.
/// @param insertID ���뵽����ǰ��.
void WINAPI XMenuBar_InsertMenuItem(HELE hEle,int index,int id,wchar_t *pText,int uFlags,int insertID) //����˵���
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HELE  hMenuBarBtn=(HELE)Array_GetAtEle(((ele_*)hEle)->hArrayEle,index);
	if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		MenuBarBtn_InsertMenuItem(hMenuBarBtn,id,pText,uFlags,insertID);
}

/// @brief ��Ӳ˵���,��ָ��ͼ��.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵����ϰ�ť����.
/// @param id   �˵���ID.
/// @param pText �ı�����.
/// @param uFlags ��ʶ.
/// @param insertID ���뵽����ǰ��.
/// @param hImage  ͼƬ���.
void WINAPI XMenuBar_InsertMenuItemImage(HELE hEle,int index,int id,wchar_t *pText,int uFlags,int insertID,HIMAGE hImage) //���Ӳ˵���
{	
	IsMenuBarDebug(hEle,__FUNCTION__);
	IsHImageDebug(hImage,__FUNCTION__);
	HELE  hMenuBarBtn=(HELE)Array_GetAtEle(((ele_*)hEle)->hArrayEle,index);
	if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		MenuBarBtn_InsertMenuItemImage(hMenuBarBtn,id,pText,uFlags,insertID,hImage);
}

/// @brief ɾ���˵���.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵����ϰ�ť����.
/// @param id   �˵���ID.
void WINAPI XMenuBar_DeleteMenuItem(HELE hEle,int index,int id)
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HELE  hMenuBarBtn=(HELE)Array_GetAtEle(((ele_*)hEle)->hArrayEle,index);
	if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		MenuBarBtn_DeleteMenuItem(hMenuBarBtn,id);
}

/// @brief ���ò˵����ϰ�ť�߶�.
/// @param hEle Ԫ�ؾ��.
/// @param height ��ť�߶�.
void WINAPI XMenuBar_SetButtonHeight(HELE hEle,int height)
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	MENUBAR(hEle)->buttonHeight=height;
}

/// @brief ��ȡ�˵����ϰ�ť���.��ť����ΪMenuBarButton.
/// @param hEle Ԫ�ؾ��.
/// @param index ��ť����λ������.
/// @return ��ť���.
HELE WINAPI XMenuBar_GetButton(HELE hEle,int index)  //��ȡ�˵����ϰ�ť
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	return (HELE)XArray_GetAt(((ele_*)hEle)->hArrayEle,index);
}

/// @brief ��ȡ�˵����.
/// @param hEle Ԫ�ؾ��.
/// @param index �˵�����λ������.
/// @return �˵����.
HMENUX WINAPI XMenuBar_GetMenu(HELE hEle,int index) //��ȡ�˵����
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	HELE hButton=XMenuBar_GetButton(hEle,index);  //��ȡ�˵����ϰ�ť
	if(hButton)
	{
		if(XC_MENUBAR_BUTTON==XC_GetObjectType(hButton))
		{
			menuBarButon_ *pMenuBtn=(menuBarButon_*)hButton;
			return pMenuBtn->hMenu;
		}
	}
	return NULL;
}

/// @brief ɾ���˵����ϵ�ָ�������˵���ť,��������,ͬʱ�õ����˵���ť�µĵ����˵�Ҳ������.
/// @param hEle Ԫ�ؾ��.
/// @param index ��ť����λ������.
void WINAPI XMenuBar_DeleteButton(HELE hEle,int index) //ɾ���˵��������,ͬʱ�ð�ť�µĵ����˵�Ҳ������
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	int count = XArray_GetCount(((ele_*)hEle)->hArrayEle);
	if(index>=0 && index<count)
	{
		HELE hDel=(HELE)XArray_GetAt(((ele_*)hEle)->hArrayEle,index);
		XEle_Destroy(hDel);
		MENUBAR(hEle)->bAdjust=TRUE;
	}
}

/// @brief ���ò˵���Ԫ�ر�����ͼ.
/// @param hEle Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XMenuBar_SetImage(HELE hEle,HIMAGE hImage)
{
	IsMenuBarDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}

	Image_AddImage(MENUBAR(hEle)->hImage,hImage);
}

void MenuBar_OnMenuMouseMove(HELE hEle,POINT *pPt)
{
	//pPt:��Ļ����
	menuBar_ *pMenuBar=MENUBAR(hEle);

	if(pMenuBar->bDown)
	{
		POINT pt={pPt->x,pPt->y};
		ScreenToClient(((ele_*)hEle)->pWindow->hWnd,&pt);
		XEle_PointNCWndToEle(hEle,&pt);

		MenuBar_OnMouseMove(hEle,0,&pt);
	}
}

void MenuBar_Adjust(HELE hEle) //��������
{
	MENUBAR(hEle)->bAdjust=FALSE;

	menuBar_ *pObject=(menuBar_*)hEle;

	ele_* pEle=(ele_*)hEle;
	int top=(pEle->rect.bottom-pEle->rect.top-MENUBAR(hEle)->buttonHeight)/2;

	int left=5;
	int width=0;
	RECT rect;

	int count=XArray_GetCount(pEle->hArrayEle);
	for(int i=0;i<count;i++)
	{
		HELE  hMenuBarBtn=(HELE)(menuBarButon_*)XArray_GetAt( pEle->hArrayEle,i);
		if(XC_MENUBAR_BUTTON==XC_GetObjectType(hMenuBarBtn))
		{
			XEle_GetRect(hMenuBarBtn,&rect);
			width=rect.right-rect.left;

			rect.left=left;
			rect.right=rect.left+width;
			rect.top=top;
			rect.bottom=rect.top+MENUBAR(hEle)->buttonHeight;
			XEle_SetRect(hMenuBarBtn,&rect);
			left+=width;
		}
	}
}

BOOL CALLBACK MenuBar_OnMouseMove(HELE hEle,UINT flags,POINT *pPt)
{
	menuBar_ *pMenuBar=MENUBAR(hEle);
	if(pMenuBar->bDown)
	{
		POINT pt={pPt->x,pPt->y};
		int count=Array_GetCount(((ele_*)hEle)->hArrayEle);
		for(int i=0; i<count; i++)
		{
			ele_ *pChild=Array_GetAtEle(((ele_*)hEle)->hArrayEle,i);

			if(XC_MENUBAR_BUTTON==XC_GetObjectType(pChild))
			{
				if( PtInRect(&pChild->rect,pt) )
				{
					int menuItemCount=XMenu_GetItemCount(((menuBarButon_*)pChild)->hMenu);
					if(menuItemCount>0)
					{
						if(pMenuBar->pBtnTop!=((menuBarButon_*)pChild))
						{
							if(pMenuBar->pBtnTop) //�ر���ǰ�Ĳ˵�
							{
								MenuBarBtn_CloseMenu((HELE)pMenuBar->pBtnTop);
								((button_*)pMenuBar->pBtnTop)->state=STATE_LEAVE; //�޸İ�ť״̬
								XEle_RedrawEle((HELE)pMenuBar->pBtnTop);
							}
							pMenuBar->pBtnTop=(menuBarButon_*)pChild;
							((button_*)pChild)->state=STATE_DOWN;
							XEle_RedrawEle((HELE)pChild);
							MenuBarBtn_PopupMenu((HELE)pChild);
						}
					}
					break;
				}
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK MenuBar_OnDraw(HELE hEle,HDRAW hDraw)
{
	if(MENUBAR(hEle)->bAdjust)
		MenuBar_Adjust(hEle);

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	//	if(XEle_IsBkTransparent(hEle))
	//		Ele_DrawTransparent(hEle,hdc,&rect);
	//	else
	//	{
	XDraw_FillSolidRect_(hDraw,&rect,((ele_*)hEle)->bkColor);
	if(MENUBAR(hEle)->hImage)
	{
		XDraw_HImageSuper_(hDraw,MENUBAR(hEle)->hImage,&rect);
	}else
	{
		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(180,180,180));
		HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);
		XDraw_MoveToEx_(hDraw,0,rect.bottom-1,NULL);
		XDraw_LineTo_(hDraw,rect.right,rect.bottom-1);
		//	SelectObject(hdc,hOld);
		//	DeleteObject(hPen);
	}
	//	}
	return TRUE;
}

void CALLBACK MenuBar_OnDestroy(HELE hEle)  //����
{
	if(MENUBAR(hEle)->hImage) XImage_Destroy(MENUBAR(hEle)->hImage);
}

///@}