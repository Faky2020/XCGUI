/**************************************************************************\
*
* Copyright (c)  �Ųʽ����. All Rights Reserved.
*
* �Ųʽ���� - �ٷ���վ : http://www.xcgui.com
*
\**************************************************************************/
#include "StdAfx.h"

/// @defgroup check ��ѡ��ť(Check)
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
HELE WINAPI XCheck_Create(int x, int y, int cx, int cy,wchar_t *pTitle,HXCGUI hParent)  //������ť
{
	check_ *pCheck=(check_*)malloc(sizeof(check_));
	memset(pCheck,0,sizeof(check_));

	Check_Init((HELE)pCheck,x,y,cx,cy,XC_CHECK,pTitle,hParent);
	return (HELE)pCheck;
}


void Check_Init(HELE hEle,int x,int y,int cx,int cy,int eleType,wchar_t *pTitle,HXCGUI hParent) //��ʼ��ע��
{
	Btn_Init(hEle,x,y,cx,cy,eleType,pTitle,hParent);

	AddTypeDebug(hEle,XC_CHECK);

	((button_*)hEle)->textFlag=DT_VCENTER| DT_SINGLELINE;

	XEle_RegisterMessage(hEle,XM_PAINT,Check_OnDraw);
	XEle_RegisterEvent(hEle,XE_BNCLICK,Check_OnEventBtnClick);
	XEle_RegisterEvent(hEle,XE_DESTROY,Check_OnDestroy);
}

//��ͼ:

/// @brief ��������뿪��δѡ��״̬ʱ��ͼ.
/// @param hEle   Ԫ�ؾ��.
/// @param hImage ͼƬ���.
void WINAPI XCheck_SetImageLeave_UnCheck(HELE hEle,HIMAGE hImage)  //����뿪ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	XBtn_SetImageLeave(hEle,hImage);
}

/// @brief �������ͣ����δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageStay_UnCheck(HELE hEle,HIMAGE hImage)   //���ͣ��ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	XBtn_SetImageStay(hEle,hImage);
}

/// @brief ������갴�º�δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageDown_UnCheck(HELE hEle,HIMAGE hImage)   //��갴��ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	XBtn_SetImageDown(hEle,hImage);
}

/// @brief ���ý��ú�δѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageDisable_UnCheck(HELE hEle,HIMAGE hImage) //��ť����״̬ͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	XBtn_SetImageDisable(hEle,hImage);
}

/// @brief ��������뿪��ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageLeave_Check(HELE hEle,HIMAGE hImage)  //����뿪ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_leave_check,hImage);
}

/// @brief �������ͣ����ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageStay_Check(HELE hEle,HIMAGE hImage)   //���ͣ��ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_stay_check,hImage);
}
/// @brief ������갴�º�ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageDown_Check(HELE hEle,HIMAGE hImage)  //��갴��ʱͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_down_check,hImage);
}

/// @brief ���ý��ú�ѡ��״̬ʱ��ͼ.
/// @param hEle    Ԫ�ؾ��.
/// @param hImage  ͼƬ���.
void WINAPI XCheck_SetImageDisable_Check(HELE hEle,HIMAGE hImage) //��ť����״̬ͼƬ
{
	IsCheckDebug(hEle,__FUNCTION__);
	if(hImage)
	{
		IsHImageDebug(hImage,__FUNCTION__);
	}
	Image_AddImage(CHECK(hEle)->hImage_disable_check,hImage);
}

BOOL CALLBACK Check_OnDraw(HELE hEle,HDRAW hDraw)
{
	RECT rect;
	XEle_GetClientRect(hEle,&rect);

	if(XBtn_IsCheck(hEle)) //��ѡ
	{
		Check_DrawCheck(hEle,hDraw,rect);
	}else
	{
		Check_DrawUnCheck(hEle,hDraw,rect);
	}

	if(((ele_*)hEle)->bDrawFocus && hEle==XWnd_GetFocusEle(XEle_GetHWindow(hEle))) //���ƽ���
	{
		RECT rcFocus={0,0,rect.right,rect.bottom};
		XDraw_FocusRect_(hDraw,&rcFocus);
	}
	return TRUE;
}

void Check_DrawCheck(HELE hEle,HDRAW hDraw,RECT &rect) //���ƹ�ѡ״̬
{	
	RECT rcText=rect;
	rcText.left+=17;
	int top=rect.bottom/2-6;  //����Բ����
	if(FALSE==((ele_*)hEle)->bEnable)  //����)
	{
		if(CHECK(hEle)->hImage_disable_check)
		{
			XDraw_HImageSuper_(hDraw,CHECK(hEle)->hImage_disable_check,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(80,80, 80),TRUE);
		}
		//�����ı�
		COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		wchar_t *pText=XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw,color);
		return ;
	}else if(STATE_LEAVE ==((button_*)hEle)->state)	//�뿪
	{
		if(CHECK(hEle)->hImage_leave_check)
		{
			XDraw_HImageSuper_(hDraw,CHECK(hEle)->hImage_leave_check,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(80,80, 80),TRUE);
		}
	}else if( STATE_STAY==((button_*)hEle)->state)//ͣ��
	{
		if(CHECK(hEle)->hImage_stay_check)
		{
			XDraw_HImageSuper_(hDraw,CHECK(hEle)->hImage_stay_check,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(39,135,194),TRUE);
		}
	}else if( STATE_DOWN==((button_*)hEle)->state) //����
	{
		if(CHECK(hEle)->hImage_down_check)
		{
			XDraw_HImageSuper_(hDraw,CHECK(hEle)->hImage_down_check,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(39,135,194),TRUE);
		}
		rcText.top+=2;
	}
	//�����ı�
	wchar_t *pText=XBtn_GetText(hEle);
	if(pText)
	{
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,((button_*)hEle)->textFlag);//DT_VCENTER| DT_SINGLELINE);
	}
}

void Check_DrawUnCheck(HELE hEle,HDRAW hDraw,RECT &rect) //����δ��ѡ״̬
{
	RECT rcText=rect;
	rcText.left+=17;
	int top=rect.bottom/2-6;  //����Բ����

	if(FALSE==((ele_*)hEle)->bEnable)  //����)
	{
		if(BUTTON(hEle)->hImage_disable)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_disable,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(80,80,80),FALSE);
		}
		//�����ı�
		COLORREF color=XDraw_SetTextColor_(hDraw,RGB(128,128,128));
		wchar_t *pText=XBtn_GetText(hEle);
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,DT_VCENTER| DT_SINGLELINE);
		XDraw_SetTextColor_(hDraw,color);
		return ;
	}else if(STATE_LEAVE ==((button_*)hEle)->state)	//�뿪
	{
		if(BUTTON(hEle)->hImage_leave)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_leave,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(80,80,80),FALSE);
		}
	}else if( STATE_STAY==((button_*)hEle)->state)//ͣ��
	{
		if(BUTTON(hEle)->hImage_stay)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_stay,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(39,135,194),FALSE);
		}
	}else if( STATE_DOWN==((button_*)hEle)->state) //����
	{
		if(BUTTON(hEle)->hImage_down)
		{
			XDraw_HImageSuper_(hDraw,BUTTON(hEle)->hImage_down,&rect);
		}else
		{
			XDraw_Check_(hDraw,2,top,RGB(39,135,194),FALSE);
		}
		rcText.top+=2;
	}

	//�����ı�
	wchar_t *pText=XBtn_GetText(hEle);
	if(pText)
	{
		XDraw_DrawText_(hDraw,pText,wcslen(pText),&rcText,((button_*)hEle)->textFlag);
	}
}

BOOL CALLBACK Check_OnEventBtnClick(HELE hEle,HELE hEventEle)
{
	if(hEle==hEventEle)
	{
		XBtn_SetCheck(hEle,!XBtn_IsCheck(hEle));
		XEle_RedrawEle(hEle);
		return TRUE;
	}
	return FALSE;
}

void CALLBACK Check_OnDestroy(HELE hEle)  //����
{
	if(CHECK(hEle)->hImage_leave_check)   XImage_Destroy(CHECK(hEle)->hImage_leave_check);
	if(CHECK(hEle)->hImage_stay_check)    XImage_Destroy(CHECK(hEle)->hImage_stay_check);
	if(CHECK(hEle)->hImage_down_check)    XImage_Destroy(CHECK(hEle)->hImage_down_check);
	if(CHECK(hEle)->hImage_disable_check) XImage_Destroy(CHECK(hEle)->hImage_disable_check);
}

///@}