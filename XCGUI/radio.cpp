/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup radio ��ѡ��ť(Radio)
/// @ingroup groupElements
/// @{

/// @brief ������ѡ��ťԪ��.
/// @param x  Ԫ��x����.
/// @param y  Ԫ��y����.
/// @param cx  ���.
/// @param cy  �߶�.
/// @param pTitle  ����.
/// @param hParent  ��Ϊ���ھ����Ԫ�ؾ��.
/// @return ��ѡ��ť���.
HELE WINAPI XRadio_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent)
{
	radio_ *pRadio=(radio_*)malloc(sizeof(radio_));
	memset(pRadio,0,sizeof(radio_));
	
	Radio_Init((HELE)pRadio,x,y,cx,cy,XC_RADIO,pTitle,hParent);

	return (HELE)pRadio;
}

void Radio_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent) //��ʼ��ע��
{
	Btn_Init(hEle,x,y,cx,cy,eleType,pTitle,hParent);
	AddTypeDebug(hEle,XC_RADIO);

	((button_*)hEle)->textFlag=DT_VCENTER| DT_SINGLELINE | DT_END_ELLIPSIS;

	XEle_RegisterMessage(hEle,XM_PAINT,Radio_OnDraw);
	XEle_RegisterEvent(hEle,XE_BNCLICK,Radio_OnEventBtnClick);
	XEle_RegisterEvent(hEle,XE_DESTROY,Radio_OnDestroy);
}

//��ͼ:

/// @brief ���õ�ѡ��ťԪ��,����뿪��δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageLeave_UnCheck(HELE hEle,HIMAGE hImage)  //����뿪ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	XBtn_SetImageLeave(hEle,hImage);
}

/// @brief ���õ�ѡ��ťԪ��,���ͣ����δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageStay_UnCheck(HELE hEle,HIMAGE hImage)   //���ͣ��ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	XBtn_SetImageStay(hEle,hImage);
}
/// @brief  ���õ�ѡ��ťԪ��,��갴�º�δѡ��״̬ʱ��ͼ. 
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageDown_UnCheck(HELE hEle,HIMAGE hImage)   //��갴��ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	XBtn_SetImageDown(hEle,hImage);
}
/// @brief ���õ�ѡ��ťԪ�ؽ��ú�δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageDisable_UnCheck(HELE hEle,HIMAGE hImage) //��ť����״̬ͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	XBtn_SetImageDisable(hEle,hImage);
}
/// @brief ���õ�ѡ��ťԪ��,����뿪��ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageLeave_Check(HELE hEle,HIMAGE hImage)  //����뿪ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_leave_check,hImage);
}
/// @brief ���õ�ѡ��ťԪ��,���ͣ����ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageStay_Check(HELE hEle,HIMAGE hImage)   //���ͣ��ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_stay_check,hImage);
}
/// @brief ���õ�ѡ��ťԪ��,��갴�º�ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageDown_Check(HELE hEle,HIMAGE hImage)   //��갴��ʱͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_down_check,hImage);
}
/// @brief ���õ�ѡ��ťԪ�ؽ��ú�ѡ��״̬ʱ����ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XRadio_SetImageDisable_Check(HELE hEle,HIMAGE hImage) //��ť����״̬ͼƬ
{
	IsRadioDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(RADIO(hEle)->hImage_disable_check,hImage);
}

/// @brief ������ID.
/// @param hEle Ԫ�ؾ��.
/// @param groupID  ��ID
void WINAPI XRadio_SetGroupID(HELE hEle,int groupID)  //������ID
{
	IsRadioDebug(hEle,__FUNCTION__);
	RADIO(hEle)->groupID=groupID;
}

/// @brief ��ȡ��ID.
/// @param hEle Ԫ�ؾ��.
/// @return  ������ID
int  WINAPI XRadio_GetGroupID(HELE hEle)  //��ȡ��ID
{
	IsRadioDebug(hEle,__FUNCTION__);
	return RADIO(hEle)->groupID;
}

/// @brief ���ð�ť��ʽ.
/// @param  hEle Ԫ�ؾ��.
/// @param  bStyle  ����:TRUE,�ر�:FALSE;
void  WINAPI XRadio_EnableButtonStyle(HELE hEle,BOOL bStyle) //���ð�ť��ʽ
{
	IsRadioDebug(hEle,__FUNCTION__);
	RADIO(hEle)->bButtonStyle=bStyle;
	if(bStyle)
		BUTTON(hEle)->textFlag= DT_VCENTER | DT_SINGLELINE | DT_CENTER | DT_END_ELLIPSIS;
	else
		BUTTON(hEle)->textFlag= DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS;
}

/// @brief ��Ԫ��,����ť��ѡ�л�ȡ��ѡ��,�����XEle_ShowEle()����,��ʾ�����ذ󶨵�Ԫ��.
/// @param  hEle Ԫ�ؾ��.
/// @param  bindEle  ��Ԫ�ؾ��;
void WINAPI XRadio_SetBindEle(HELE hEle,HELE bindEle)
{
	IsRadioDebug(hEle,__FUNCTION__);
	RADIO(hEle)->hBindEle=bindEle;
}

BOOL CALLBACK Radio_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(XBtn_IsCheck(hEle)) //��ѡ
	{
		Radio_DrawCheck(hEle,hDraw,rect);
	}else
	{
		Radio_DrawUnCheck(hEle,hDraw,rect);
	}

	if(((ele_*)hEle)->bDrawFocus && hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		if(RADIO(hEle)->bButtonStyle)
		{
			RECT rcFocus={2,2,rect.right-2,rect.bottom-2};
			XDraw_FocusRect_(hDraw,&rcFocus);
		}else
		{
			RECT rcFocus={0,0,rect.right,rect.bottom};
			XDraw_FocusRect_(hDraw,&rcFocus);
		}
	}
	return TRUE;
}

void Radio_DrawCheck(HELE hEle,HDRAW hDraw,RECT &rect) //���ƹ�ѡ״̬
{	
	int top=rect.bottom/2-6;  //����Բ����
	if(FALSE==((ele_*)hEle)->bEnable)  //����)
	{
		if(RADIO(hEle)->hImage_disable_check)
		{
			XDraw_HImageSuper_(hDraw,RADIO(hEle)->hImage_disable_check,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDisable2(hEle,hDraw,rect);
			}else
				Radio_Draw_Check2(hDraw,2,top,RGB(100,100,100),RGB(80,80, 80));
		}
		//�����ı�
	/*	COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		wchar_t *pText=XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw,color);
		return ;*/
	}else if(STATE_LEAVE ==((button_*)hEle)->state)	//�뿪
	{
		if(RADIO(hEle)->hImage_leave_check)
		{
			XDraw_HImageSuper_(hDraw,RADIO(hEle)->hImage_leave_check,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawLeave2(hEle,hDraw,rect);
			}else
				Radio_Draw_Check2(hDraw,2,top,RGB(100,100,100),RGB(80,80, 80));
		}
	}else if( STATE_STAY==((button_*)hEle)->state)//ͣ��
	{
		if(RADIO(hEle)->hImage_stay_check)
		{
			XDraw_HImageSuper_(hDraw,RADIO(hEle)->hImage_stay_check,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawStay2(hEle,hDraw,rect);
			}else
				Radio_Draw_Check2(hDraw,2,top,RGB(100,100,100),RGB(39,135,194));
		}
	}else if( STATE_DOWN==((button_*)hEle)->state) //����
	{
		if(RADIO(hEle)->hImage_down_check)
		{
			XDraw_HImageSuper_(hDraw,RADIO(hEle)->hImage_down_check,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDown2(hEle,hDraw,rect);
			}else
				Radio_Draw_Check2(hDraw,2,top,RGB(100,100,100),RGB(39,135,194));
		}
	}

	if(RADIO(hEle)->bButtonStyle)
	{
		Btn_DrawIconAndText(hEle,hDraw,rect);
	}else
	{
		wchar_t *pText=XBtn_GetText(hEle);
		if(pText)
		{
			RECT rcText=rect;
			rcText.left+=17;
			XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,((button_*)hEle)->textFlag);
		}
	}
}

void Radio_Draw_Check2(HDRAW hDraw,int x,int y,COLORREF color_dot,COLORREF color_border)
{
	IsDrawDebug(hDraw,__FUNCTION__);

	HDC hdc=XDraw_GetHDC_(hDraw);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	int left=x+pDraw->x;
	int top=y+pDraw->y;

	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	SolidBrush  solidbrush(Color(GetRValue(color_dot),GetGValue(color_dot),GetBValue(color_dot)));
	graphics.FillEllipse(&solidbrush,Rect(left+3,top+3,6,6));

	//�߿�
	Pen bluePen(Color( GetRValue(color_border),GetGValue(color_border),GetBValue(color_border)));
	Rect ellipseRect(left, top, 12, 12);
	graphics.DrawEllipse(&bluePen, ellipseRect);
}

void Radio_DrawUnCheck(HELE hEle,HDRAW hDraw,RECT &rect) //����δ��ѡ״̬
{
	int top=rect.bottom/2-6;  //����Բ����
	if(FALSE==((ele_*)hEle)->bEnable)  //����)
	{
		if(BUTTON(hEle)->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_disable,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDisable2(hEle,hDraw,rect);
			}else
				Radio_Draw_UnCheck2(hDraw,2,top,RGB(180,180,180),RGB(255,255,255),RGB(80,80, 80));
		}
/*		//�����ı�
		COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		wchar_t *pText=XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw,color);
		return ;*/
	}else if(STATE_LEAVE ==((button_*)hEle)->state)	//�뿪
	{
		if(BUTTON(hEle)->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_leave,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawLeave2(hEle,hDraw,rect);
			}else
				Radio_Draw_UnCheck2(hDraw,2,top,RGB(180,180,180),RGB(255,255,255),RGB(80,80, 80));
		}
	}else if( STATE_STAY==((button_*)hEle)->state)//ͣ��
	{
		if(BUTTON(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_stay,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawStay2(hEle,hDraw,rect);
			}else
				Radio_Draw_UnCheck2(hDraw,2,top,RGB(180,180,180),RGB(255,255,255),RGB(39,135,194));
		}
	}else if( STATE_DOWN==((button_*)hEle)->state) //����
	{
		if(BUTTON(hEle)->hImage_down)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_down,&rect);
		}else
		{
			if(RADIO(hEle)->bButtonStyle)
			{
				Btn_DrawDown2(hEle,hDraw,rect);
			}else
				Radio_Draw_UnCheck2(hDraw,2,top,RGB(180,180,180),RGB(255,255,255),RGB(39,135,194));
		}
	}

	if(RADIO(hEle)->bButtonStyle)
	{
		Btn_DrawIconAndText(hEle,hDraw,rect);
	}else
	{
		wchar_t *pText=XBtn_GetText(hEle);
		if(pText)
		{
			RECT rcText=rect;
			rcText.left+=17;
			XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,((button_*)hEle)->textFlag);
		}
	}
}

void Radio_Draw_UnCheck2(HDRAW hDraw,int x,int y,COLORREF color_dot1,COLORREF color_dot2,COLORREF color_border)
{
	IsDrawDebug(hDraw,__FUNCTION__);

	HDC hdc=XDraw_GetHDC_(hDraw);
	draw_xc_ *pDraw=(draw_xc_*)hDraw;
	int left=x+pDraw->x;
	int top=y+pDraw->y;

	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeHighQuality);

	LinearGradientBrush  brush(Rect(left+2,top,8,8),
		Color( GetRValue(color_dot1),GetGValue(color_dot1),GetBValue(color_dot1)),
		Color( GetRValue(color_dot2),GetGValue(color_dot2),GetBValue(color_dot2))
		,LinearGradientModeForwardDiagonal);
	graphics.FillEllipse(&brush,Rect(left+2,top+2,8,8));

	//�߿�
	Pen bluePen(Color( GetRValue(color_border),GetGValue(color_border),GetBValue(color_border)));
	Rect ellipseRect(left, top, 12, 12);
	graphics.DrawEllipse(&bluePen, ellipseRect);

}

BOOL CALLBACK Radio_OnEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(hEle!=hEventEle)
		return FALSE;

	if(XBtn_IsCheck(hEle))
		return FALSE;

	ele_ *pEle=(ele_*)hEle;

	XBtn_SetCheck(hEle,TRUE);
	XEle_RedrawEle(hEle);

	HARRAY hArrayEle=NULL;
	if(pEle->pParentEle)
	{
		hArrayEle=pEle->pParentEle->hArrayEle;
	}else
	{
		window_ *pWindow=(window_*)XEle_GetHWindow(hEle);
		hArrayEle=pWindow->hArrayEle;
	}

	int count=Array_GetCount(hArrayEle);
	int index=pEle->id;
	
	radio_  *pRadioT=NULL;
	for (int i=0;i<count;i++)
	{
		pRadioT=(radio_*)XArray_GetAt(hArrayEle,i);
		if(XC_RADIO==((ele_*)pRadioT)->eleType)
		{
			if( RADIO(hEle)->groupID==pRadioT->groupID && RADIO(hEle)!=pRadioT)
			{
				if(BUTTON(pRadioT)->bCheck)
				{
					XBtn_SetCheck((HELE)pRadioT,FALSE);
					XEle_RedrawEle((HELE)pRadioT);
					break;
				}
			}
		}
	}

	return FALSE;
}

void CALLBACK Radio_OnDestroy(HELE hEle)  //����
{
	if(RADIO(hEle)->hImage_leave_check) XImage_Destroy(RADIO(hEle)->hImage_leave_check);
	if(RADIO(hEle)->hImage_stay_check) XImage_Destroy(RADIO(hEle)->hImage_stay_check);
	if(RADIO(hEle)->hImage_down_check) XImage_Destroy(RADIO(hEle)->hImage_down_check);
	if(RADIO(hEle)->hImage_disable_check) XImage_Destroy(RADIO(hEle)->hImage_disable_check);
}

///@}
