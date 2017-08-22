/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup progressBar ������(ProgressBar)
/// @ingroup groupElements
/// @{

/// @brief ����������Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param bHorizon ���ֵΪTRUEˮƽ������,�����෴.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XProgBar_Create(int x, int y, int cx, int cy,BOOL bHorizon,HXCGUI hParent)
{
	progressBar_ *pObj=(progressBar_*)malloc(sizeof(progressBar_));
	memset(pObj,0,sizeof(progressBar_));
	pObj->bHorizon=bHorizon;
	ProgBar_Init((HELE)pObj,x,y,cx,cy,XC_PROGRESSBAR,hParent);
	return (HELE)pObj;
}

void ProgBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_PROGRESSBAR);
	((progressBar_*)hEle)->range=100;
	((progressBar_*)hEle)->curPos=50;
	((progressBar_*)hEle)->bPercent=FALSE;
	XEle_RegisterMessage(hEle,XM_PAINT,ProgBar_OnDraw);
}

/// @brief ���ý�������Χ.
/// @param hEle Ԫ�ؾ��.
/// @param range ��������Χ.
void WINAPI XProgBar_SetRange(HELE hEle,int range)  //���÷�Χ
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	if(range<0) return;

	if(range<((progressBar_*)hEle)->range)
		((progressBar_*)hEle)->curPos=range;

	((progressBar_*)hEle)->range=range;
}

/// @brief ���ý�������ǰλ�õ�.
/// @param hEle Ԫ�ؾ��.
/// @param pos  ��ǰλ�õ�.
void WINAPI XProgBar_SetPos(HELE hEle,int pos)  //���õ�ǰλ��
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	if(pos<0) return ;

	if(pos>((progressBar_*)hEle)->range)
		((progressBar_*)hEle)->curPos=((progressBar_*)hEle)->range;

	((progressBar_*)hEle)->curPos=pos;
}

/// @brief ��ȡ��������Χ.
/// @param hEle Ԫ�ؾ��.
/// @return  ��������Χ.
int  WINAPI XProgBar_GetRange(HELE hEle)
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	return ((progressBar_*)hEle)->range;
}

/// @brief ��ȡ��������ǰλ�õ�.
/// @param hEle Ԫ�ؾ��.
/// @return  ��������ǰλ�õ�.
int  WINAPI XProgBar_GetPos(HELE hEle)
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	return ((progressBar_*)hEle)->curPos;
}

/// @brief ���ý�����Ԫ��ˮƽ��ֱ.
/// @param hEle Ԫ�ؾ��.
/// @param bHorizon ���ֵΪTRUEˮƽ������,�����෴.
void WINAPI XProgBar_SetHorizon(HELE hEle,BOOL bHorizon)
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	((progressBar_*)hEle)->bHorizon=bHorizon;
}

/// @brief ������ʾ�ٷֱȹ���.
/// @param hEle Ԫ�ؾ��.
/// @param bPercent ���ֵΪTRUE��ʾ�ٷֱ�,�����෴.
void WINAPI XProgBar_EnablePercent(HELE hEle,BOOL bPercent) //��ʾ�ٷֱ�
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	((progressBar_*)hEle)->bPercent=bPercent;
}

//��ͼ:

/// @brief ������Ԫ�ر�����ͼ.
/// @param hEle   Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XProgBar_SetImage(HELE hEle,HIMAGE hImage) //����
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}

	progressBar_ *pObject=(progressBar_*)hEle;
	Image_AddImage(pObject->hImage_bk,hImage);
}

/// @brief ������Ԫ��,��ʾ��ǰ������ͼ.
/// @param hEle   Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XProgBar_SetImage2(HELE hEle,HIMAGE hImage) //��ʾ��ǰ����ͼƬ
{
	IsProgressBarDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}

	progressBar_ *pObject=(progressBar_*)hEle;
	Image_AddImage(pObject->hImage,hImage);
}

BOOL CALLBACK ProgBar_OnDraw(HELE hEle,HDRAW hDraw)
{
	progressBar_ *pObj=(progressBar_*)hEle;

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(pObj->bHorizon) //ˮƽ
	{
		//���Ʊ���
		ProgBar_OnDrawHorizon(hEle,hDraw,rect);
	}else //��ֱ
	{
		ProgBar_OnDrawVertical(hEle,hDraw,rect);
	}

	return TRUE;
}

void ProgBar_OnDrawHorizon(HELE hEle,HDRAW hDraw,RECT &rect)
{
	progressBar_ *pObj=(progressBar_*)hEle;

	//���Ʊ���
	if(pObj->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,pObj->hImage_bk,&rect);
	}else
	{
		//���û�������
		HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,3,3);
		XDraw_SelectClipRgn_(hDraw,hRgn);

		//�������
		XDraw_GradientFill4_(hDraw,RGB(255,255,255),RGB(210,210,210),RGB(200,200,200),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_V);
		
		//���������
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(180,180,180));
		XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
		//DeleteObject(hBrush);

		//DeleteObject(hRgn);
	}
	//���ƽ���
	double pos=0;
	if(0!=pObj->range)
		pos=((double)pObj->curPos/(double)pObj->range);

	int width=(int)(pos*(rect.right-rect.left));
	RECT rc=rect;
	rc.right=rc.left+width;
	if(pObj->hImage)
	{
		switch(XImage_GetDrawType(pObj->hImage))
		{
		case XC_IMAGE_DEFAULT: //��ͨ:
		case XC_IMAGE_ADAPTIVE:	
			XDraw_HImage2_(hDraw,pObj->hImage,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);
			break;
		case XC_IMAGE_STRETCH: //����
			XDraw_HImageStretch_(hDraw,pObj->hImage,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);
			break;
		case XC_IMAGE_TILE://ƽ��
			XDraw_HImageExTile_(hDraw,pObj->hImage,&rc,0);
			break;
		}
	}else
	{
		//���û�������
		HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom,3,3);
		XDraw_SelectClipRgn_(hDraw,hRgn);

		//�������
		XDraw_GradientFill4_(hDraw,RGB(208,255,220),RGB(0,210,53),RGB(0,189,48),RGB(208,255,220),&rc,GRADIENT_FILL_RECT_V);

		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(0,210,53));
		HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
		XDraw_MoveToEx_(hDraw,rc.right,0,NULL);
		XDraw_LineTo_(hDraw,rc.right,rc.bottom);
		//SelectObject(hdc,hOldPen);
		//DeleteObject(hPen);

		if(pObj->bPercent)
		{
			int  percent=(int)(pos*100); //�ٷֱ�
			wchar_t percentW[10]={0};
			wsprintf(percentW,L"%d%%",percent);
			XDraw_DrawText_(hDraw,percentW,wcslen(percentW),&rect,DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}

		XDraw_SelectClipRgn_(hDraw,NULL);
	//	DeleteObject(hRgn);
	}
}


void ProgBar_OnDrawVertical(HELE hEle,HDRAW hDraw,RECT &rect)
{
	progressBar_ *pObj=(progressBar_*)hEle;
	//���Ʊ���
	if(pObj->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,pObj->hImage_bk,&rect);
	}else
	{
		//���û�������
		HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,0,rect.right+1,rect.bottom+1,3,3);
		XDraw_SelectClipRgn_(hDraw,hRgn);
		//�������
		XDraw_GradientFill4_(hDraw,RGB(255,255,255),RGB(210,210,210),RGB(200,200,200),RGB(255,255,255),&rect,GRADIENT_FILL_RECT_H);

		//���������
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(180,180,180));
		XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
		//DeleteObject(hBrush);

		XDraw_SelectClipRgn_(hDraw,NULL);
	//	DeleteObject(hRgn);
	}

	//���ƽ���
	double pos=0;
	if(0!=pObj->range)
		pos=((double)pObj->curPos/(double)pObj->range);

	int height=(int)(pos*(rect.bottom-rect.top));
	RECT rc=rect;
	rc.top=rect.bottom-height;
	if(pObj->hImage)
	{
		switch(XImage_GetDrawType(pObj->hImage))
		{
		case XC_IMAGE_DEFAULT: //��ͨ:
		case XC_IMAGE_ADAPTIVE:
			{	
				RECT rc2=rc;
				rc2.bottom=XImage_GetHeight(pObj->hImage);
				rc2.top=rc2.bottom-height;
				XDraw_HImageSuper2_(hDraw,pObj->hImage,&rc,&rc2);
			}
			break;
		case XC_IMAGE_STRETCH: //����
			XDraw_HImageStretch_(hDraw,pObj->hImage,rc.left,rc.top,rc.right-rc.left,height);
			break;
		case XC_IMAGE_TILE://ƽ��
			XDraw_HImageExTile_(hDraw,pObj->hImage,&rc,1);
			break;
		}
	}else
	{
		//���û�������
		HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,1,1,rect.right,rect.bottom,3,3);
		XDraw_SelectClipRgn_(hDraw,hRgn);

		//�������
		XDraw_GradientFill4_(hDraw,RGB(208,255,220),RGB(0,210,53),RGB(0,189,48),RGB(208,255,220),&rc,GRADIENT_FILL_RECT_H);

		HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(0,210,53));
		HGDIOBJ hOldPen=XDraw_SelectObject_(hDraw,hPen);
		XDraw_MoveToEx_(hDraw,0,rc.top,NULL);
		XDraw_LineTo_(hDraw,rc.right,rc.top);
	//	SelectObject(hdc,hOldPen);
	//	DeleteObject(hPen);

		if(pObj->bPercent)
		{
			int  percent=(int)(pos*100); //�ٷֱ�
			wchar_t percentW[10]={0};
			wsprintf(percentW,L"%d%%",percent);
			XDraw_DrawText_(hDraw,percentW,wcslen(percentW),&rect,DT_VCENTER | DT_SINGLELINE | DT_CENTER);
		}

		XDraw_SelectClipRgn_(hDraw,NULL);
	}
}


///@}