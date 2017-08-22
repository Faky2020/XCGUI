/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#pragma once


struct  imageListItem_
{
	//HANDLE  handle;  //���  λͼ��ͼ����
	//����  0λͼ  1��͸��ɫλͼ  2ͼ�� 3������ʽͼƬ,��png
	//4 ���ļ�����ͼ��
 //  int     type;  
	
//   COLORREF color;  //͸��ɫ
//	Image   *pImage; //������ʽͼƬ,��PNGͼƬ

	HIMAGE  hImage;//ͼƬ
};

struct imageList_
{
	object_ object;
	int    refCount; //���ü���,��ֵΪ0ʱ ���ٶ���

	HARRAY hArrayImage; //ͼƬ�б� imageListItem_*
	SIZE  size; //ͼƬ��С

	BOOL bFixedSize; //���ƹ̶���С
};

//λͼ���� ͼ������

//API:
XC_API HXCGUI WINAPI XImageList_Create(int cx,int cy);
XC_API void WINAPI XImageList_Destroy(HXCGUI hImageList); //����
XC_API void WINAPI XImageList_AddImage(HXCGUI hImageList,HIMAGE hImage); //���ͼƬ

XC_API int  WINAPI XImageList_GetWidth(HXCGUI hImageList);   //��ȡͼƬ���
XC_API int  WINAPI XImageList_GetHeight(HXCGUI hImageList);  //��ȡͼƬ�߶�
XC_API int  WINAPI XImageList_GetCount(HXCGUI hImageList);   //��ȡͼƬ����
XC_API HIMAGE WINAPI XImageList_GetImage(HXCGUI hImageList,int index); //��ȡͼƬ

XC_API void WINAPI XImageList_DeleteIndex(HXCGUI hImageList,int index); //ɾ��ָ��ͼƬ
XC_API void WINAPI XImageList_DeleteAll(HXCGUI hImageList);  //ɾ��ȫ��ͼƬ

XC_API void WINAPI XImageList_DrawImage(HXCGUI hImageList,HDRAW hDraw,int index, int x, int y);
XC_API void WINAPI XImageList_DrawImage2(HXCGUI hImageList,HDRAW hDraw,int index, RECT *pRect);

XC_API void WINAPI XImageList_EnableFixedSize(HXCGUI hImageList,BOOL bEnable); //���ƹ̶���С Fixed-size
XC_API BOOL WINAPI XImageList_IsFixedSize(HXCGUI hImageList);
//˽�з���:
HXCGUI ImageList_AddRef(HXCGUI hImageList); //�������ü���