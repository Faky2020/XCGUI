/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"
#include "imageList.h"

/// @defgroup imageList ͼƬ�б�
/// @ingroup groupOther
/// ͼƬ�б�����������ͼƬ,���ɾ����ʾ��,��ͼƬ�б������һ��UIԪ�غ�,�����Զ����ٽӿھ��,������Ҫ�����ֶ�����ͼƬ�б���.
/// @{

/// @brief ����ͼƬ�б�.
/// @param cx ͼƬ���.
/// @param cy ͼƬ�߶�.
/// @return ͼƬ�б���.
HXCGUI WINAPI XImageList_Create(int cx,int cy)
{
	int len=sizeof(imageList_);
	imageList_  *pObject =(imageList_*)malloc(sizeof(imageList_));
	memset(pObject,0,sizeof(imageList_));
	pObject->size.cx=cx;
	pObject->size.cy=cy;
	pObject->bFixedSize=TRUE;
	pObject->hArrayImage=XArray_Create();
	pObject->refCount=0;

	((object_*)pObject)->type=XC_IMAGELIST;
	return pObject;
}

/// @brief ͼƬ�б�����.
/// @param hImageList ͼƬ�б���.
void WINAPI XImageList_Destroy(HXCGUI hImageList)  //����
{
	IsImageListDebug(hImageList,__FUNCTION__);
	imageList_ *pObj=(imageList_*)hImageList;
	
	if(1==pObj->refCount)
	{
		XImageList_DeleteAll(pObj);
		//int count=Array_GetCount(pObj->hArrayImage);
		XArray_Destroy(pObj->hArrayImage);
		free(hImageList);
	}else
		pObj->refCount--;
}

/// @brief ���ͼƬ.
/// @param hImageList ͼƬ�б���.
/// @param hImage  ͼƬ���.
void WINAPI XImageList_AddImage(HXCGUI hImageList,HIMAGE hImage) //���ͼƬ���ļ�
{
	IsImageListDebug(hImageList,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
		imageListItem_ *pNew=(imageListItem_*)malloc(sizeof(imageListItem_));
		pNew->hImage=Image_AddRef(hImage);
		XArray_Add(((imageList_*)hImageList)->hArrayImage,pNew);
	}
}

/// @brief ��ȡͼƬ�߶�.
/// @param hImageList ͼƬ�б���.
/// @return ͼƬ�߶�.
int  WINAPI XImageList_GetWidth(HXCGUI hImageList)
{
	IsImageListDebug(hImageList,__FUNCTION__);
	return ((imageList_*)hImageList)->size.cx;
}

/// @brief ��ȡͼƬ���.
/// @param hImageList ͼƬ�б���.
/// @return ͼƬ���.
int  WINAPI XImageList_GetHeight(HXCGUI hImageList)
{
	IsImageListDebug(hImageList,__FUNCTION__);
	return ((imageList_*)hImageList)->size.cy;
}

/// @brief ��ȡͼƬ�б���ͼƬ����.
/// @param hImageList ͼƬ�б���.
/// @return ͼƬ�б���ͼƬ����.
int  WINAPI XImageList_GetCount(HXCGUI hImageList)   //��ȡͼƬ����
{
	IsImageListDebug(hImageList,__FUNCTION__);
	return XArray_GetCount(((imageList_*)hImageList)->hArrayImage);
}

/// @brief ��ȡͼƬ.
/// @param hImageList ͼƬ�б���.
/// @param index ͼƬ����.
/// @return ͼƬ���.
HIMAGE WINAPI XImageList_GetImage(HXCGUI hImageList,int index) //��ȡͼƬ
{
	IsImageListDebug(hImageList,__FUNCTION__);
	if(index<0) return NULL;

	int count= XArray_GetCount(((imageList_*)hImageList)->hArrayImage);
	if(index>=count) return NULL;

	imageListItem_ *pItem=(imageListItem_*)XArray_GetAt(((imageList_*)hImageList)->hArrayImage,index);
	if(pItem)
		return pItem->hImage;

	return NULL;
}

/// @brief ɾ��ͼƬ�б���,ָ������λ�õ�ͼƬ.
/// @param hImageList ͼƬ�б���.
/// @param index  Ҫɾ����ͼƬλ������.
void WINAPI XImageList_DeleteIndex(HXCGUI hImageList,int index)//ɾ��ָ��ͼƬ
{
	IsImageListDebug(hImageList,__FUNCTION__);
	imageList_ *pImageList=(imageList_*)hImageList;

	imageListItem_ *pItem=(imageListItem_*)Array_GetAt(pImageList->hArrayImage,index);
	if(pItem)
	{
		XImage_Destroy(pItem->hImage);
		free(pItem);
	}
	XArray_DeleteIndex(pImageList->hArrayImage,index);
}

/// @brief ��ͼƬ�б���ɾ��ȫ��ͼƬ.
/// @param hImageList ͼƬ�б���.
void WINAPI XImageList_DeleteAll(HXCGUI hImageList) //ɾ��ȫ��ͼƬ
{
	IsImageListDebug(hImageList,__FUNCTION__);
	imageList_ *pImageList=(imageList_*)hImageList;

	int count=Array_GetCount(pImageList->hArrayImage);
	for(int i=0;i<count;i++)
	{
		imageListItem_ *pItem=(imageListItem_*)Array_GetAt(pImageList->hArrayImage,i);
		XImage_Destroy(pItem->hImage);
		free(pItem);
	}
	XArray_DeleteAll(pImageList->hArrayImage);
}

/// @brief ����ͼƬ.
/// @param hImageList ͼƬ�б���.
/// @param hDraw   ��ͼ���.
/// @param index  ͼƬ����.
/// @param x   ��ʾλ��x����.
/// @param y   ��ʾλ��y����.
void WINAPI XImageList_DrawImage(HXCGUI hImageList,HDRAW hDraw,int index, int x, int y)
{
	IsImageListDebug(hImageList,__FUNCTION__);

	imageList_ *pObject=(imageList_*)hImageList;
	if(index>=0 && index<Array_GetCount(pObject->hArrayImage))
	{
		imageListItem_ *pItem=Array_GetAtImage(pObject->hArrayImage,index);
		if(pObject->bFixedSize)
		{
			XDraw_HImageStretch_(hDraw,pItem->hImage,x,y,pObject->size.cx,pObject->size.cy);
		}else
		{
			int width=XImage_GetWidth(pItem->hImage);
			int height=XImage_GetHeight(pItem->hImage);

			XDraw_HImageStretch_(hDraw,pItem->hImage,
				x+(pObject->size.cx-width)/2,
				y+(pObject->size.cy-height)/2,
				width,height);
		}
	}
}

/// @brief ����ͼƬ,ָ����С.
/// @param hImageList ͼƬ�б���.
/// @param hDraw   ��ͼ���.
/// @param index  ͼƬ����.
/// @param pRect  ����.
void WINAPI XImageList_DrawImage2(HXCGUI hImageList,HDRAW hDraw,int index, RECT *pRect)
{
	IsImageListDebug(hImageList,__FUNCTION__);

	imageList_ *pObject=(imageList_*)hImageList;
	if(index>=0 && index<Array_GetCount(pObject->hArrayImage))
	{
		imageListItem_ *pItem=Array_GetAtImage(pObject->hArrayImage,index);
		XDraw_HImageStretch_(hDraw,pItem->hImage,pRect->left,pRect->top,pRect->right-pRect->left,pRect->bottom-pRect->top);
	}
}

/// @brief ���ƹ̶���С.
/// @param hImageList ͼƬ�б���.
/// @param bEnable  �Ƿ�����.
void WINAPI XImageList_EnableFixedSize(HXCGUI hImageList,BOOL bEnable) //���ƹ̶���С Fixed-size
{
	IsImageListDebug(hImageList,__FUNCTION__);
	((imageList_*)hImageList)->bFixedSize=bEnable;
}

/// @brief �ж�ͼƬ�Ƿ�����Ϊ�̶���С.
/// @param hImageList ͼƬ�б���.
/// @return ͼƬ������Ϊ�̶���СTRUE,�����෴FALSE.
BOOL WINAPI XImageList_IsFixedSize(HXCGUI hImageList)
{
	IsImageListDebug(hImageList,__FUNCTION__);
	return ((imageList_*)hImageList)->bFixedSize;
}

///@}


HXCGUI ImageList_AddRef(HXCGUI hImageList) //�������ü���
{
	if(hImageList)
	{
		((imageList_*)hImageList)->refCount++;
		return hImageList;
	}
	return NULL;
}