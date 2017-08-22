/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup propertyPage ����ҳԪ��(PropertyPage)
/// @ingroup groupElements
/// @{

/// @brief ��������ҳԪ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XPPage_Create(int x, int y, int cx, int cy,HXCGUI hParent) //������ť
{
	propertyPage_ *pObj=(propertyPage_*)malloc(sizeof(propertyPage_));
	memset(pObj,0,sizeof(propertyPage_));

	PPage_Init((HELE)pObj,x,y,cx,cy,XC_PROPERTYPAGE,hParent);
	return (HELE)pObj;
}

void PPage_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_PROPERTYPAGE);
	propertyPage_ *pObj=PPAGE(hEle);
	pObj->height=25;
	pObj->widthBtn=45;
	pObj->hArrayList=XArray_Create();
	pObj->spacing=1;
	pObj->bScrollButton=TRUE;

	pObj->hBtnUp=XBtn_Create(cx-39,pObj->height-22,20,20,L"<<");
	XEle_AddEle(hEle,pObj->hBtnUp);

	pObj->hBtnDown=XBtn_Create(cx-20,pObj->height-22,20,20,L">>");
	XEle_AddEle(hEle,pObj->hBtnDown);

	XEle_ShowEle(pObj->hBtnUp,FALSE);
	XEle_ShowEle(pObj->hBtnDown,FALSE);

	XEle_RegisterMessage(hEle,XM_PAINT,PPage_OnDraw);
	XEle_RegisterEvent(hEle,XE_SIZE,PPage_OnEventSize);

	XEle_RegisterMessage(pObj->hBtnUp,XM_PAINT,PPage_OnDraw_Up);
	XEle_RegisterMessage(pObj->hBtnDown,XM_PAINT,PPage_OnDraw_Down);
	XEle_RegisterEvent(pObj->hBtnUp,XE_BNCLICK,PPage_OnEventBtnClick_Up);
	XEle_RegisterEvent(pObj->hBtnDown,XE_BNCLICK,PPage_OnEventBtnClick_Down);
	XEle_RegisterEvent(hEle,XE_DESTROY,PPage_OnDestroy);
}

void CALLBACK PPage_OnDestroy(HELE hEle) //����
{
	int count=XArray_GetCount(PPAGE(hEle)->hArrayList);
	void  *pItem=NULL;
	for(int i=0;i<count;i++)
	{
		pItem=Array_GetAt(PPAGE(hEle)->hArrayList,i);
		free(pItem);
	}
	XArray_Destroy(PPAGE(hEle)->hArrayList);
}

/// @brief ���һ����ǩ.
/// @param hEle Ԫ�ؾ��.
/// @param pName  ��ǩ��.
/// @param hPage  �󶨵���ҳ��Ԫ��.
/// @return ��ǩ����.
int WINAPI XPPage_AddLabel(HELE hEle,wchar_t *pName,HELE hPage) //���һ����ǩ
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(hPage)
	{
		IsEleDebug(hPage,__FUNCTION__);
		if(NULL==((ele_*)hPage)->pParentEle)
		{
			XEle_AddEle(hEle,hPage);
		}
	}

	propertyPage_item_ *pItem=PPage_AddLabel(hEle,pName,hPage);
	XArray_Add(PPAGE(hEle)->hArrayList,pItem);
	PPAGE(hEle)->bAdjust=TRUE;
	return Array_GetCount(PPAGE(hEle)->hArrayList)-1;
}

/// @brief ����һ����ǩ.
/// @param hEle Ԫ�ؾ��.
/// @param index  ����λ������.
/// @param pName  ��ǩ��.
/// @param hPage  �󶨵���ҳ��Ԫ��.
/// @return ��ǩ����.
int WINAPI XPPage_InsertLabel(HELE hEle,int index,wchar_t *pName,HELE hPage)//����һ����ǩ
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(hPage)
	{
		IsEleDebug(hPage,__FUNCTION__);
	}

	propertyPage_item_ *pItem=PPage_AddLabel(hEle,pName,hPage);
	XArray_insert(PPAGE(hEle)->hArrayList,pItem,index);
	PPAGE(hEle)->bAdjust=TRUE;

	return index;
}

propertyPage_item_* PPage_AddLabel(HELE hEle,wchar_t *pName,HELE hPage)
{
	propertyPage_item_  *pItem=(propertyPage_item_*)malloc(sizeof(propertyPage_item_));
	memset(pItem,0,sizeof(propertyPage_item_));

	pItem->hButton=XPPageBtn_Create(0,0,10,10,pName,hEle);
	pItem->hPage=hPage;

	if(hPage && NULL==((ele_*)hPage)->pParentEle)
	{
		XEle_AddEle(hEle,hPage);
	}

	//XEle_RegisterMessage(pItem->hButton,XM_PAINT,PPage_OnDrawLabel);
	XEle_RegisterEvent(pItem->hButton,XE_BNCLICK,PPage_OnEventBtnClick);
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

	if(NULL==PPAGE(hEle)->pSelectItem)
	{
		PPAGE(hEle)->pSelectItem=pItem;
		XBtn_SetCheck(pItem->hButton,TRUE);
	}

	if(hPage)
	{
		//����ҳ��С
		RECT rc;
		XEle_GetClientRect(hEle,&rc);
		rc.top=PPAGE(hEle)->height;
		rc.left++;
		rc.right--;
		rc.bottom--;
		XEle_SetRect(hPage,&rc);
	}
	return pItem;
}

/// @brief ����ͼԪ�ص���ǩ.
/// @param hEle Ԫ�ؾ��.
/// @param index  ��ǩ����.
/// @param hPage  Ҫ�󶨵���ͼԪ��.
/// @return ����ɹ�����TRUE,�����෴.
BOOL WINAPI XPPage_SetBindEle(HELE hEle,int index,HELE hPage)
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	IsEleDebug(hPage,__FUNCTION__);

	propertyPage_ *pObj=PPAGE(hEle);
	if(index<0 || index>= Array_GetCount(pObj->hArrayList))
		return FALSE;

	if(NULL==((ele_*)hPage)->pParentEle)
	{
		XEle_AddEle(hEle,hPage);
	}

	propertyPage_item_ *pItem=(propertyPage_item_*)Array_GetAt(pObj->hArrayList,index);
	pItem->hPage=hPage;

	
	if(pItem==pObj->pSelectItem)
	{
		XEle_ShowEle(hPage,TRUE);
	}else
	{
		XEle_ShowEle(hPage,FALSE);
	}
	pObj->bAdjust=TRUE;
	return TRUE;
}

/// @brief ���ñ�ǩ�߶�.
/// @param hEle  Ԫ�ؾ��.
/// @param height ��ǩ�߶�.
void WINAPI XPPage_SetLabelHeight(HELE hEle,int height) //���ñ�ǩ�߶�
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	PPAGE(hEle)->height=height;
	XPPage_Adjust(hEle);
	XEle_RedrawEle(hEle);
}

/// @brief ����ָ����ǩ���.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩ����.
/// @param width ��ǩ���.
void WINAPI XPPage_SetLabelWidth(HELE hEle,int index,int width)  //���ñ�ǩ���
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	propertyPage_ *pObj=PPAGE(hEle);
	int count=XArray_GetCount(pObj->hArrayList);
	if(index>=0 && index<count)
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(pObj->hArrayList,index);
		pItem->widthUser=width;
		pObj->bAdjust=TRUE;
	}
}

/// @brief ��ȡָ����ǩ���.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩ����.
/// @return  ���ر�ǩ���.
int  WINAPI XPPage_GetLabelWidth(HELE hEle,int index)  //��ȡ��ǩ���
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	propertyPage_ *pObj=PPAGE(hEle);
	int count=XArray_GetCount(pObj->hArrayList);
	if(index>=0 && index<count)
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(pObj->hArrayList,index);
		return pItem->widthUser;
	}
	return -1;
}

/// @brief ��ȡ��ǩ������.
/// @param hEle  Ԫ�ؾ��.
/// @return  ��ǩ������.
int  WINAPI XPPage_GetLabelCount(HELE hEle) //��ȡ��ǩ������
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	return XArray_GetCount(PPAGE(hEle)->hArrayList);
}

/// @brief ����ѡ���ǩ.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������.
/// @param reDraw �Ƿ��ػ�.
void WINAPI XPPage_SetSelect(HELE hEle,int index,BOOL reDraw)  //����ѡ���ǩ
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(index<0 || index>=Array_GetCount(PPAGE(hEle)->hArrayList))
		return ;

	propertyPage_item_ *pNewSel=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,index);
	if(PPAGE(hEle)->pSelectItem !=pNewSel)
	{
		if(PPAGE(hEle)->pSelectItem)
		{
			if(PPAGE(hEle)->pSelectItem->hPage)
				XEle_ShowEle(PPAGE(hEle)->pSelectItem->hPage,FALSE);
			XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton,FALSE);
		}
		PPAGE(hEle)->pSelectItem=pNewSel;
		if(PPAGE(hEle)->pSelectItem->hPage)
			XEle_ShowEle(PPAGE(hEle)->pSelectItem->hPage,TRUE);
		XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton,TRUE);

		if(FALSE==XEle_IsShowEle(pNewSel->hButton))
		{
			PPAGE(hEle)->indent=index;
			PPAGE(hEle)->bAdjust=TRUE;
		}
		Ele_SendEvent(hEle,XE_PPAGE_SELECT,index,0);
		
		if(reDraw)
			XEle_RedrawEle(hEle);
	}
}

/// @brief ���ñ�ǩ�ı�.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������.
/// @param pText �ı�����.
void WINAPI XPPage_SetLabelText(HELE hEle,int index,wchar_t *pText)  //����
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(NULL == pText) return ;

	if(pText && index>=0 && index<Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,index);

		SIZE size;    //�ַ�����
		HDC hdc=GetDC(NULL);
		HGDIOBJ hOldFont=SelectObject(hdc,XFont_GetHFONT(((ele_*)pItem->hButton)->hFontX));
		GetTextExtentPoint32(hdc,pText,wcslen(pText),&size);
		SelectObject(hdc,hOldFont);
		ReleaseDC(NULL,hdc);
		pItem->width=size.cx+10;

		XBtn_SetText(pItem->hButton,pText);
		PPAGE(hEle)->bAdjust=TRUE;
		XEle_RedrawEle(hEle);
	}
}

/// @brief ��ȡѡ��ı�ǩ����.
/// @param hEle  Ԫ�ؾ��.
/// @return ��ǩλ������.
int WINAPI XPPage_GetSelect(HELE hEle) //��ȡѡ��ı�ǩ
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(PPAGE(hEle)->pSelectItem)
	{
		propertyPage_item_  *pItem=NULL;
		int count=XArray_GetCount(PPAGE(hEle)->hArrayList);
		for(int i=0;i<count;i++)
		{
			pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,i);
			if(PPAGE(hEle)->pSelectItem==pItem)
			{
				return i;
			}
		}
	}
	return -1;
}

/// @brief ��ȡ��ǩ�߶�.
/// @param hEle  Ԫ�ؾ��.
/// @return ��ǩ�߶�.
int WINAPI XPPage_GetLabelHeight(HELE hEle) //��ȡ��ǩ�߶�
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	return PPAGE(hEle)->height;
}

/// @brief ��ȡ��ǩ�ı�.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������
/// @return �ı�����.
wchar_t* WINAPI XPPage_GetLabelText(HELE hEle,int index)  //��ȡ�ı�
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(index>=0 && index< Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,index);
		return XBtn_GetText(pItem->hButton);
	}
	return NULL;
}

/// @brief ��ȡ��ǩ��ť.���ذ�ť�������ΪButton.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������
/// @return ��ǩ��ť���.
HELE WINAPI XPPage_GetLabel(HELE hEle,int index) //��ȡ��ǩ��ť
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(index>=0 && index< Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,index);
		return pItem->hButton;
	}
	return NULL;
}

/// @brief ��ȡ��ǩ��Ӧ��ҳ.
/// @param hEle  Ԫ�ؾ��.
/// @param index ��ǩλ������
/// @return �󶨵�ҳԪ��.
HELE WINAPI XPPage_GetLabelPage(HELE hEle,int index) 
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(index>=0 && index< Array_GetCount(PPAGE(hEle)->hArrayList))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,index);
		return pItem->hPage;
	}
	return NULL;
}

/// @brief ��ȡ����ҳԪ�ذ󶨵�ҳԪ��,��Ӧ��ǩ����0������ֵ.
/// @param hEle  Ԫ�ؾ��.
/// @param hPage ����ҳԪ�ذ󶨵�ҳԪ�ؾ��
/// @return ҳ��Ӧ��ǩλ������ֵ.
int WINAPI XPPage_GetPageIndex(HELE hEle,HELE hPage) //������ҳ��Ӧ��ǩ����
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	IsEleDebug(hPage,__FUNCTION__);
	int count=XArray_GetCount(PPAGE(hEle)->hArrayList);
	for(int i=0;i<count;i++)
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,i);
		if(hPage==pItem->hPage)
		{
			return i;
		}
	}
	return -1;
}

/// @brief ��ȡ����ҳ��ǩ��ťԪ��λ������ֵ.
/// @param hEle  Ԫ�ؾ��.
/// @param hLabel ��ǩ��ťԪ�ؾ��.
/// @return ��ǩλ������ֵ.
int WINAPI XPPage_GetLabelIndex(HELE hEle,HELE hLabel) //��ȡ����ҳ��ǩ��ťԪ��λ������ֵ
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	IsButtonDebug(hLabel,__FUNCTION__);
	int count=XArray_GetCount(PPAGE(hEle)->hArrayList);
	for(int i=0;i<count;i++)
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,i);
		if(hLabel==pItem->hButton)
		{
			return i;
		}
	}
	return -1;
}

/// @brief ɾ��ָ����ǩ.
/// @param hEle  Ԫ�ؾ��.
/// @param index Ҫɾ���ı�ǩλ������
/// @param deletePage �������ΪTRUE,ͬʱɾ���ñ�ǩ�󶨵�ҳ,��������ҳ,�����෴.
void WINAPI XPPage_DeleteLabel(HELE hEle,int index,BOOL deletePage) //ɾ��
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	int count=Array_GetCount(PPAGE(hEle)->hArrayList);
	if(index>=0 && index<count)
	{
		propertyPage_item_ *pDel=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,index);
		XArray_DeleteIndex(PPAGE(hEle)->hArrayList,index);
		count--;
		XEle_Destroy(pDel->hButton);
		if(deletePage)
		{
			if(pDel->hPage)	XEle_Destroy(pDel->hPage);
		}

		if(PPAGE(hEle)->pSelectItem==pDel)
		{
			if(index>=count) index--;

			if(index>=0)
			{
				PPAGE(hEle)->pSelectItem=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,index);
				XBtn_SetCheck(PPAGE(hEle)->pSelectItem->hButton,TRUE);
				
				Ele_SendEvent(hEle,XE_PPAGE_SELECT,index,0);
			}else
			{	
				PPAGE(hEle)->pSelectItem=NULL;
				Ele_SendEvent(hEle,XE_PPAGE_SELECT,-1,0);
			}
			PPage_OnEventSize(hEle,hEle);
		}
		free(pDel);
		PPAGE(hEle)->bAdjust=TRUE;
		XEle_RedrawEle(hEle);
	}
}

/// @brief ɾ�����б�ǩ.
/// @param hEle  Ԫ�ؾ��.
/// @param deletePage �������ΪTRUE,ͬʱɾ���ñ�ǩ�󶨵�ҳ,��������ҳ,�����෴.
void WINAPI XPPage_DeleteLabelAll(HELE hEle,BOOL deletePage) //ɾ������PPAGE
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	int count=Array_GetCount(PPAGE(hEle)->hArrayList);
	propertyPage_item_ *pDel=NULL;
	for(int i=0;i<count;i++)
	{
		pDel=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,i);
		XEle_Destroy(pDel->hButton);
		if(deletePage)
		{
			if(pDel->hPage)	XEle_Destroy(pDel->hPage);
		}
		free(pDel);
	}
	XArray_DeleteAll(PPAGE(hEle)->hArrayList);

	if(PPAGE(hEle)->pSelectItem)
	{
		PPAGE(hEle)->pSelectItem=NULL;
		Ele_SendEvent(hEle,XE_PPAGE_SELECT,-1,0);
	}
	PPAGE(hEle)->indent=0;
	PPAGE(hEle)->bAdjust=TRUE;
	XEle_RedrawEle(hEle);
}

/// @brief ���û�رչ�����ť.
/// @param hEle  Ԫ�ؾ��.
/// @param bEnable TRUE����,�����෴.
void WINAPI XPPage_EnableScrollButton(HELE hEle,BOOL bEnable) //�Ƿ���ʾ������ť
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(PPAGE(hEle)->bScrollButton!=bEnable)
	{
		PPAGE(hEle)->bScrollButton=bEnable;
		XEle_ShowEle(PPAGE(hEle)->hBtnUp,FALSE);
		XEle_ShowEle(PPAGE(hEle)->hBtnDown,FALSE);
		XPPage_Adjust(hEle);
	}
}

/// @brief ���ñ�ǩ���ǩ֮��ļ��.
/// @param hEle  Ԫ�ؾ��.
/// @param spacing �����С.
void WINAPI XPPage_SetLabelSpacing(HELE hEle,int spacing)
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	((propertyPage_*)hEle)->spacing=spacing;
	((propertyPage_*)hEle)->bAdjust=TRUE;
}

/// @brief ��ȡ��ǩ���ǩ֮��ļ��.
/// @param hEle  Ԫ�ؾ��.
/// @return �����С.
int WINAPI XPPage_GetLabelSpacing(HELE hEle)
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	return ((propertyPage_*)hEle)->spacing;
}

/// @brief ����ҳԪ�ص�������.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XPPage_Adjust(HELE hEle)
{	
	IsPropertyPageDebug(hEle,__FUNCTION__);
	propertyPage_ *pObj=PPAGE(hEle);
	pObj->bAdjust=FALSE;

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	int width=0;//TAB��ť����������
	int count=Array_GetCount(pObj->hArrayList); 
	int index=0;

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

	if(pObj->bScrollButton)
		width=rect.right-rect.left-pObj->widthBtn;
	else
		width=rect.right-rect.left;

	propertyPage_item_ *pItem=NULL;
	for(;index<pObj->indent;index++) //���ز���ʾ��tab
	{
		pItem=(propertyPage_item_*)Array_GetAt(pObj->hArrayList,index);
		XEle_ShowEle(pItem->hButton,FALSE);
	}

	RECT rcItem;
	int left=0;
	int  tabWidth=0;
	for(;index<count;index++)
	{
		pItem=(propertyPage_item_*)Array_GetAt(pObj->hArrayList,index);

		if(0==pItem->widthUser)
			tabWidth=pItem->width;
		else
			tabWidth=pItem->widthUser;

		if((left+tabWidth)>width)
			break;

		rcItem.left=left;
		rcItem.top=0;
		rcItem.right=left+tabWidth;
		rcItem.bottom=pObj->height;
		XEle_SetRect(pItem->hButton,&rcItem);
		if(pItem->hPage)
		{
			if(pObj->pSelectItem==pItem)
			{
				XEle_ShowEle(pItem->hPage,TRUE);
			}else
			{
				XEle_ShowEle(pItem->hPage,FALSE);
			}
		}
		XEle_ShowEle(pItem->hButton,TRUE);

		left+=tabWidth;
		left+=pObj->spacing;
	}

	//����������ť
	if(pObj->bScrollButton)
	{
		if(0!=pObj->indent || index!=count)
		{
			XEle_ShowEle(pObj->hBtnUp,TRUE);
			XEle_ShowEle(pObj->hBtnDown,TRUE);
		}else
		{
			XEle_ShowEle(pObj->hBtnUp,FALSE);
			XEle_ShowEle(pObj->hBtnDown,FALSE);
		}
		//����������ťλ��
		RECT rcButton; //20*20
		rcButton.top=PPAGE(hEle)->height-22;
		rcButton.bottom=rcButton.top+20;
		rcButton.right=rect.right;
		rcButton.left=rcButton.right-20;

		XEle_SetRect(PPAGE(hEle)->hBtnDown,&rcButton);

		rcButton.right=rcButton.left;
		rcButton.left=rcButton.right-20;
		XEle_SetRect(PPAGE(hEle)->hBtnUp,&rcButton);
	}

	for(;index<count;index++) //���ز���ʾ��tab
	{
		pItem=(propertyPage_item_*)Array_GetAt(pObj->hArrayList,index);
		XEle_ShowEle(pItem->hButton,FALSE);
	}

	//����ҳ��С
	{
		rect.top=PPAGE(hEle)->height;
		rect.left++;
		rect.right--;
		rect.bottom--;

		propertyPage_item_ *pItem=NULL;
		int count=Array_GetCount(PPAGE(hEle)->hArrayList);
		for(int i=0;i<count;i++)
		{
			pItem=(propertyPage_item_*)Array_GetAt(PPAGE(hEle)->hArrayList,i);
			if(pItem->hPage)
			{
				XEle_SetRect(pItem->hPage,&rect);
			}
		}
	}
}

/// @brief ��ť����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XPPage_SetUp(HELE hEle)  //�����
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	if(PPAGE(hEle)->indent>0)
	{
		PPAGE(hEle)->indent--;
		PPAGE(hEle)->bAdjust=TRUE;
		XEle_RedrawEle(hEle);
	}
//	OutputDebugStringA("�����\n");
}

/// @brief �Ұ�ť����.
/// @param hEle  Ԫ�ؾ��.
void WINAPI XPPage_SetDown(HELE hEle) //�ҹ���
{
	IsPropertyPageDebug(hEle,__FUNCTION__);
	int count=XArray_GetCount(PPAGE(hEle)->hArrayList);
	if(count<=0) return;

	if(PPAGE(hEle)->indent<(count-1))
	{
		propertyPage_item_ *pItem=(propertyPage_item_*)XArray_GetAt(PPAGE(hEle)->hArrayList,count-1);
		if(FALSE==XEle_IsShowEle(pItem->hButton))
		{
			PPAGE(hEle)->indent++;
			PPAGE(hEle)->bAdjust=TRUE;
			XEle_RedrawEle(hEle);
		}
	}
//	OutputDebugStringA("�ҹ���\n");
}

BOOL CALLBACK PPage_OnEventBtnClick_Up(HELE hEle,HELE hEventEle) //��ť�¼�
{
	if(hEle!=hEventEle)
		return FALSE;

	XPPage_SetUp((HELE)((ele_*)hEle)->pParentEle);
	return TRUE;
}

BOOL CALLBACK PPage_OnEventBtnClick_Down(HELE hEle,HELE hEventEle) //��ť�¼�
{
	if(hEle!=hEventEle)
		return FALSE;

	XPPage_SetDown((HELE)((ele_*)hEle)->pParentEle);
	return TRUE;
}

BOOL CALLBACK PPage_OnDraw(HELE hEle,HDRAW hDraw)
{
	propertyPage_ *pObj=PPAGE(hEle);
	if(pObj->bAdjust)
	{
		XPPage_Adjust(hEle);
	}

	RECT rectEle;
	XEle_GetClientRect(hEle,&rectEle);

	if(((ele_*)hEle)->bBorder)
	{
		rectEle.top=pObj->height-1;
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,((ele_*)hEle)->borderColor);
		XDraw_FrameRect_(hDraw,&rectEle,hBrush);
		//DeleteObject(hBrush);
	}
	return TRUE;
}

BOOL CALLBACK PPage_OnEventSize(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		XPPage_Adjust(hEle);
	}
	return FALSE;
}

BOOL CALLBACK PPage_OnDraw_Up(HELE hEle,HDRAW hDraw)   //�����ϰ�ť
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
//		DeleteObject(hBrush);
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
//	DeleteObject(hRgn);
//	DeleteObject(hBrush2);

	//���Ʊ߿�
	HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
	XDraw_FrameRect_(hDraw,&rect,hBrush);
//	DeleteObject(hBrush);

	return TRUE;
}

BOOL CALLBACK PPage_OnDraw_Down(HELE hEle,HDRAW hDraw) //�����°�ť
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
//	DeleteObject(hRgn);
//	DeleteObject(hBrush2);

	//���Ʊ߿�
	HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(128,128,128));
	XDraw_FrameRect_(hDraw,&rect,hBrush);
//	DeleteObject(hBrush);
	return TRUE;
}

BOOL CALLBACK PPage_OnEventBtnClick(HELE hEle,HELE hEventEle) //��ǩѡ��
{
	if(hEle==hEventEle)
	{
		propertyPage_ *pLabel=(propertyPage_*)XEle_GetParentEle(hEle);

		int count=XArray_GetCount(pLabel->hArrayList);
		for(int i=0;i<count;i++)
		{
			propertyPage_item_  *pItem=(propertyPage_item_*)XArray_GetAt(pLabel->hArrayList,i);
			if( pItem->hButton==hEle )
			{
				if(pLabel->pSelectItem->hButton!=hEle)
				{
					if(pLabel->pSelectItem->hPage)
						XEle_ShowEle(pLabel->pSelectItem->hPage,FALSE);
					XBtn_SetCheck(pLabel->pSelectItem->hButton,FALSE);

					if(pItem->hPage)
						XEle_ShowEle(pItem->hPage,TRUE);
					XBtn_SetCheck(hEle,TRUE);
					pLabel->pSelectItem=pItem;

					Ele_SendEvent((HELE)pLabel,XE_PPAGE_SELECT,i,0);
					XEle_RedrawEle((HELE)pLabel);
				}
				break;
			}
		}
	}
	return TRUE;
}

///@}


//////////////////////////////////////////////////////////////////////////////
HELE XPPageBtn_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent)
{
	button_ *pNew=(button_*)malloc(sizeof(button_));
	memset(pNew,0,sizeof(button_));

	PPageBtn_Init((HELE)pNew,x,y,cx,cy,XC_PROPERTYPAGE_LABEL,pTitle,hParent);

	return (HELE)pNew;
}

void PPageBtn_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent)
{
	Btn_Init(hEle,x,y,cx,cy,eleType,pTitle,hParent);

	AddTypeDebug(hEle,XC_PROPERTYPAGE_LABEL);

	XEle_EnableFocus(hEle,FALSE);
	XEle_RegisterMessage(hEle,XM_PAINT,PPageBtn_OnDrawLabel);
}


BOOL CALLBACK PPageBtn_OnDrawLabel(HELE hEle,HDRAW hDraw)
{
	button_ *pObj=BUTTON(hEle);
	if(pObj->hImage_leave || pObj->hImage_stay || pObj->hImage_down
		|| pObj->hImage_check ||pObj->hImage_disable || pObj->hImage_icon)
	{
		Btn_OnDraw(hEle,hDraw);
		return TRUE;
	}

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

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
		//	SelectObject(hdc,hOldPen);
		//	DeleteObject(hPen);

			//������߿�
			HPEN hPen2=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(128,128,128));
			HGDIOBJ hOldPen2=XDraw_SelectObject_(hDraw,hPen2);
			XDraw_MoveToEx_(hDraw,rect.left,rect.bottom-1,NULL);
			XDraw_LineTo_(hDraw,rect.left,rect.top);
			XDraw_LineTo_(hDraw,rect.right-1,rect.top);
			XDraw_LineTo_(hDraw,rect.right-1,rect.bottom);
		//	SelectObject(hdc,hOldPen2);
		//	DeleteObject(hPen2);
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
			//DeleteObject(hBrush);
		}
	}

	Btn_DrawIconAndText(hEle,hDraw,rect);
	return TRUE;
}