/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"


/// @defgroup sliderBar ������Ԫ��(SliderBar)
/// @ingroup groupElements
/// @{

/// @brief ����������Ԫ��.
/// @param x   Ԫ��x����.
/// @param y   Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param bHorizon ���ֵΪTRUEˮƽ������,����ֱ������.
/// @param hParent ���Ǵ�����Դ�����UIԪ����Դ���.����Ǵ�����Դ���������ӵ�����,
///                �����Ԫ����Դ���������ӵ�Ԫ��.
/// @return Ԫ�ؾ��.
HELE WINAPI XSliderBar_Create(int x, int y, int cx, int cy,BOOL bHorizon,HXCGUI hParent)
{
	slider_ *pObj=(slider_*)malloc(sizeof(slider_));
	memset(pObj,0,sizeof(slider_));
	pObj->bHorizon=bHorizon;
	SliderBar_Init((HELE)pObj,x,y,cx,cy,XC_SLIDERBAR,hParent);
	return (HELE)pObj;
}

void SliderBar_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,HXCGUI hParent)
{
	Ele_Init(hEle,x,y,cx,cy,eleType,hParent);
	AddTypeDebug(hEle,XC_SLIDERBAR);

	slider_ *pObj=SLIDER(hEle);
	pObj->range=100;
	pObj->minPos=1;
	pObj->btnWidth=10;

	if(pObj->bHorizon)
	{
		pObj->hButton= XBtn_Create(0,0,pObj->btnWidth,cy);
	}else
	{
		pObj->hButton= XBtn_Create(0,0,cx,pObj->btnWidth);
	}

	XEle_AddEle(hEle,pObj->hButton);
	XEle_EnableFocus(pObj->hButton,FALSE);
	Ele_SetType(pObj->hButton,XC_BUTTON_SLIDERBAR_SLIDER);

	XEle_RegisterMessage(hEle,XM_PAINT,SliderBar_OnDraw);
	XEle_RegisterMessage(hEle,XM_MOUSEMOVE,SliderBar_OnMouseMove);
	XEle_RegisterMessage(hEle,XM_LBUTTONDOWN,SliderBar_OnLButtonDown);
	XEle_RegisterMessage(hEle,XM_LBUTTONUP,SliderBar_OnLButtonUp);
	XEle_RegisterEvent(hEle,XE_MOUSELEAVE,SliderBar_OnEventMouseLeave);	

	XEle_RegisterMessage(pObj->hButton,XM_PAINT,SliderBar_OnDrawButton);
	XEle_RegisterEvent(hEle,XE_DESTROY,SliderBar_OnDestroy);
}

/// @brief ���û�����Χ.
/// @param hEle   Ԫ�ؾ��
/// @param range  ������Χ.
void WINAPI XSliderBar_SetRange(HELE hEle,int range)  //���û�����Χ
{
	IsSliderDebug(hEle,__FUNCTION__);
	SLIDER(hEle)->range=range;
	if(SLIDER(hEle)->bHorizon)
	{
		double cx=(((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left)-SLIDER(hEle)->btnWidth;

		if(0!=cx && 0!=SLIDER(hEle)->range)
			SLIDER(hEle)->minPos=cx/SLIDER(hEle)->range;
		else
			SLIDER(hEle)->minPos=0;
	}else
	{
		double cy=(((ele_*)hEle)->rect.bottom-((ele_*)hEle)->rect.top)-SLIDER(hEle)->btnWidth;

		if(0!=cy && 0!=SLIDER(hEle)->range)
			SLIDER(hEle)->minPos=cy/SLIDER(hEle)->range;
		else
			SLIDER(hEle)->minPos=0;
	}
}

/// @brief ���û���λ��.
/// @param hEle   Ԫ�ؾ��
/// @param pos  ����λ��.
void WINAPI XSliderBar_SetPos(HELE hEle,int pos)     //���û���λ��
{
	IsSliderDebug(hEle,__FUNCTION__);
	slider_ *pObj=SLIDER(hEle);

	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(pObj->bHorizon)
	{
		int cx=rect.right-rect.left;
		int x=(int)(pos*pObj->minPos);
		RECT rc;
		rc.left=x;
		rc.top=0;
		rc.right=rc.left+pObj->btnWidth;
		rc.bottom=rect.bottom-rect.top;
		if(rc.right>cx)
		{
			rc.right=cx;
			rc.left=rc.right-pObj->btnWidth;
		}
		XEle_SetRect(pObj->hButton,&rc);
	}else
	{
		int cy=rect.bottom-rect.top;
		int y=(int)(pos*pObj->minPos);
		RECT rc=rect;
		rc.bottom=rect.bottom-y;
		rc.top=rc.bottom-pObj->btnWidth;
		if(rc.top<0)
		{
			rc.bottom=pObj->btnWidth;
			rc.top=0;
		}
		XEle_SetRect(pObj->hButton,&rc);
	}	
	SLIDER(hEle)->pos=pos;
	XEle_RedrawEle(hEle);
}

/// @brief ��ȡ����λ��.
/// @param hEle   Ԫ�ؾ��
/// @return  ����λ��.
int  WINAPI XSliderBar_GetPos(HELE hEle)            //��ȡ����ֵ
{
	IsSliderDebug(hEle,__FUNCTION__);
	return SLIDER(hEle)->pos;
}

/// @brief ��ȡ�������ϻ�����.���ؾ������ΪButton.
/// @param hEle   Ԫ�ؾ��
/// @return  ������.
HELE WINAPI XSliderBar_GetButton(HELE hEle)      //��ȡ����
{
	IsSliderDebug(hEle,__FUNCTION__);
	return SLIDER(hEle)->hButton;
}

/// @brief ����Ϊˮƽ��ֱ������.
/// @param hEle   Ԫ�ؾ��.
/// @param bHorizon ���ֵΪTRUEˮƽ������,�����෴.
void WINAPI XSliderBar_SetHorizon(HELE hEle,BOOL bHorizon)  //ˮƽ��ʾ��ֱ
{
	IsSliderDebug(hEle,__FUNCTION__);
	SLIDER(hEle)->bHorizon=bHorizon;

	slider_ *pObj=SLIDER(hEle);

	int cx=((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left;
	int cy=((ele_*)hEle)->rect.bottom-((ele_*)hEle)->rect.top;
	int btnWidth= ((ele_*)(pObj->hButton))->rect.right-((ele_*)(pObj->hButton))->rect.left;
	int btnHeight= ((ele_*)(pObj->hButton))->rect.bottom-((ele_*)(pObj->hButton))->rect.top;
	if(pObj->bHorizon)
	{
		RECT rc;
		rc.left=(long)(pObj->pos*pObj->minPos);
		rc.top=cy/2-btnWidth/2;
		rc.right=rc.left+btnHeight;
		rc.bottom=rc.top+btnWidth;
		XEle_SetRect(pObj->hButton,&rc);
	}else
	{
		RECT rc;
		rc.left=cx/2-btnHeight/2;
		rc.top=(long)(pObj->pos*pObj->minPos);

		rc.right=rc.left+btnHeight;
		rc.bottom=rc.top+btnWidth;

		XEle_SetRect(pObj->hButton,&rc);
	}
	XEle_RedrawEle(hEle);
}

/// @brief ��ȡ������.
/// @param hEle   Ԫ�ؾ��.
/// @return  ������.
int WINAPI XSliderBar_GetButtonWidth(HELE hEle) //��ȡ������
{
	IsSliderDebug(hEle,__FUNCTION__);
	slider_ *pObj=SLIDER(hEle);
	return pObj->btnWidth;
}

/// @brief ���û�����.
/// @param hEle   Ԫ�ؾ��.
/// @param width  ������.
void WINAPI XSliderBar_SetButtonWidth(HELE hEle,int width) //���û�����
{
	IsSliderDebug(hEle,__FUNCTION__);
	slider_ *pObj=SLIDER(hEle);
	pObj->btnWidth=width;
	SliderBar_Adjust(hEle);
}

/// @brief ������Ԫ�ر�����ͼ.
/// @param hEle   Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XSliderBar_SetImage(HELE hEle,HIMAGE hImage)
{
	IsSliderDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(SLIDER(hEle)->hImage_bk,hImage);
}

/// @brief ������Ԫ��,��ʾ��ǰ������ͼ.
/// @param hEle   Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XSliderBar_SetImage2(HELE hEle,HIMAGE hImage) //��ʾ��ǰ����ͼƬ
{
	IsSliderDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(SLIDER(hEle)->hImage,hImage);
}

void SliderBar_Adjust(HELE hEle)
{
	slider_ *pObj=SLIDER(hEle);

	if(SLIDER(hEle)->bHorizon)
	{
		double cx=(((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left)-SLIDER(hEle)->btnWidth;
		if(0!=cx && 0!=SLIDER(hEle)->range)
			SLIDER(hEle)->minPos=cx/SLIDER(hEle)->range;
		else
			SLIDER(hEle)->minPos=0;
	}else
	{
		double cy=(((ele_*)hEle)->rect.bottom-((ele_*)hEle)->rect.top)-SLIDER(hEle)->btnWidth;
		if(0!=cy && 0!=SLIDER(hEle)->range)
			SLIDER(hEle)->minPos=cy/SLIDER(hEle)->range;
		else
			SLIDER(hEle)->minPos=0;
	}

	int cx=((ele_*)hEle)->rect.right-((ele_*)hEle)->rect.left;
	int cy=((ele_*)hEle)->rect.bottom-((ele_*)hEle)->rect.top;
	int btnWidth= ((ele_*)(pObj->hButton))->rect.right-((ele_*)(pObj->hButton))->rect.left;
	int btnHeight= ((ele_*)(pObj->hButton))->rect.bottom-((ele_*)(pObj->hButton))->rect.top;
	if(pObj->bHorizon)
	{
		btnWidth=pObj->btnWidth;

		RECT rc;
		rc.left=(long)(pObj->pos*pObj->minPos);
		rc.top=cy/2-btnHeight/2;
		rc.right=rc.left+btnWidth;
		rc.bottom=rc.top+btnHeight;
		XEle_SetRect(pObj->hButton,&rc);
	}else
	{
		btnHeight=pObj->btnWidth;
		RECT rc;
		rc.left=cx/2-btnWidth/2;
		rc.top=(long)(pObj->pos*pObj->minPos);
		rc.right=rc.left+btnWidth;
		rc.bottom=rc.top+btnHeight;
		XEle_SetRect(pObj->hButton,&rc);
	}
	//XEle_RedrawEle(hEle);
}

BOOL CALLBACK SliderBar_OnMouseMove(HELE hEle,UINT flags,POINT *pPt)
{
	slider_ *pObj=SLIDER(hEle);
	if(pObj->bDown)
	{
		RECT rect;
		XEle_GetClientRect(hEle,&rect);
		int cx=rect.right-rect.left;
		int cy=rect.bottom-rect.top;
		int btnWidth= ((ele_*)(pObj->hButton))->rect.right-((ele_*)(pObj->hButton))->rect.left;
		int btnHeight= ((ele_*)(pObj->hButton))->rect.bottom-((ele_*)(pObj->hButton))->rect.top;
		if(pObj->bHorizon)
		{
			int x=pPt->x-(btnWidth/2);

			if(x<0)
				x=0;
			else if(x>(cx-btnWidth)) 
				x=cx-btnWidth;

			int pos=(int)( x/pObj->minPos);
			if(pos != pObj->pos)
			{
				pObj->pos=pos;
				RECT rc;
				rc.left=(long)(pos*pObj->minPos);
				rc.top=cy/2-btnHeight/2;
				rc.right=rc.left+btnWidth;
				rc.bottom=rc.top+btnHeight;
				XEle_SetRect(pObj->hButton,&rc);
				XEle_SetCapture(hEle);   //����Ԫ����겶��

				Ele_SendEvent(hEle,XE_SLIDER_CHANGE,(WPARAM)pObj->pos,0);
				XEle_RedrawEle(hEle);
			}
		}else
		{
			int height=rect.bottom-pPt->y;
			height=height-(btnHeight/2);

			if(height<0)
				height=0;
			else if(height>(cy-btnHeight)) 
				height=cy-btnHeight;

			int pos=(int)( height/pObj->minPos);
			if(pos != pObj->pos)
			{
				pObj->pos=pos;
				RECT rc=rect;
				rc.left=cx/2-btnWidth/2;
				rc.right=rc.left+btnWidth;
				rc.bottom=rc.bottom-height;
				rc.top=rc.bottom-pObj->btnWidth;
				XEle_SetRect(pObj->hButton,&rc);
				XEle_SetCapture(hEle);   //����Ԫ����겶��

				Ele_SendEvent(hEle,XE_SLIDER_CHANGE,(WPARAM)pObj->pos,0);
				XEle_RedrawEle(hEle);
			}
		}
		return TRUE;
	}
	return FALSE;
}

BOOL CALLBACK SliderBar_OnLButtonDown(HELE hEle,UINT flags,POINT *pPt)
{
	slider_ *pObj=SLIDER(hEle);
	if(!pObj->bDown)
	{
		pObj->bDown=TRUE;
		RECT rect;
		XEle_GetClientRect(hEle,&rect);
		int cx=rect.right-rect.left;
		int cy=rect.bottom-rect.top;
		int btnWidth= ((ele_*)(pObj->hButton))->rect.right-((ele_*)(pObj->hButton))->rect.left;
		int btnHeight= ((ele_*)(pObj->hButton))->rect.bottom-((ele_*)(pObj->hButton))->rect.top;
		if(pObj->bHorizon)
		{
			int x=pPt->x-(btnWidth/2);

			if(x<0)
				x=0;
			else if(x>(cx-btnWidth)) 
				x=cx-btnWidth;

			int pos=(int)( x/pObj->minPos);
			if(pos != pObj->pos)
			{
				pObj->pos=pos;
				RECT rc;
				rc.left=(long)(pos*pObj->minPos);
				rc.top=cy/2-btnHeight/2;
				rc.right=rc.left+btnWidth;
				rc.bottom=rc.top+btnHeight;
				XEle_SetRect(pObj->hButton,&rc);
				XEle_SetCapture(hEle);   //����Ԫ����겶��

				BUTTON(pObj->hButton)->state=STATE_DOWN;
				Ele_SendEvent(hEle,XE_SLIDER_CHANGE,(WPARAM)pObj->pos,0);
				XEle_RedrawEle(hEle);
			}
		}else
		{
			int height=rect.bottom-pPt->y;
			height=height-(btnHeight/2);

			if(height<0)
				height=0;
			else if(height>(cy-btnHeight)) 
				height=cy-btnHeight;

			int pos=(int)( height/pObj->minPos);
			if(pos != pObj->pos)
			{
				pObj->pos=pos;
				RECT rc=rect;
				rc.left=cx/2-btnWidth/2;
				rc.right=rc.left+btnWidth;
				rc.bottom=rc.bottom-height;
				rc.top=rc.bottom-pObj->btnWidth;
				XEle_SetRect(pObj->hButton,&rc);
				XEle_SetCapture(hEle);   //����Ԫ����겶��
				Ele_SendEvent(hEle,XE_SLIDER_CHANGE,(WPARAM)pObj->pos,0);
				XEle_RedrawEle(hEle);
			}
		}
	}
	return FALSE;
}

BOOL CALLBACK SliderBar_OnLButtonUp(HELE hEle,UINT flags,POINT *pPt)
{
	slider_ *pObj=SLIDER(hEle);
	if(pObj->bDown)
	{
		pObj->bDown=FALSE;
		XEle_ReleaseCapture(hEle);    //�ͷ�Ԫ����겶��
	}
	return FALSE;
}

BOOL CALLBACK SliderBar_OnEventMouseLeave(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	slider_ *pObj=SLIDER(hEle);
	if(pObj->bDown)
	{
		pObj->bDown=FALSE;
		XEle_ReleaseCapture(hEle);    //�ͷ�Ԫ����겶��
	}
	return FALSE;
}

BOOL CALLBACK SliderBar_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	slider_ *pObject=SLIDER(hEle);

	if(pObject->hImage_bk)
	{
		XDraw_HImageSuper_(hDraw,pObject->hImage_bk,&rect);
	}else
	{
		if(pObject->bHorizon) //ˮƽ
		{
			int middle=(rect.bottom-rect.top)/2+1;

			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,0,middle-4,rect.right+1,middle+4,3,3);
			XDraw_SelectClipRgn_(hDraw,hRgn);

			//���������
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);

			/////////
			HPEN hPen1=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(80,80,80));
			HGDIOBJ hOld1=XDraw_SelectObject_(hDraw,hPen1);

			XDraw_MoveToEx_(hDraw,3,         middle-4,NULL);
			XDraw_LineTo_(hDraw,rect.right-2,middle-4);

			//XDraw_SelectObject_(hDraw,hOld1);
			//DeleteObject(hPen1);
			///////////////
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(200,200,200));
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);

			XDraw_MoveToEx_(hDraw,2,         middle-3,NULL);
			XDraw_LineTo_(hDraw,rect.right-2,middle-3);

		//	SelectObject(hdc,hOld);
		//	DeleteObject(hPen);

			XDraw_SelectClipRgn_(hDraw,NULL);
		//	DeleteObject(hRgn);
		}else //��ֱ
		{
			int middle=(rect.right-rect.left)/2+1;

			HRGN hRgn=XDraw_CreateRoundRectRgn_(hDraw,middle-4,0,middle+4,rect.bottom,3,3);
			XDraw_SelectClipRgn_(hDraw,hRgn);
			//���������
			HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
			XDraw_FrameRgn_(hDraw,hRgn,hBrush,1,1);
			//DeleteObject(hBrush);

			/////////
			HPEN hPen1=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(80,80,80));
			HGDIOBJ hOld1=XDraw_SelectObject_(hDraw,hPen1);

			XDraw_MoveToEx_(hDraw, middle-4,3,NULL);
			XDraw_LineTo_(hDraw,middle-4,rect.bottom-2);

	//		SelectObject(hdc,hOld1);
	//		DeleteObject(hPen1);
			///////////////
			HPEN hPen=XDraw_CreatePen_(hDraw,PS_SOLID,1,RGB(200,200,200));
			HGDIOBJ hOld=XDraw_SelectObject_(hDraw,hPen);

			XDraw_MoveToEx_(hDraw, middle-3,2,NULL);
			XDraw_LineTo_(hDraw,middle-3,rect.bottom-2);

			//SelectObject(hdc,hOld);
			//DeleteObject(hPen);

			XDraw_SelectClipRgn_(hDraw,NULL);
			//DeleteObject(hRgn);
		}
	}

	HDC hdc=XDraw_GetHDC_(hDraw);
	//������ͼ
	if(pObject->bHorizon) //ˮƽ
	{
		if(pObject->hImage)
		{
			int cx=0;
			if(0!=pObject->range)
			{
				double  pos=(double)pObject->pos/pObject->range;
				int width=rect.right-rect.left;
				cx=(int)(pos*width);
			}

			RECT rc=rect;
			rc.right=cx;

			switch(XImage_GetDrawType(pObject->hImage))
			{
			case XC_IMAGE_DEFAULT: //��ͨ:
			case XC_IMAGE_ADAPTIVE:	
				XDraw_HImage2_(hDraw,pObject->hImage,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);
				break;
			case XC_IMAGE_STRETCH: //����
				XDraw_HImageStretch_(hDraw,pObject->hImage,rc.left,rc.top,rc.right-rc.left,rc.bottom-rc.top);
				break;
			case XC_IMAGE_TILE://ƽ��
				XDraw_HImageExTile_(hDraw,pObject->hImage,&rc,0);
				break;
			}
		}
	}else //��ֱ
	{
		if(pObject->hImage)
		{
			int height=0;
			if(0!=pObject->range)
			{
				double  pos=(double)pObject->pos/pObject->range;
				height=(int)(pos*(rect.bottom-rect.top));
			}

			RECT rc=rect;
			rc.top=rc.bottom-height;

			switch(XImage_GetDrawType(pObject->hImage))
			{
			case XC_IMAGE_DEFAULT: //��ͨ:
			case XC_IMAGE_ADAPTIVE:
				{	
					RECT rc2=rc;
					rc2.bottom=XImage_GetHeight(pObject->hImage);
					rc2.top=rc2.bottom-height;
					XDraw_HImageSuper2_(hDraw,pObject->hImage,&rc,&rc2);
				}
				break;
			case XC_IMAGE_STRETCH: //����
				XDraw_HImageStretch_(hDraw,pObject->hImage,rc.left,rc.top,rc.right-rc.left,height);
				break;
			case XC_IMAGE_TILE://ƽ��
				XDraw_HImageExTile_(hDraw,pObject->hImage,&rc,1);
				break;
			}
		}
	}

	return TRUE;
}

BOOL CALLBACK SliderBar_OnDrawButton(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);
	HELE hParetn=XEle_GetParentEle(hEle);

	if(BUTTON(hEle)->hImage_leave) return FALSE;
	if(BUTTON(hEle)->hImage_stay) return FALSE;
	if(BUTTON(hEle)->hImage_down) return FALSE;
	if(BUTTON(hEle)->hImage_check) return FALSE;
	if(BUTTON(hEle)->hImage_disable) return FALSE;

	if(hParetn && FALSE==((slider_*)hParetn)->bHorizon)
	{
		XDraw_GradientFill4_(hDraw,RGB(250,250,250),RGB(210,210,210),RGB(200,200,200),RGB(230,230,230),&rect,GRADIENT_FILL_RECT_H);
	}else
		XDraw_GradientFill4_(hDraw,RGB(250,250,250),RGB(210,210,210),RGB(200,200,200),RGB(230,230,230),&rect,GRADIENT_FILL_RECT_V);

	{
		//���������
		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(130,130,130));
		XDraw_FrameRect_(hDraw,&rect,hBrush);
		//DeleteObject(hBrush);
	}

	{
		RECT rc=rect;
		rc.left++;
		rc.top++;
		rc.right--;
		rc.bottom--;

		HBRUSH hBrush=XDraw_CreateSolidBrush_(hDraw,RGB(250,250,250));
		XDraw_FrameRect_(hDraw,&rc,hBrush);
		//DeleteObject(hBrush);
	}
	return TRUE;
}

void CALLBACK SliderBar_OnDestroy(HELE hEle)  //����
{
	if(SLIDER(hEle)->hImage_bk) XImage_Destroy(SLIDER(hEle)->hImage_bk);
	if(SLIDER(hEle)->hImage) XImage_Destroy(SLIDER(hEle)->hImage);
}

///@}