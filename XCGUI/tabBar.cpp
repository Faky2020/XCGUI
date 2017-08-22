/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup tabBar tabBarԪ��(TabBar)
/// @ingroup groupElements
/// @{

/// @brief ����tabBarԪ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XTabBar_Create(int x, int y, int cx, int cy,HXCGUI hParent)
{
	tabBar_ *pNew=(tabBar_*)malloc(sizeof(tabBar_));
	memset(pNew,0,sizeof(tabBar_));   

	TabBar_Init((HELE)pNew,x,y,cx,cy,XC_TABBAR,hParent);
	return (HELE)pNew;
}

void TabBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_TABBAR);

	tabBar_ *pObject=(tabBar_*)hEle;
	pObject->hArrayList=XArray_Create();
	pObject->widthBtn=45;
	pObject->height=cy;
	pObject->spacing=1;
	pObject->align=align_top;

	pObject->hBtnUp=XBtn_Create(cx-39,pObject->height-22,20,20,L"<<");
	XEle_AddEle(hEle,pObject->hBtnUp);

	pObject->hBtnDown=XBtn_Create(cx-20,pObject->height-22,20,20,L">>");
	XEle_AddEle(hEle,pObject->hBtnDown);

	XEle_ShowEle(pObject->hBtnUp,FALSE);
	XEle_ShowEle(pObject->hBtnDown,FALSE);

	XEle_RegisterMessage(hEle,XM_PAINT,TabBar_OnDraw);
	XEle_RegisterEvent(hEle,XE_SIZE,TabBar_OnEventSize);

	XEle_RegisterMessage(pObject->hBtnUp,XM_PAINT,TabBar_OnDraw_Up);
	XEle_RegisterMessage(pObject->hBtnDown,XM_PAINT,TabBar_OnDraw_Down);
	XEle_RegisterEvent(pObject->hBtnUp,XE_BNCLICK,TabBar_OnEventBtnClick_Up);
	XEle_RegisterEvent(pObject->hBtnDown,XE_BNCLICK,TabBar_OnEventBtnClick_Down);
	XEle_RegisterEvent(hEle,XE_DESTROY,TabBar_OnDestroy);
}

/// @brief ���һ����ǩ.
/// @param hEle   Ԫ�ؾ��
/// @param *pName ��ǩ�ı�����.
/// @param hPage   ��ҳԪ�ؾ��.
/// @return ��ǩ����.
int WINAPI XTabBar_AddLabel(HELE hEle,wchar_t *pName,HELE hPage) //���һ����ǩ
{
	IsTabBarDebug(hEle,__FUNCTION__);
	if(hPage)
	{
		IsEleDebug(hPage,__FUNCTION__);
	}
	tabBar_  *pObject=(tabBar_*)hEle;

	tabBar_item_ *pItem=(tabBar_item_*)TabBar_AddLabel(hEle,pName,hPage);

	XArray_Add(pObject->hArrayList,pItem);
	pObject->bAdjust=TRUE;
	return Array_GetCount(pObject->hArrayList)-1;
}

/// @brief ����һ����ǩ.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ����λ��.
/// @param *pName ��ǩ�ı�����.
/// @param hPage   ��ҳԪ�ؾ��.
/// @return ��ǩ����.
int WINAPI XTabBar_InsertLabel(HELE hEle,int index,wchar_t *pName,HELE hPage)
{
	IsTabBarDebug(hEle,__FUNCTION__);
	if(hPage)
	{
		IsEleDebug(hPage,__FUNCTION__);
	}

	tabBar_item_ *pItem=TabBar_AddLabel(hEle,pName,hPage);
	XArray_insert(((tabBar_*)hEle)->hArrayList,pItem,index);
	((tabBar_*)hEle)->bAdjust=TRUE;
	return index;
}

/// @brief ɾ��һ����ǩ.
/// @param hEle   Ԫ�ؾ��.
/// @param index  λ������.
/// @param deletePage  �Ƿ�ͬʱɾ���󶨵�ҳԪ��.
void WINAPI XTabBar_DeleteLabel(HELE hEle,int index,BOOL deletePage)  //ɾ��
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pObject=(tabBar_*)hEle;
	int count=Array_GetCount(pObject->hArrayList);
	if(index>=0 && index<count)
	{
		tabBar_item_ *pDel=(tabBar_item_*)Array_GetAt(pObject->hArrayList,index);
		XArray_DeleteIndex(pObject->hArrayList,index);
		count--;
		XEle_Destroy(pDel->hButton);
		if(deletePage)
		{
			if(pDel->hPage)	XEle_Destroy(pDel->hPage);
		}

		if(pObject->pSelectItem==pDel)
		{
			if(index>=count) index--;

			if(index>=0)
			{
				pObject->pSelectItem=(tabBar_item_*)Array_GetAt(pObject->hArrayList,index);
				XBtn_SetCheck(pObject->pSelectItem->hButton,TRUE);
				
				Ele_SendEvent(hEle,XE_TABBAR_SELECT,index,0);
			}else
			{	
				pObject->pSelectItem=NULL;
				Ele_SendEvent(hEle,XE_TABBAR_SELECT,-1,0);
			}
			TabBar_OnEventSize(hEle,hEle);
		}
		free(pDel);
		
		//XEle_RedrawEle(hEle);
	}
}

/// @brief ɾ�����б�ǩ.
/// @param hEle   Ԫ�ؾ��.
/// @param deletePage  �Ƿ�ͬʱɾ���󶨵�ҳԪ��.
void WINAPI XTabBar_DeleteLabelAll(HELE hEle,BOOL deletePage) //ɾ������TAB
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pObject=(tabBar_*)hEle;
	int count=Array_GetCount(pObject->hArrayList);
	tabBar_item_ *pDel=NULL;
	for(int i=0;i<count;i++)
	{
		pDel=(tabBar_item_*)Array_GetAt(pObject->hArrayList,i);
		XEle_Destroy(pDel->hButton);
		if(deletePage)
		{
			if(pDel->hPage)	XEle_Destroy(pDel->hPage);
		}
		free(pDel);
	}
	XArray_DeleteAll(pObject->hArrayList);

	if(pObject->pSelectItem)
	{
		pObject->pSelectItem=NULL;
		Ele_SendEvent(hEle,XE_TABBAR_SELECT,-1,0);
	}
	pObject->indent=0;
	TabBar_Adjust(hEle);
	//XEle_RedrawEle(hEle);
}

/// @brief ��ȡ��ǩ��ťButton.
/// @param hEle   Ԫ�ؾ��.
/// @param index  λ������.
/// @return ��ť���.
HELE WINAPI XTabBar_GetLabel(HELE hEle,int index) //��ȡ��ǩ��ťButton
{
	IsTabBarDebug(hEle,__FUNCTION__);
	if(index>=0 && index< Array_GetCount(((tabBar_*)hEle)->hArrayList))
	{
		tabBar_item_ *pItem=(tabBar_item_*)XArray_GetAt(((tabBar_*)hEle)->hArrayList,index);
		return pItem->hButton;
	}
	return NULL;
}

/// @brief ��ȡ��ǩ��Ӧ��ҳ.
/// @param hEle   Ԫ�ؾ��.
/// @param index  λ������.
/// @return �󶨵�ҳԪ��.
HELE WINAPI XTabBar_GetLabelPage(HELE hEle,int index)  //��ȡ��ǩ��Ӧ��ҳ
{
	IsTabBarDebug(hEle,__FUNCTION__);
	if(index>=0 && index< Array_GetCount(((tabBar_*)hEle)->hArrayList))
	{
		tabBar_item_ *pItem=(tabBar_item_*)XArray_GetAt(((tabBar_*)hEle)->hArrayList,index);
		return pItem->hPage;
	}
	return NULL;
}

/// @brief ������ҳ��Ӧ��ǩ����.
/// @param hEle   Ԫ�ؾ��.
/// @param hPage  �󶨵�ҳԪ��.
/// @return ��ǩ����,ʧ�ܷ���-1.
int WINAPI XTabBar_GetPageIndex(HELE hEle,HELE hPage) //������ҳ��Ӧ��ǩ����
{
	IsTabBarDebug(hEle,__FUNCTION__);
	int count=XArray_GetCount(((tabBar_*)hEle)->hArrayList);
	for(int i=0;i<count;i++)
	{
		tabBar_item_ *pItem=(tabBar_item_*)XArray_GetAt(((tabBar_*)hEle)->hArrayList,i);
		if(hPage==pItem->hPage)
		{
			return i;
		}
	}
	return -1;
}

/// @brief ��ȡѡ��ı�ǩ����.
/// @param hEle  Ԫ�ؾ��.
/// @return ��ǩλ������.
int  WINAPI XTabBar_GetSelect(HELE hEle)  //��ȡѡ��ı�ǩ
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pObject=(tabBar_*)hEle;
	if(pObject->pSelectItem)
	{
		tabBar_item_  *pItem=NULL;
		int count=XArray_GetCount(pObject->hArrayList);
		for(int i=0;i<count;i++)
		{
			pItem=(tabBar_item_*)XArray_GetAt(pObject->hArrayList,i);
			if(pObject->pSelectItem==pItem)
			{
				return i;
			}
		}
	}
	return -1;
}

/// @brief ���ñ�ǩ���, 0û�м��.
/// @param hEle   Ԫ�ؾ��.
/// @param spacing  ��ǩ�����С.
void WINAPI XTabBar_SetLabelSpacing(HELE hEle,int spacing) //���ñ�ǩ���, 0û�м��
{
	IsTabBarDebug(hEle,__FUNCTION__);
	((tabBar_*)hEle)->spacing=spacing;
	((tabBar_*)hEle)->bAdjust=TRUE;
}

/// @brief ��ȡ��ǩ���, 0û�м��.
/// @param hEle   Ԫ�ؾ��.
/// @return  ��ǩ�����С.
int WINAPI XTabBar_GetLabelSpacing(HELE hEle) //��ȡ��ǩ���, 0û�м��
{
	IsTabBarDebug(hEle,__FUNCTION__);
	return ((tabBar_*)hEle)->spacing;
}

/// @brief ��ȡ��ǩ������.
/// @param hEle   Ԫ�ؾ��.
/// @return  ��ǩ������.
int  WINAPI XTabBar_GetLabelCount(HELE hEle) //��ȡ��ǩ������
{
	IsTabBarDebug(hEle,__FUNCTION__);
	return XArray_GetCount(((tabBar_*)hEle)->hArrayList);
}

/// @brief ����ͼԪ�ص���ǩ.
/// @param hEle   Ԫ�ؾ��.
/// @param index  ��ǩ����.
/// @param hPage  ��ͼԪ��.
/// @return  �ɹ�����TRUE,�����෴.
BOOL WINAPI XTabBar_SetBindEle(HELE hEle,int index,HELE hPage) //����ͼԪ�ص���ǩ
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pObj=(tabBar_*)hEle;
	if(index<0 || index>= Array_GetCount(pObj->hArrayList))
		return FALSE;

	if(NULL==hPage)
		return FALSE;

	tabBar_item_ *pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,index);
	pItem->hPage=hPage;

	if(pItem==pObj->pSelectItem)
	{
		XEle_ShowEle(hPage,TRUE);
	}else
	{
		XEle_ShowEle(hPage,FALSE);
	}
	return TRUE;
}

/// @brief ����ѡ���ǩ.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������.
/// @param reDraw �Ƿ��ػ�.
void WINAPI XTabBar_SetSelect(HELE hEle,int index,BOOL reDraw)   //����ѡ���ǩ
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pObj=(tabBar_*)hEle;
	if(index<0 || index>=Array_GetCount(pObj->hArrayList))
		return ;

	tabBar_item_ *pNewSel=(tabBar_item_*)Array_GetAt(pObj->hArrayList,index);
	if(pObj->pSelectItem !=pNewSel)
	{
		if(pObj->pSelectItem)
		{
			if(pObj->pSelectItem->hPage)
				XEle_ShowEle(pObj->pSelectItem->hPage,FALSE);
			XBtn_SetCheck(pObj->pSelectItem->hButton,FALSE);
			//��������Ԫ��
			if(reDraw)
			{
				RECT rect;
				XEle_GetClientRect(pObj->pSelectItem->hPage,&rect);
				XEle_RectToNCWnd(pObj->pSelectItem->hPage,&rect);
				XWnd_RedrawWndRect(XEle_GetHWindow(hEle),&rect);
			}
		}
		pObj->pSelectItem=pNewSel;
		if(pObj->pSelectItem->hPage)
			XEle_ShowEle(pObj->pSelectItem->hPage,TRUE);
		XBtn_SetCheck(pObj->pSelectItem->hButton,TRUE);

		//pObj->indent=index;
		pObj->bAdjust=TRUE;

		Ele_SendEvent(hEle,XE_TABBAR_SELECT,index,0);
		if(reDraw)
		{
			XEle_RedrawEle(pObj->pSelectItem->hPage);
			XEle_RedrawEle(hEle);
		}
	}
}

/// @brief ���ö��뷽��.
/// @param hEle  Ԫ�ؾ��.
/// @param align ���뷽��,Ŀǰ�϶�����¶�����Ч.
void WINAPI XTabBar_SetAlign(HELE hEle,align_type_ align)
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pTabBar=(tabBar_*)hEle;
	if(pTabBar->align != align)
	{
		pTabBar->align=align;
		TabBar_Adjust(hEle);
	}
}

/// @brief ƽ�̱�ǩ,ÿ����ǩ��ʾ��ͬ��С.
/// @param hEle  Ԫ�ؾ��.
/// @param bTile �Ƿ�����.
void WINAPI XTabBar_EnableTile(HELE hEle,BOOL bTile)  //ƽ�̱�ǩ,ÿ����ǩ��ʾ��ͬ��С
{
	IsTabBarDebug(hEle,__FUNCTION__);
	((tabBar_*)hEle)->bTile=bTile;
	TabBar_Adjust(hEle);
}

tabBar_item_* TabBar_AddLabel(HELE hEle,wchar_t *pName,HELE hPage)
{
	tabBar_item_  *pItem=(tabBar_item_*)malloc(sizeof(tabBar_item_));
	memset(pItem,0,sizeof(tabBar_item_));

	pItem->hButton=XBtn_Create(0,0,10,10,pName,hEle);
	pItem->hPage=hPage;
	//if(hPage && NULL==((ele_*)hPage)->pParentEle)
	//{
	//	XEle_AddEle(hEle,hPage);
	//}

	XEle_RegisterMessage(pItem->hButton,XM_PAINT,TabBar_Btn_OnDrawLabel);
	XEle_RegisterEvent(pItem->hButton,XE_BNCLICK,TabBar_OnEventBtnClick);
	tabBar_ *pObject=(tabBar_*)hEle;
	if(pName)
	{
		SIZE size;    //�ַ�����
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)pItem->hButton)->hFontX));
		GetTextExtentPoint32(hdc,pName,wcslen(pName),&size);
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);

		pItem->width=size.cx+10;
	}
	if(pItem->width<50)
		pItem->width=50;

	if(NULL==pObject->pSelectItem)
	{
		pObject->pSelectItem=pItem;
		XBtn_SetCheck(pItem->hButton,TRUE);
	}

	return pItem;
}

void TabBar_Adjust(HELE hEle)
{
	tabBar_ *pObj=(tabBar_*)hEle;
	pObj->bAdjust=FALSE;
	int count=Array_GetCount(pObj->hArrayList);
	if(count<1)
	{
		pObj->indent=0;
		XEle_ShowEle(pObj->hBtnUp,FALSE);
		XEle_ShowEle(pObj->hBtnDown,FALSE);
		return;
	}
	if(pObj->indent>=count)
	{
		pObj->indent=0;
	}

	if(pObj->bTile)  //ƽ��
	{
		int width=((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left;
		int size=width/count;
		tabBar_item_ *pItem=NULL;
		RECT rcItem;
		for(int i=0;i<(count-1);i++)
		{
			pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,i);
			rcItem.left=size*i;
			rcItem.top=0;
			rcItem.right=rcItem.left+size;
			rcItem.bottom=pObj->height;
			XEle_SetRect(pItem->hButton,&rcItem);
		}
		pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,count-1);
		rcItem.left=size*(count-1);
		rcItem.top=0;
		rcItem.right=width;
		rcItem.bottom=pObj->height;
		XEle_SetRect(pItem->hButton,&rcItem);
		return ;
	}


	int width=((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left;//-pObj->widthBtn;

	int index=0;
	int left=0;
	tabBar_item_ *pItem=NULL;
	for(;index<pObj->indent;index++)
	{
		pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,index);
		XEle_ShowEle(pItem->hButton,FALSE);
	}

	left=0;
	RECT rcItem;
	for(;index<count;index++)
	{
		pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,index);

		if((left+pItem->width)>width)
			break;

		rcItem.left=left;
		rcItem.top=0;
		rcItem.right=left+pItem->width;
		rcItem.bottom=pObj->height;
		XEle_SetRect(pItem->hButton,&rcItem);
		XEle_ShowEle(pItem->hButton,TRUE);

		left+=pItem->width;
		left+=pObj->spacing;
	}

	//����������ť
	if(0!=pObj->indent || index!=count)
	{
		XEle_ShowEle(pObj->hBtnUp,TRUE);
		XEle_ShowEle(pObj->hBtnDown,TRUE);
	}else
	{
		XEle_ShowEle(pObj->hBtnUp,FALSE);
		XEle_ShowEle(pObj->hBtnDown,FALSE);
	}

	for(;index<count;index++)
	{
		pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,index);
		XEle_ShowEle(pItem->hButton,FALSE);
	}

	for(int i=0;i<count;i++)
	{
		pItem=(tabBar_item_*)Array_GetAt(pObj->hArrayList,i);
		if(pItem->hPage)
		{
			if(pObj->pSelectItem==pItem)
				XEle_ShowEle(pItem->hPage,TRUE);
			else
				XEle_ShowEle(pItem->hPage,FALSE);
		}
	}
}


BOOL CALLBACK TabBar_OnDraw(HELE hEle,HDRAW hDraw)
{
	tabBar_ *pTabBar=(tabBar_*)hEle;
	if(pTabBar->bAdjust)
	{
		TabBar_Adjust(hEle);
	}

	if(FALSE==((ele_*)hEle)->bBorder)
		return TRUE;

	RECT rectEle;
	XEle_GetClientRect(hEle,&rectEle);

	if(align_top==pTabBar->align)
	{
		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,((ele_*)hEle)->borderColor);
		HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);

		XDraw_MoveToEx_(hDraw,rectEle.left,rectEle.bottom-1);
		XDraw_LineTo_(hDraw,rectEle.right,rectEle.bottom-1);

		XDraw_SelectObject_(hDraw,hOld);
		XDraw_DeleteObject_(hDraw,hPen);
	}else if(align_bottom==pTabBar->align)
	{
		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,((ele_*)hEle)->borderColor);
		HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);

		XDraw_MoveToEx_(hDraw,rectEle.left,rectEle.top);
		XDraw_LineTo_(hDraw,rectEle.right,rectEle.top);

		XDraw_SelectObject_(hDraw,hOld);
		XDraw_DeleteObject_(hDraw,hPen);
	}

	return TRUE;
}

BOOL CALLBACK TabBar_Btn_OnDrawLabel(HELE hEle,HDRAW hDraw)
{
	HELE hParent=XEle_GetParentEle(hEle);
	if(align_top==((tabBar_*)hParent)->align)
	{
		return TabBar_Btn_OnDrawLabel_Top(hEle,hDraw);
	}else if(align_bottom==((tabBar_*)hParent)->align)
	{
		return TabBar_Btn_OnDrawLabel_Bottom(hEle,hDraw);
	}
	return TRUE;
}

BOOL TabBar_Btn_OnDrawLabel_Top(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	button_ *pObj=BUTTON(hEle);

	if(pObj->bCheck)
	{
		if(pObj->hImage_check)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);

			//������ǳ��ɫ��
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);
			//SelectObject(hdc,hOldPen);
			//DeleteObject(hPen);

			//������߿�
			HPEN hPen2=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(128,128,128));
			HGDIOBJ hOldPen2=XDraw_SelectObject_(hDraw,hPen2);
			XDraw_MoveToEx_(hDraw,rect.left,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left,rect.top);
			XDraw_LineTo_(hDraw,rect.right-1,rect.top);
			XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
			//SelectObject(hdc,hOldPen2);
			//DeleteObject(hPen2);
		}
	}else if(STATE_LEAVE==pObj->state)
	{
		rect.top+=2;
		if(pObj->hImage_leave)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			//DeleteObject(hBrush);
		}
	}else if(STATE_STAY==pObj->state)
	{
		if(pObj->hImage_stay)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			//�����ڱ߿�
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);
			//SelectObject(hdc,hOldPen);
			//DeleteObject(hPen);

			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			//DeleteObject(hBrush);
		}
	}else if(STATE_DOWN==pObj->state)
	{
		if(pObj->hImage_down)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);
			//�����ڱ߿�
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);
		//	SelectObject(hdc,hOldPen);
		//	DeleteObject(hPen);

			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
		//	DeleteObject(hBrush);
		}
	}
	Btn_DrawIconAndText(hEle,hDraw,rect);

	return TRUE;
}

BOOL TabBar_Btn_OnDrawLabel_Bottom(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	button_ *pObj=BUTTON(hEle);

	if(pObj->bCheck)
	{
		if(pObj->hImage_check)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);

			//������ǳ��ɫ��
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.top,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.bottom-2);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-2);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top);
			//SelectObject(hdc,hOldPen);
			//DeleteObject(hPen);

			//������߿�
			HPEN hPen2=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(128,128,128));
			HGDIOBJ hOldPen2=XDraw_SelectObject_(hDraw,hPen2);

			XDraw_MoveToEx_(hDraw,rect.left,rect.top,NULL);
			XDraw_LineTo_(hDraw,rect.left,rect.bottom-1);
			XDraw_LineTo_(hDraw,rect.right-1,rect.bottom-1);
			XDraw_LineTo_(hDraw,rect.right-1,rect.top);
			
			//SelectObject(hdc,hOldPen2);
			//DeleteObject(hPen2);
		}
	}else if(STATE_LEAVE==pObj->state)
	{
		rect.bottom-=2;
		if(pObj->hImage_leave)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			//DeleteObject(hBrush);
		}
	}else if(STATE_STAY==pObj->state)
	{
		if(pObj->hImage_stay)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
			//�����ڱ߿�
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.top,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.bottom-2);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-2);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top);

			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			XDraw_DeleteObject_(hDraw,hBrush);
			//DeleteObject(hBrush);
		}
	}else if(STATE_DOWN==pObj->state)
	{
		if(pObj->hImage_down)
		{
			return FALSE;
		}else
		{
			XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);
			//�����ڱ߿�
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(253,183,53));
			HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
			XDraw_MoveToEx_(hDraw,rect.left+1,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left+1,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.top+1);
			XDraw_LineTo_(hDraw,rect.right-2,rect.bottom-1);

			//������߿�
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
			XDraw_FrameRect_(hDraw,&rect,hBrush);
			XDraw_DeleteObject_(hDraw,hBrush);
		//	DeleteObject(hBrush);
		}
	}
	Btn_DrawIconAndText(hEle,hDraw,rect);

	return TRUE;
}

BOOL CALLBACK TabBar_OnDraw_Up(HELE hEle,HDRAW hDraw)   //�����ϰ�ť
{
	button_ *pObj=BUTTON(hEle);
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(STATE_LEAVE==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
	}else if(STATE_STAY==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);

		RECT rc={rect.left+1,rect.top+1,rect.right-1,rect.bottom-1};
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(253,183,53));
		XDraw_FrameRect_(hDraw,&rc,hBrush);
		//DeleteObject(hBrush);
	}else if(STATE_DOWN==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);

		RECT rc={rect.left+1,rect.top+1,rect.right-1,rect.bottom-1};
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(253,183,53));
		XDraw_FrameRect_(hDraw,&rc,hBrush);
		//DeleteObject(hBrush);
	}

	POINT  pt[3];
	pt[0].x=rect.left+5+2;
	pt[0].y=rect.top+7+2;
	pt[1].x=rect.left+10+2;
	pt[1].y=rect.top+2+2;
	pt[2].x=rect.left+10+2;
	pt[2].y=rect.top+13+2;
	HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
	HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(0,0,0));
	XDraw_FillRgn_(hDraw,hRgn,hBrush2);
	//DeleteObject(hRgn);
	//DeleteObject(hBrush2);

	//���Ʊ߿�
	HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
	XDraw_FrameRect_(hDraw,&rect,hBrush);
	//DeleteObject(hBrush);

	return TRUE;
}

BOOL CALLBACK TabBar_OnDraw_Down(HELE hEle,HDRAW hDraw) //�����°�ť
{
	button_ *pObj=BUTTON(hEle);
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(STATE_LEAVE==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);
	}else if(STATE_STAY==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(255,255,255),RGB(210,210,210),&rect,GRADIENT_FILL_RECT_V);

		RECT rc={rect.left+1,rect.top+1,rect.right-1,rect.bottom-1};
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(253,183,53));
		XDraw_FrameRect_(hDraw,&rc,hBrush);
		//DeleteObject(hBrush);
	}else if(STATE_DOWN==pObj->state)
	{
		XDraw_GradientFill2_(hDraw,RGB(210,210,210),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);

		RECT rc={rect.left+1,rect.top+1,rect.right-1,rect.bottom-1};
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(253,183,53));
		XDraw_FrameRect_(hDraw,&rc,hBrush);
		//DeleteObject(hBrush);
	}
	POINT  pt[3];
	pt[0].x=rect.left+5+2;
	pt[0].y=rect.top+2+2;
	pt[1].x=rect.left+5+2;
	pt[1].y=rect.top+12+2;
	pt[2].x=rect.left+10+2;
	pt[2].y=rect.top+7+2;
	HRGN hRgn=XDraw_CreatePolygonRgn_(hDraw,pt,3,ALTERNATE);
	HBRUSH hBrush2=XDraw_CreateSolidBrush_(hDraw,RGB(0,0,0));
	XDraw_FillRgn_(hDraw,hRgn,hBrush2);
	//DeleteObject(hRgn);
	//DeleteObject(hBrush2);

	//���Ʊ߿�
	HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
	XDraw_FrameRect_(hDraw,&rect,hBrush);
	//DeleteObject(hBrush);
	return TRUE;
}

/// @brief ��ť����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XTabBar_SetUp(HELE hEle)    //�����
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pTabBar=(tabBar_*)hEle;
	if(pTabBar->indent>0)
	{
		pTabBar->indent--;
		pTabBar->bAdjust=TRUE;
		XEle_RedrawEle(hEle);
	}
}

/// @brief �Ұ�ť����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XTabBar_SetDown(HELE hEle)  //�ҹ���
{
	IsTabBarDebug(hEle,__FUNCTION__);
	tabBar_ *pTabBar=(tabBar_*)hEle;
	int count=XArray_GetCount(pTabBar->hArrayList);
	if(count<=0) return;

	if(pTabBar->indent<(count-1))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(pTabBar->hArrayList,count-1);
		if(FALSE==XEle_IsShowEle(pItem->hButton))
		{
			pTabBar->indent++;
			pTabBar->bAdjust=TRUE;
			XEle_RedrawEle(hEle);
		}
	}
}

BOOL CALLBACK TabBar_OnEventBtnClick_Up(HELE hEle,HELE hEventEle) //��ť�¼�
{
	if(hEle!=hEventEle)
		return FALSE;

	XTabBar_SetUp((HELE)((ele_*)hEle)->pParentEle);
	return FALSE;
}

BOOL CALLBACK TabBar_OnEventBtnClick_Down(HELE hEle,HELE hEventEle) //��ť�¼�
{
	if(hEle!=hEventEle)
		return FALSE;

	XTabBar_SetDown((HELE)((ele_*)hEle)->pParentEle);
	return FALSE;
}

BOOL CALLBACK TabBar_OnEventBtnClick(HELE hEle,HELE hEventEle) //��ǩѡ��
{
	if(hEle==hEventEle)
	{
		tabBar_ *pLabel=(tabBar_*)XEle_GetParentEle(hEle);

		int count=XArray_GetCount(pLabel->hArrayList);
		for(int i=0;i<count;i++)
		{
			tabBar_item_  *pItem=(tabBar_item_*)XArray_GetAt(pLabel->hArrayList,i);
			if( pItem->hButton==hEle )
			{
				if(pLabel->pSelectItem->hButton!=hEle)
				{
					XBtn_SetCheck(pLabel->pSelectItem->hButton,FALSE);
					if(pLabel->pSelectItem->hPage)
					{
						XEle_ShowEle(pLabel->pSelectItem->hPage,FALSE);
						//��������Ԫ��
						RECT rect;
						XEle_GetClientRect(pLabel->pSelectItem->hPage,&rect);
						XEle_RectToNCWnd(pLabel->pSelectItem->hPage,&rect);
						XWnd_RedrawWndRect(XEle_GetHWindow(hEle),&rect);
					}
					
					pLabel->pSelectItem=pItem;
					XBtn_SetCheck(hEle,TRUE);
					if(pItem->hPage)
					{
						XEle_ShowEle(pItem->hPage,TRUE);
						XEle_RedrawEle(pLabel->pSelectItem->hPage);
					}
					
					Ele_SendEvent((HELE)pLabel,XE_TABBAR_SELECT,i,0);
					XEle_RedrawEle((HELE)pLabel);
				}
				break;
			}
		}
	}
	return FALSE;
}

void CALLBACK TabBar_OnDestroy(HELE hEle) //����
{
	int count=XArray_GetCount(((tabBar_*)hEle)->hArrayList);
	void  *pItem=NULL;
	for(int i=0;i<count;i++)
	{
		pItem=Array_GetAt(((tabBar_*)hEle)->hArrayList,i);
		free(pItem);
	}
	XArray_Destroy(((tabBar_*)hEle)->hArrayList);
}

BOOL CALLBACK TabBar_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		tabBar_ *pObject=(tabBar_*)hEle;

		RECT rect;
		XEle_GetClientRect(hEle,&rect);

		pObject->height=rect.bottom-rect.top;

		TabBar_Adjust(hEle);

		//����������ťλ�� 
		RECT rcButton; //20*20
		rcButton.top=pObject->height-22;
		rcButton.bottom=rcButton.top+20;
		rcButton.right=rect.right;
		rcButton.left=rcButton.right-20;
		
		XEle_SetRect(pObject->hBtnDown,&rcButton);

		rcButton.right=rcButton.left;
		rcButton.left=rcButton.right-20;
		XEle_SetRect(pObject->hBtnUp,&rcButton);
	}
	return FALSE;
}

///@}